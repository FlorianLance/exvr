
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "xml_io_manager.hpp"

// std
#include <optional>

// Qt
#include <QDesktopServices>
#include <QFileDialog>
#include <QFileInfo>

// base
#include "utility/benchmark.hpp"

// local
#include "data/node_flow.hpp"
#include "utility/maths_utility.hpp"


using namespace tool;
using namespace tool::ex;

bool XmlIoManager::save_experiment_file(QString expFilePath){

    QtLogger::message(QSL("[XML] Save experiment to file: ") % expFilePath);
    QFile expFile(expFilePath);
    if ( !expFile.open(QIODevice::WriteOnly) ){
        return false;
    }
    expFileToSave = expFilePath;

    w = std::make_unique<QXmlStreamWriter>(&expFile);
    w->setAutoFormatting(true);
    w->writeStartDocument();
    write_experiment();
    w->writeEndDocument();

    return true;
}

bool XmlIoManager::load_experiment_file(QString expFilePath){

    QtLogger::message(QSL("[XML] Load experiment from file: ") % expFilePath);
    BenchGuard b("[XML::load_experiment_file");

    // set current file to load
    expFileToLoad = expFilePath;

    QFile file(expFileToLoad);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QtLogger::error(QSL("[XML] Can't load experiment file, invalid path: ") % expFileToLoad);
        return false;
    }

    // file valid, clean experiment
    m_experiment->clean_experiment();

    // unpile xml
    r = std::make_unique<QXmlStreamReader>();
    r->setDevice(&file);
    bool expValid = false;
    while(!r->atEnd()){
        if(check_start_node(QSL("Experiment"))){
            QtLogger::status(QSL("Read XML experiment file: ") % expFilePath, 2000);
            QtLogger::message(QSL("[XML] Read XML experiment file: ") % expFilePath);
            expValid = read_exp();
            QtLogger::status(QSL("XML experiment file loaded."), 2000);
            QtLogger::message(QSL("[XML] XML experiment file loaded."));
        }
        r->readNext();
    }

    // check nodes validity
    if(!expValid){
        QtLogger::error(QSL("[XML] Cannot read experiment xml. "));
        return false;
    }

    // xml has been fully loaded, update path
    m_experiment->states.currentExpfilePath = expFileToLoad;

//    m_experiment->check_elements();
    m_experiment->compute_loops_levels();    
    m_experiment->check_legacy_conditions(); // due to previous used xml format

    m_experiment->update_conditions();
    m_experiment->selectedElement = nullptr;

    // clean XML elements arrays
    readXmlRoutines.clear();
    readXmlISIs.clear();
    readXmlStartLoops.clear();
    readXmlEndLoops.clear();

    // check validity
    m_experiment->check_integrity();


    QtLogger::status(QSL("Loading done."), 2000);
    QtLogger::message(QSL("[XML] Loading done."));

    return true;
}



bool XmlIoManager::read_exp(){

    BenchGuard b("[XML::read_exp");

    assign_attribute(m_experiment->states.currentName, QSL("name"), false);
    assign_attribute(m_experiment->states.loadedExpDesignerVersion, QSL("version"), true);
    assign_attribute(m_experiment->states.currentMode, QSL("mode"), false);
    assign_attribute(m_experiment->states.designerPathUsedForLoadedExp, QSL("designer-used"), false);

    auto split = m_experiment->states.loadedExpDesignerVersion.split(".");
    if(split.size() == 2){
        const auto major = split[0].toInt();
        if(m_experiment->states.majorNumVersion != major){
            QtLogger::error(QSL("[XML] Incompatible version of experiment file: software is ") %
                    QString::number(m_experiment->states.majorNumVersion) % QSL(" and file is ") % m_experiment->states.loadedExpDesignerVersion);
            return false;
        }
    }else{
        QtLogger::error(QSL("[XML] Invalid version number."));
        return false;
    }

    if(auto designerUsed = read_attribute<QString>(QSL("designer-used"), false); designerUsed.has_value()){
        QtLogger::message(QSL("[XML] Experiment previously saved by designer: ") % designerUsed.value() %
                          QSL(" with version: ") % m_experiment->states.loadedExpDesignerVersion);
    }

    r->readNext();

    bool currentNodeValid   = false;
    while(!r->atEnd()){       
        if(check_start_node(QSL("Settings"))){
            QtLogger::message(QSL("[XML] Read settings..."));
            if(!read_settings()){
                break;
            }
        }else if(check_start_node(QSL("Resources"))){
            QtLogger::message(QSL("[XML] Read resources..."));
            if(auto reloadCode = read_attribute<int>(QSL("reload"), true); reloadCode.has_value()){                
                ResourcesManager::get()->set_reload_code(reloadCode.value());
            }            
            if(!read_resources()){
                break;
            }
        }else if(check_start_node(QSL("Components"))){
            QtLogger::message(QSL("[XML] Read components..."));
            if(!read_components()){
                break;
            }
        }else if(check_start_node(QSL("FlowElements"))){
            QtLogger::message(QSL("[XML] Read flow elements..."));
            if(!read_flow_elements()){
                break;
            }
        }else if(check_start_node(QSL("FlowSequence"))){
            QtLogger::message(QSL("[XML] Read flow sequence..."));
            if(!read_flow_sequence()){
                break;
            }
        }else if(check_end_node(QSL("Experiment"))){
            currentNodeValid = true;
            break;
        }
        r->readNext();
    }

    return currentNodeValid;
}

ElementUP XmlIoManager::read_element(){

    const auto id = read_attribute<int>(QSL("key"), true);
    const auto &typeStr = read_attribute<QString>(QSL("type"), true);
    if(!id.has_value() || !typeStr.has_value()){
        QtLogger::error(QSL("[XML] Invalid element at line: ") % QString::number(r->lineNumber()));
        return nullptr;
    }
    const Element::Type type = Element::get_type(typeStr.value().toStdString());

    ElementUP element = nullptr;
    switch (type) {{
    case Element::Type::Routine:
            for(size_t ii = 0; ii < readXmlRoutines.size(); ++ii){
                if(readXmlRoutines[ii] != nullptr){
                    if(readXmlRoutines[ii]->key() == id){
                        element = std::move(readXmlRoutines[ii]);
                        readXmlRoutines[ii] = nullptr;
                        return std::move(element);
                    }
                }
            }
    }break;{
    case Element::Type::Isi:
            for(size_t ii = 0; ii < readXmlISIs.size(); ++ii){
                if(readXmlISIs[ii] != nullptr){
                    if(readXmlISIs[ii]->key() == id){
                        element = std::move(readXmlISIs[ii]);
                        readXmlISIs[ii] = nullptr;
                        return std::move(element);
                    }
                }
            }
    }break;{
    case Element::Type::LoopStart:
            for(size_t ii = 0; ii < readXmlStartLoops.size(); ++ii){
                if(readXmlStartLoops[ii] != nullptr){
                    if(readXmlStartLoops[ii]->loop->key() == id){
                        element = std::move(readXmlStartLoops[ii]);
                        readXmlStartLoops[ii] = nullptr;
                        return std::move(element);
                    }
                }
            }
    }break;{
    case Element::Type::LoopEnd:
            for(size_t ii = 0; ii < readXmlEndLoops.size(); ++ii){
                if(readXmlEndLoops[ii] != nullptr){
                    if(readXmlEndLoops[ii]->loop->key() == id){
                        element = std::move(readXmlEndLoops[ii]);
                        readXmlEndLoops[ii] = nullptr;
                        return std::move(element);
                    }
                }
            }
    }break;{
    default: break;}
    }

    QtLogger::error(QSL("[XML] Cannot find flow sequence element at line: ") % QString::number(r->lineNumber()) % QSL(" with id ") % QString::number(id.value()));

    return nullptr;
}

void XmlIoManager::check_read_elements(){

    // routines
    size_t countBefore = readXmlRoutines.size();

    std::sort(readXmlRoutines.begin(), readXmlRoutines.end());
    readXmlRoutines.erase(std::unique(readXmlRoutines.begin(), readXmlRoutines.end()), readXmlRoutines.end());

    size_t countAfter = readXmlRoutines.size();
    if(countBefore > countAfter){
        QtLogger::warning(
            QSL("Remove ") % QString::number(countBefore - countAfter) % QSL(" duplicated routines.")
        );
    }

    for(auto &routine : readXmlRoutines){
        routine->check_integrity();
    }
}

bool XmlIoManager::check_start_node(QString nodeName){

    if(r->isStartElement()){
        if(r->name() == nodeName){
            return true;
        }
    }
    return false;
}

bool XmlIoManager::check_end_node(QString nodeName){
    if(r->isEndElement()){
        if(r->name() == nodeName){
            return true;
        }
    }
    return false;
}

QString XmlIoManager::invalid_bracket_error_message(int id, IdKey::Type type){
    return QSL("Invalid xml ") % from_view(IdKey::to_string(type)) % QSL(" (id:") % QString::number(id) % QSL("), no end bracket.");
}

void XmlIoManager::write_generator(const Generator &generator){

    w->writeAttribute(QSL("g_order"), QString::number(generator.order));

    if(generator.info.has_value()){
        w->writeAttribute(QSL("g_info"), generator.info.value());
    }
    if(generator.decimals.has_value()){
        w->writeAttribute(QSL("g_dec"), generator.decimals.value());
    }
    if(generator.min.has_value()){
        w->writeAttribute(QSL("g_min"), generator.min.value());
    }
    if(generator.max.has_value()){
        w->writeAttribute(QSL("g_max"), generator.max.value());
    }
    if(generator.step.has_value()){
        w->writeAttribute(QSL("g_step"), generator.step.value());
    }
}

Generator XmlIoManager::read_generator(){

    Generator g;   
    if(auto order = read_attribute<int>({"g_order","gen_order"}, true); order.has_value()){
        g.order = order.value();
    }
    g.info      = read_attribute<QString>({QSL("g_info"), QSL("gen_text")}, false);
    g.decimals  = read_attribute<QString>({QSL("g_dec"),  QSL("gen_decimals")}, false);
    g.min       = read_attribute<QString>({QSL("g_min"),  QSL("gen_min")}, false);
    g.max       = read_attribute<QString>({QSL("g_max"),  QSL("gen_max")}, false);
    g.step      = read_attribute<QString>({QSL("g_step"), QSL("gen_singleStep")}, false);
    return g;
}

void XmlIoManager::write_argument(const Arg &arg){

    w->writeStartElement(QSL("Arg"));
    w->writeAttribute(QSL("name"),  arg.name);
    w->writeAttribute(QSL("ui"),    from_view(get_name(arg.associated_ui_type())));
    w->writeAttribute(QSL("value"), arg.value());
    w->writeAttribute(QSL("type"),  from_view(get_unity_type_string(arg.unity_type())));
    int dim = arg.dimensions_nb();
    w->writeAttribute(QSL("dim"),   QString::number(dim));

    if(dim > 0){
        w->writeAttribute(QSL("sep"), arg.separator());
        QString sizesStr;
        for(int ii = 0; ii < arg.dimensions_nb(); ++ii){
            if(ii != 0){
                sizesStr += QSL(" ");
            }
            sizesStr += QString::number(arg.size_dimension(ii));
        }
        w->writeAttribute(QSL("sizes"), sizesStr);
    }

    if(arg.generator.has_value()){
        w->writeAttribute(QSL("gen"), "");
        write_generator(arg.generator.value());
    }

    w->writeEndElement();
}

void XmlIoManager::write_set(const Set &set){
    w->writeStartElement(QSL("Set"));
    w->writeAttribute(QSL("key"),   QString::number(set.key()));
    w->writeAttribute(QSL("name"),  set.name);
    w->writeAttribute(QSL("occu"),  QString::number(set.occurencies));
    w->writeEndElement();
}

std::tuple<std::optional<Arg>, QString> XmlIoManager::read_argument(){

//    const auto key        = read_attribute<int>({QSL("key"), QSL("key_ui"), QSL("key_ui_element")}, true);
    const auto name       = read_attribute<QString>(QSL("name"), true);
    const auto dim        = read_attribute<int>(QSL("dim"), true);
    const auto type       = read_attribute<QString>(QSL("type"), true);
    const auto value      = read_attribute<QString>(QSL("value"), true);
    const auto ui         = read_attribute<QString>({QSL("ui"), QSL("gen_type"), QSL("uiGeneratorType")}, true);

    if(!name.has_value()    ||
       !dim.has_value()     ||
       !type.has_value()    ||
       !value.has_value()   ||
       !ui.has_value()){
        return {std::nullopt,QSL("Invalid arg at line: ") % QString::number(r->lineNumber())};
    }

    const auto uiGType= tool::ex::get_ui_type(ui.value().toStdString());
    if(!uiGType.has_value()){
        return {std::nullopt,QSL("Invalid ui type at line: ") % QString::number(r->lineNumber())};
    }

    QString separator;
    QVector<int> sizes;
    if(dim.value() > 0){
        assign_attribute(separator, {QSL("sep"), QSL("separator")}, true);
        if(auto sizesStr = read_attribute<QString>(QSL("sizes"), true); sizesStr.has_value()){
            for(const auto &sizeStr : sizesStr.value().split(' ')){
                sizes << sizeStr.toInt();
            }
        }
    }

    std::optional<UnityType> uType = get_unity_type(type->toStdString());
    if(!uType.has_value()){
        return {std::nullopt,QSL("Invalid unity type type at line: ") % QString::number(r->lineNumber())};
    }

    Arg arg = Arg::generate_from_loaded_xml_values(uiGType.value(), name.value(), value.value(), separator, sizes, uType.value());
    if( has_attribute({QSL("gen"), QSL("generator")})){
        arg.generator = read_generator();
    }
    return {std::move(arg), ""};
}

ConfigUP XmlIoManager::read_config(){

    const auto key      = read_attribute<int>(QSL("key"), true);
    const auto name     = read_attribute<QString>(QSL("name"), true);
    if(!key.has_value() || !name.has_value() ){
        QtLogger::error(QSL("[XML] Invalid config at line: ") % QString::number(r->lineNumber()));
        return nullptr;
    }

    auto config = std::make_unique<Config>(name.value(), ConfigKey{key.value()});
    r->readNext();

    while(!r->atEnd()){

        if(check_start_node(QSL("Arg"))){
            if(auto arg = read_argument(); std::get<0>(arg).has_value()){
                config->add_arg(std::move(std::get<0>(arg).value()));
            }else{
                QtLogger::error(QSL("[XML] -> from config ") % name.value() % QSL(": ") % std::get<1>(arg));
            }
            r->readNext();
        }

        if(check_end_node(QSL("Config")) || check_end_node(QSL("InitConfig"))){
            return config;
        }

        r->readNext();
    }
    return nullptr;
}

void XmlIoManager::write_config(const Config *config, bool initConfig){

    w->writeStartElement(initConfig ? QSL("InitConfig") : QSL("Config"));
    w->writeAttribute(QSL("key"),  QString::number(config->key()));
    w->writeAttribute(QSL("name"), config->name);

    for(const auto &arg : config->args){
        write_argument(arg.second);
    }

    w->writeEndElement(); // /InitConfig or /Config
}

bool XmlIoManager::read_configs(Component *component){

    r->readNext();
    component->configs.clear();

    while(!r->atEnd()){

        if(check_start_node(QSL("Config"))){
            component->add_config(read_config());
        }

        if(check_end_node(QSL("Configs"))){
            return true;
        }

        r->readNext();
    }
    QtLogger::error(QSL("[XML] Invalid xml configs list, no end bracket."));

    return false;
}

ComponentUP XmlIoManager::read_component(){

    const auto key  = read_attribute<int>(QSL("key"), true);
    const auto name = read_attribute<QString>(QSL("name"), true);
    auto unityName  = read_attribute<QString>(QSL("type"), true);

    if(!key.has_value() || !name.has_value() || !unityName.has_value()){
        QtLogger::error(QSL("[XML] Invalid component at line: ") % QString::number(r->lineNumber()));
        return nullptr;
    }

    auto unityNameStr = unityName.value();
    auto type = Component::get_type_from_unity_name(unityNameStr.toStdString());

    if(!type.has_value()){

        // for converting legacy
        unityNameStr = unityNameStr.remove("Component"); // for old style
        unityNameStr = unityNameStr.remove("MP36");
        unityNameStr = unityNameStr.replace("EyeCamera", "Camera");
        unityNameStr = unityNameStr.replace("SpatializedAudio", "AudioSource");
        unityNameStr = unityNameStr.replace("TextCamera", "TextViewer");
        unityNameStr = unityNameStr.replace("SliderCamera", "SliderUI");

        // try again with modifications
        type = Component::get_type_from_unity_name(unityNameStr.toStdString());
        if(!type.has_value()){
            QtLogger::error(QSL("[XML] Invalid component type at line: ") % QString::number(r->lineNumber()) % QSL(" with name ") % name.value());
            return nullptr;
        }
    }

    // generate component
    auto component = std::make_unique<Component>(type.value(), ComponentKey{key.value()}, name.value());

    r->readNext();
    while(!r->atEnd()){

        if(check_start_node(QSL("InitConfig"))){
            component->initConfig = read_config();
        }else if(check_start_node(QSL("Configs"))){
            if(!read_configs(component.get())){
                return nullptr;
            }
        }else if(check_end_node(QSL("Component"))){
            return component;
        }

        r->readNext();
    }

    QtLogger::error(invalid_bracket_error_message(key.value(), IdKey::Type::Component));

    return nullptr;
}

std::unique_ptr<Resource> XmlIoManager::read_resource(){

    const auto key   = read_attribute<int>(QSL("key"), true);
    const auto typeStr = read_attribute<QString>(QSL("type"), true);
    const auto alias = read_attribute<QString>(QSL("alias"), true);
    const auto path  = read_attribute<QString>(QSL("path"), true);

    if(!key.has_value() || !typeStr.has_value() || !alias.has_value()  || !path.has_value()){
        QtLogger::error(QSL("[XML] Invalid resource at line: ") % QString::number(r->lineNumber()));
        return nullptr;
    }

    const auto type = Resource::get_type(typeStr.value().toStdString());
    if(!type.has_value()){
        QtLogger::error(QSL("[XML] Invalid resource type at line: ") % QString::number(r->lineNumber()));
        return nullptr;
    }

    auto resource = std::make_unique<Resource>(type.value(), key.value(), path.value(), alias.value());

    // check if absolute path
    auto fileInfo = QFileInfo(path.value());
    if(fileInfo.exists()){
        fileInfo.makeAbsolute();
        resource->path = fileInfo.canonicalFilePath();
        return resource;
    }

    if(fileInfo.isRelative()){

        // if relative
        auto expDir = QFileInfo(expFileToLoad).absoluteDir();
        fileInfo = QFileInfo(expDir.path() % QSL("/") % path.value());
        if(fileInfo.exists()){
            fileInfo.makeAbsolute();
            resource->path = fileInfo.canonicalFilePath();
        }else{
            QtLogger::error(QSL("[XML] Cannot create resource path from ") % path.value());
            // doesn't exist, keep loaded path
            resource->path  = path.value();
        }
        return  resource;
    }else if(fileInfo.isAbsolute()){
        QtLogger::error(QSL("[XML] Cannot find resource file from absolute path: ") % path.value());
    }

    // doesn't exist, keep loaded path
    resource->path  = path.value();

    return resource;
}

void XmlIoManager::write_component(const Component *component) {

    w->writeStartElement(QSL("Component"));
    w->writeAttribute(QSL("key"),                QString::number(component->key()));
    w->writeAttribute(QSL("name"),               component->name());
    w->writeAttribute(QSL("type"),               from_view(Component::get_unity_name(component->type)));
//    w->writeAttribute(QSL("static"),             component->isStatic ? "1" : "0");
//    w->writeAttribute(QSL("static_update"),      component->staticUpdate ? "1" : "0");
//    w->writeAttribute(QSL("static_visibility"),  component->staticVisibility ? "1" : "0");
    write_config(component->initConfig.get(), true);
    w->writeStartElement(QSL("Configs"));
    for(const auto &config : component->configs){
        write_config(config.get());
    }
    w->writeEndElement(); // /Configs
    w->writeEndElement(); // /Component
}

void XmlIoManager::write_interval(const Interval &interval){
    w->writeStartElement(QSL("Interval"));
    w->writeAttribute(QSL("key"),    QString::number(interval.key()));
    w->writeAttribute(QSL("t1"),     QString::number(interval.start.v));
    w->writeAttribute(QSL("t2"),     QString::number(interval.end.v));
    w->writeEndElement(); // /Interval
}

std::optional<Interval> XmlIoManager::read_interval(){

    const auto key   = read_attribute<int>(QSL("key"), true);
    const auto start = read_attribute<double>(QSL("t1"), true);
    const auto end   = read_attribute<double>(QSL("t2"), true);
    if(!key.has_value() || !start.has_value() || !end.has_value()){
        QtLogger::error(QSL("[XML] Invalid interval at line: ") % QString::number(r->lineNumber()));
        return {};
    }
    return Interval{SecondsTS{start.value()}, SecondsTS{end.value()}, IntervalKey{key.value()}};
}

void XmlIoManager::write_timeline(const Timeline *timeline){

    w->writeStartElement(QSL("Timeline"));
    w->writeAttribute(QSL("key"), QString::number(timeline->key()));
    w->writeAttribute(QSL("type"), (timeline->type == Timeline::Update ? QSL("Update") : QSL("Visibiliy")));

    double min = std::numeric_limits<double>::max();
    double max = 0.;
    for(const auto &interval : timeline->intervals){
        if(interval.start.v < min){
            min = interval.start.v;
        }
        if(interval.end.v > max){
            max = interval.end.v;
        }
    }
    if(timeline->intervals.size() > 0){
        w->writeComment(QSL("Starts at ") % QString::number(min) % QSL("(s) and ends at ") % QString::number(max) % QSL("s(), duration: ") % QString::number(max-min) % QSL("(s)"));
    }

    for(const auto &interval : timeline->intervals){
        write_interval(interval);
    }
    w->writeEndElement(); // /Timeline
}

TimelineUP XmlIoManager::read_timeline(){

    const auto key  = read_attribute<int>(QSL("key"), true);
    const auto typeStr = read_attribute<QString>(QSL("type"), true);

    if(!key.has_value() || !typeStr.has_value()){
        QtLogger::error(QSL("[XML] Invalid timeline at line: ") % QString::number(r->lineNumber()));
        return nullptr;
    }

    const auto type = typeStr.value() == QSL("Update") ? Timeline::Update : Timeline::Visibility;
    auto timeline = std::make_unique<Timeline>(type, TimelineKey{key.value()});

    // read attributes
    r->readNext();
    while(!r->atEnd()){
        if(check_start_node(QSL("Interval"))){
            if(auto interval = read_interval(); interval.has_value()){
                timeline->intervals.emplace_back(std::move(interval.value()));
            }
        }else if(check_end_node(QSL("Timeline"))){
            return timeline;
        }

        r->readNext();
    }

    return nullptr;
}

void XmlIoManager::write_action(const Action *action) {

    w->writeStartElement(QSL("Action"));
    w->writeAttribute(QSL("key"),           QString::number(action->key()));
    w->writeAttribute(QSL("key_component"), QString::number(action->component->key()));
    w->writeAttribute(QSL("key_config"),    QString::number(action->config->key()));
    w->writeAttribute(QSL("node_used"),     action->nodeUsed ? QSL("1") : QSL("0"));
    w->writeAttribute(QSL("node_position"), QString::number(action->nodePosition.x()) % QSL(" ") % QString::number(action->nodePosition.y()));
    //w->writeAttribute(QSL("node_size"),     QString::number(action->nodeSize.width()) % QSL(" ") % QString::number(action->nodeSize.height()));

    w->writeComment(QSL("Component ") % action->component->name() % QSL(" with config ") % action->config->name);
    write_timeline(action->timelineUpdate.get());
    write_timeline(action->timelineVisibility.get());
    w->writeEndElement(); // /Action
}

void XmlIoManager::write_connection(const Condition *condition, const Connection *connection){

    QString endName,endType, startName, startType;

    if(connection->startType == Connection::Type::Component){
        if(auto startComponent = condition->get_component_from_key(ComponentKey{connection->startKey}); startComponent != nullptr){
            startName = startComponent->name();
            startType = QSL("Component");
        }else{
            QtLogger::error(QSL("[XML] Invalid start component: ") % connection->to_string() % QSL(" from ") % condition->to_string());
            return;
        }
    }else{
        if(auto startConnector = condition->get_connector_from_key(ConnectorKey{connection->startKey}); startConnector != nullptr){
            startName = startConnector->name;
            startType = QSL("Connector");
        }else{
            QtLogger::error(QSL("[XML] Invalid start connector: ") % connection->to_string() % QSL(" from ") % condition->to_string());
            return;
        }
    }

    if(connection->endType == Connection::Type::Component){
        if(auto endComponent = condition->get_component_from_key(ComponentKey{connection->endKey}); endComponent != nullptr){
            endName = endComponent->name();
            endType = QSL("Component");
        }else{
            QtLogger::error(QSL("[XML] Invalid end component: ") % connection->to_string() % QSL(" from ") % condition->to_string());
            return;
        }
    }else{
        if(auto endConnector = condition->get_connector_from_key(ConnectorKey{connection->endKey}); endConnector != nullptr){
            endName = endConnector->name;
            endType = QSL("Connector");
        }else{
            QtLogger::error(QSL("[XML] Invalid end connector: ") % connection->to_string() % QSL(" from ") % condition->to_string());
            return;
        }
    }

    w->writeComment(QSL("Connection between ") %
        QSL("Key") % QString::number(connection->startKey) % QSL(":") % startType % QSL(":") % startName % QSL(":Port") +
                     QString::number(connection->startIndex) + " and " +
        QSL("Key") % QString::number(connection->endKey)   % QSL(":") % endType % QSL(":") % endName % QSL(":Port") +
                     QString::number(connection->endIndex));

    w->writeStartElement(QSL("Connection"));
    w->writeAttribute(QSL("key"),      QString::number(connection->key()));
    w->writeAttribute(QSL("out_type"), connection->startType == Connection::Type::Component ? QSL("component") : QSL("connector"));
    w->writeAttribute(QSL("out_key"),  QString::number(connection->startKey));
    w->writeAttribute(QSL("signal_id"),QString::number(connection->startIndex));
    w->writeAttribute(QSL("out_data_type"),  connection->startDataType);
    w->writeAttribute(QSL("signal"),   connection->signal);

    w->writeAttribute(QSL("in_type"),  connection->endType == Connection::Type::Component ? QSL("component") : QSL("connector"));
    w->writeAttribute(QSL("in_key"),   QString::number(connection->endKey));
    w->writeAttribute(QSL("slot_id"),  QString::number(connection->endIndex));
    w->writeAttribute(QSL("in_data_type"),   connection->endDataType);
    w->writeAttribute(QSL("slot"),     connection->slot);

    w->writeEndElement(); // /Connection
}

void XmlIoManager::write_connector(const Connector *connector){

    w->writeStartElement(QSL("Connector"));
    w->writeAttribute(QSL("key"), QString::number(connector->key()));
    w->writeAttribute(QSL("name"), connector->name);
    w->writeAttribute(QSL("node_position"), QString::number(connector->pos.x()) % QSL(" ") % QString::number(connector->pos.y()));
    w->writeAttribute(QSL("node_size"),     QString::number(connector->size.width()) % QSL(" ") % QString::number(connector->size.height()));
    write_argument(connector->arg);
    w->writeEndElement(); // /Connector
}


std::tuple<ActionUP, QString> XmlIoManager::read_action(){

    const auto key          = read_attribute<int>(QSL("key"), true);
    const auto keyComponent = read_attribute<int>(QSL("key_component"), true);
    const auto configKey    = read_attribute<int>(QSL("key_config"), true);

    if(!key.has_value() || !keyComponent.has_value() || !configKey.has_value()){
        return {nullptr, QSL("Invalid action at line: ") % QString::number(r->lineNumber())};
    }

    Component *actionComponent = m_experiment->get_component(ComponentKey{keyComponent.value()});
    if(actionComponent == nullptr){
        return {nullptr, QSL("Invalid action at line: ") % QString::number(r->lineNumber()) % QSL(", cannot found component with key ") % QString::number(keyComponent.value())};
    }

    Config *actionConfig = actionComponent->get_config(ConfigKey{configKey.value()});
    if(actionConfig == nullptr){
        return {nullptr, QSL("Invalid action at line: ") % QString::number(r->lineNumber()) % QSL(", cannot found config with key ") % QString::number(configKey.value())};
    }

    ActionUP action = std::make_unique<Action>(actionComponent, actionConfig, ActionKey{key.value()});
    assign_attribute(action->nodeUsed, QSL("node_used"), true);
    if(auto nodePositionStr = read_attribute<QString>(QSL("node_position"), true); nodePositionStr.has_value()){
        const auto split = nodePositionStr.value().split(" ");
        action->nodePosition = QPointF(split[0].toDouble(), split[1].toDouble());
    }

//    if(auto nodeSizeStr = read_attribute<QString>(QSL("node_size"), false); nodeSizeStr.has_value()){
//        const auto split = nodeSizeStr.value().split(" ");
//        action->nodeSize = QSize(split[0].toInt(), split[1].toInt());
//    }

    r->readNext();
    while(!r->atEnd()){

        if(check_start_node("Timeline")){

            if(auto timeline = read_timeline(); timeline != nullptr){
                if(timeline->type == Timeline::Type::Update){
                    action->timelineUpdate     = std::move(timeline);
                }else{
                    action->timelineVisibility = std::move(timeline);
                }
            }

        }else if(check_end_node("Action")){
            return {std::move(action), ""};
        }

        r->readNext();
    }

    return {nullptr, invalid_bracket_error_message(key.value(), IdKey::Type::Action)};
}

std::tuple<ConnectionUP, QString> XmlIoManager::read_connection(Condition *condition){

    auto key = read_attribute<int>(QSL("key"), true);
    if(!key.has_value()){
        return {nullptr, QSL("Invalid key for connection.")};
    }

    auto connection = std::make_unique<Connection>(ConnectionKey{key.value()});

    connection->startType = compare_attribute(QSL("out_type"), QSL("component"), true) ? Connection::Type::Component : Connection::Type::Connector;
    assign_attribute(connection->startKey,      QSL("out_key"), true);
    assign_attribute(connection->startIndex,    QSL("signal_id"), true);

    assign_attribute(connection->startDataType, QSL("out_data_type"), true);
    assign_attribute(connection->signal,        QSL("signal"), true);

    connection->endType  = compare_attribute(QSL("in_type"), QSL("component"), true) ? Connection::Type::Component : Connection::Type::Connector;
    assign_attribute(connection->endKey,        QSL("in_key"), true);
    assign_attribute(connection->endIndex,      QSL("slot_id"), true);
    assign_attribute(connection->endDataType,   QSL("in_data_type"), true);
    assign_attribute(connection->slot,          QSL("slot"), true);       

    // replace underscore in slot/signal names by white space
    connection->slot   = connection->slot.replace('_', ' ');
    connection->signal = connection->signal.replace('_', ' ');

    if(connection->startType == Connection::Type::Component){

        if(auto component = condition->get_component_from_key(ComponentKey{connection->startKey}); component != nullptr){

            if(!Component::has_signals(component->type)){ // no signals
                return {nullptr, QSL("Invalid ") % connection->to_string() % QSL(" from ") % condition->to_string() + QSL(", component doesn't have any signal.")};
            }else{

                if(to_unsigned(connection->startIndex) >= Component::signals_count(component->type)){
                    return {nullptr, QSL("Invalid ") % connection->to_string() % QSL(" from ") % condition->to_string() % QSL(", id signal is bigger than number of signals available.")};
                }
            }
        }else{
            return {nullptr, QSL("Invalid ") % connection->to_string() % QSL(" from ") + condition->to_string() % QSL(", component not found in condition.")};
        }
    }else{

        if(auto connector = condition->get_connector_from_key(ConnectorKey{connection->startKey})){

            const auto io = Connector::get_io(connector->type);
            if(to_unsigned(connection->startIndex) >= io.outNb){
                return {nullptr, QSL("Invalid ") % connection->to_string() % QSL(" from ") % condition->to_string() % QSL(", id signal is bigger than number of signals available.")};
            }

        }else{
            return {nullptr, QSL("Invalid ") % connection->to_string() % QSL(" from ") + condition->to_string() % QSL(", connector not found in condition.")};
        }
    }

    if(connection->endType == Connection::Type::Component){


        if(auto component = condition->get_component_from_key(ComponentKey{connection->endKey}); component != nullptr){

            if(!Component::has_slots(component->type)){ // no signals
                return {nullptr, QSL("Invalid ") % connection->to_string() % QSL(" from ") % condition->to_string() % QSL(", component not found in condition.")};
            }else{
                if(to_unsigned(connection->endIndex) >= Component::slots_count(component->type)){
                    return {nullptr, QSL("Invalid ") % connection->to_string() % QSL(" from ") % condition->to_string() % QSL(", id slot is bigger than number of slots available.")};
                }
            }
        }else{
            return {nullptr, QSL("Invalid ") % connection->to_string() % QSL(" from ") % condition->to_string() % QSL(", component doesn't exist.")};
        }

    }else{

        if(auto connector = condition->get_connector_from_key(ConnectorKey{connection->endKey})){

            const auto io = Connector::get_io(connector->type);
            if(to_unsigned(connection->endIndex) >= io.inNb){
                return {nullptr, QSL("Invalid ") % connection->to_string() % QSL(" from ") % condition->to_string() % QSL(", id slot is bigger than number of slots available.")};
            }

        }else{
            return {nullptr, QSL("Invalid ") % connection->to_string() % QSL(" from ") + condition->to_string() % QSL(", connector not found in condition.")};
        }
    }

    return {std::move(connection), ""};
}

std::tuple<ConnectorUP, QString> XmlIoManager::read_connector(){

    const auto key         = read_attribute<int>(QSL("key"), true);
    auto name              = read_attribute<QString>(QSL("name"), true);
    const auto nodePosStr  = read_attribute<QString>(QSL("node_position"), true);
    const auto nodeSizeStr = read_attribute<QString>(QSL("node_size"), false);

    if(!key.has_value()          ||
       !name.has_value()         ||
       !nodePosStr.has_value()   ||
       !nodeSizeStr.has_value()){
        return {nullptr,QSL("invalid connector at line: ") % QString::number(r->lineNumber())};
    }

    // for converting legacy
    if(name.value().contains(QSL("Operator"))){
        name.value().replace(QSL("BinaryOperator"),QSL("BinaryOperation"));
        name.value().replace(QSL("DecimalOperator"),QSL("DecimalOperation"));
        name.value().replace(QSL("StringOperator"),QSL("StringOperation"));
    }
    if(name.value().contains(QSL("Source"))){
        name.value().remove(QSL("Source"));
    }
    if(name.value().contains(QSL("Function"))){
        name.value().remove(QSL("Function"));
    }
    if(name.value().contains(QSL("Operator"))){
        name.value().remove(QSL("Operator"));
    }
    if(name.value().contains(QSL("Convertor"))){
        name.value().remove(QSL("Convertor"));
    }
    if(name.value().contains(QSL("Action"))){
        name.value().remove(QSL("Action"));
    }

    auto typeFromStr = Connector::get_type_from_name(name.value().toStdString());
    if(!typeFromStr.has_value()){
        return {nullptr,QSL("invalid connector type at line: ") % QString::number(r->lineNumber()) % QSL(" (") % name.value() % QSL(")")};
    }

    auto split               = nodePosStr.value().split(" ");
    const auto nodePosition  = QPointF(split[0].toDouble(), split[1].toDouble());
    split                    = nodeSizeStr.value().split(" ");
    const auto nodeSize      = QSize(split[0].toInt(), split[1].toInt());
    Q_UNUSED(nodeSize)

    while(!r->atEnd()){

        if(check_start_node(QSL("Arg"))){
            if(auto arg = read_argument(); std::get<0>(arg).has_value()){
                r->readNext();                               

                return {
                    std::make_unique<Connector>(ConnectorKey{key.value()}, typeFromStr.value(), name.value(), nodePosition, std::move(std::get<0>(arg).value())),
                    ""
                };
            }
            break;
        }
        r->readNext();
    }

    return {nullptr, QSL("invalid connector at line: ") % QString::number(r->lineNumber()) % QSL(", no argument found.")};
}

void XmlIoManager::write_condition(const Condition *condition){

    w->writeStartElement(QSL("Condition"));
    w->writeAttribute(QSL("key"), QString::number(condition->key()));
    w->writeAttribute(QSL("name"), condition->name);
    w->writeAttribute(QSL("duration"),  QString::number(condition->duration.v));
    w->writeAttribute(QSL("ui_scale"),  QString::number(condition->scale));
    w->writeAttribute(QSL("ui_size"),   QString::number(condition->uiFactorSize));

    QStringList setsKeys;
    for(const auto &setKey : condition->setsKeys){
        setsKeys << QString::number(setKey);
    }
    w->writeAttribute(QSL("sets_keys"), setsKeys.join("-"));

    // find the longest timeline for every action
    double min = std::numeric_limits<double>::max();
    double max = 0.;
    for(const auto &action : condition->actions){

        for(const auto &interval : action->timelineUpdate->intervals){
            if(interval.start.v < min){
                min = interval.start.v;
            }
            if(interval.end.v > max){
                max = interval.end.v;
            }
        }
        for(const auto &interval : action->timelineVisibility->intervals){
            if(interval.start.v < min){
                min = interval.start.v;
            }
            if(interval.end.v > max){
                max = interval.end.v;
            }
        }
    }

    for(const auto &action : condition->actions){
        write_action(action.get());
    }

    for(const auto &connector : condition->connectors){
        write_connector(connector.get());                
    }

    for(const auto &connection : condition->connections){

        if(connection->endType == Connection::Type::Connector){
            if(auto inConnector = condition->get_connector_from_key(ConnectorKey{connection->endKey}); inConnector != nullptr){
                if(!inConnector->inputValidity){
                    QtLogger::error(QSL("[XML] ") % connection->to_string() % QSL(" not valid with ") % inConnector->to_string());
                    continue;
                }
            }
        }
        write_connection(condition, connection.get());
    }

    w->writeEndElement(); // /Condition
}


ConditionUP XmlIoManager::read_condition(Routine *routine){

    const auto key          = read_attribute<int>(QSL("key"), true);
    const auto name         = read_attribute<QString>(QSL("name"), true);
    const auto duration     = read_attribute<double>({QSL("duration"),QSL("ui_max_length")}, true);
    const auto uiScale      = read_attribute<double>(QSL("ui_scale"), true);
    const auto uiSize       = read_attribute<double>(QSL("ui_size"), true);

    if(!key.has_value()         ||
       !name.has_value()        ||
       !duration.has_value()    ||
       !uiScale.has_value()     ||
       !uiSize.has_value()){
        QtLogger::error(QSL("[XML] -> from routine ") % routine->name() % QSL(": invalid condition at line: ") % QString::number(r->lineNumber()));
        return {};
    }

    auto condition = Condition::generate_from_data(name.value(), ConditionKey{key.value()}, SecondsTS{duration.value()}, uiScale.value(), uiSize.value());

    const auto setsKeys = read_attribute<QString>(QSL("sets_keys"), false);
    if(setsKeys.has_value()){
        for(auto split : setsKeys->split("-")){
            condition->setsKeys.emplace_back(split.toInt());
        }
    }

    r->readNext();
    while(!r->atEnd()){

        if(check_start_node(QSL("Action"))){

            if(auto action = read_action(); std::get<0>(action) != nullptr){
                condition->actions.emplace_back(std::move(std::get<0>(action)));
            }else{
                QtLogger::error(QSL("[XML] -> from routine ") % routine->name() % QSL(", from condition ") % name.value() % QSL(": ") % std::get<1>(action));
            }

        }else if(check_start_node(QSL("Connector"))){

            if(auto connector = read_connector(); std::get<0>(connector) != nullptr){
                condition->connectors.emplace_back(std::move(std::get<0>(connector)));
            }else{
                QtLogger::error(QSL("[XML] -> from routine ") % routine->name() % QSL(", from condition ") % name.value() % QSL(": ") % std::get<1>(connector));
            }

        }else if(check_start_node(QSL("Connection"))){

            if(auto connection = read_connection(condition.get()); std::get<0>(connection) != nullptr){
                condition->connections.emplace_back(std::move(std::get<0>(connection)));
            }else{
                QtLogger::error(QSL("[XML] -> from routine ") % routine->name() % QSL(", from condition ") % name.value() % QSL(": ") % std::get<1>(connection));
            }

        }else if(check_end_node(QSL("Condition"))){
            return condition;
        }
        r->readNext();
    }

    return nullptr;
}

void XmlIoManager::write_element(const Element *element){

    if(element->type == Element::Type::Node){
        return;
    }

    w->writeStartElement(QSL("Element"));
    w->writeAttribute(QSL("key"),  QString::number(element->key()));
    w->writeAttribute(QSL("type"), from_view(Element::get_type_name(element->type)));
    w->writeEndElement(); // /Element
}

void XmlIoManager::write_loop(const Loop *loop) {

    w->writeStartElement(QSL("Loop"));
    w->writeAttribute(QSL("key"), QString::number(loop->key()));
    w->writeAttribute(QSL("name"), loop->name());
    w->writeAttribute(QSL("type"), from_view(Loop::get_name(loop->mode)));
    w->writeAttribute(QSL("nbReps"), QString::number(loop->nbReps));
    w->writeAttribute(QSL("N"), QString::number(loop->N));

    if(loop->mode == Loop::Mode::File){
        w->writeAttribute(QSL("path"), loop->filePath);
        for(const auto &set : loop->fileSets){
            write_set(set);
        }

    }else{
        for(const auto &set : loop->sets){
            write_set(set);
        }
    }           

    w->writeEndElement(); // /Loop
}

std::tuple<LoopNodeUP, LoopUP, LoopNodeUP> XmlIoManager::read_loop(){

    const auto key          = read_attribute<int>(QSL("key"), true);
    const auto name         = read_attribute<QString>(QSL("name"), true);
    const auto type         = read_attribute<QString>(QSL("type"), true);
    if(!key.has_value()         ||
       !type.has_value()        ||
       !name.has_value()){
        QtLogger::error(QSL("[XML] Invalid Loop at line: ") + QString::number(r->lineNumber()));
        return std::make_tuple(nullptr,nullptr,nullptr);
    }

    LoopUP loop = std::make_unique<Loop>(name.value(), ElementKey{key.value()});
    if(auto mode = Loop::get_mode(type.value().toStdString()); mode.has_value()){
        loop->mode = mode.value();
    }else{
        QtLogger::error(QSL("[XML] Invalid Loop type at line: ") + QString::number(r->lineNumber()));
        return std::make_tuple(nullptr,nullptr,nullptr);
    }

    assign_attribute(loop->nbReps , QSL("nbReps"), true);
    assign_attribute(loop->N , QSL("N"), false);

    // init loop start
    LoopNodeUP startLoop = std::make_unique<LoopNode>(loop.get(), true);
    LoopNodeUP endLoop   = std::make_unique<LoopNode>(loop.get(), false);
    loop->set_nodes(startLoop.get(), endLoop.get());

    // old set system
    const auto sets = read_attribute<QString>(QSL("set"), false);
    if(sets.has_value()){
        for(auto setStr : sets->split(" ")){
            loop->sets.emplace_back(Set(setStr, SetKey{-1}));
        }
        return std::make_tuple(std::move(startLoop), std::move(loop), std::move(endLoop));
    }


    // new set system
    r->readNext();
    while(!r->atEnd()){

        if(check_start_node(QSL("Set"))){

            if(auto set = read_set(); set.has_value()){
                loop->sets.emplace_back(std::move(set.value()));
            }
            r->readNext();
        }

        if(check_end_node(QSL("Loop"))){
            return std::make_tuple(std::move(startLoop), std::move(loop), std::move(endLoop));
        }

        r->readNext();
    }
    return {nullptr,nullptr,nullptr};
}

std::optional<Set> XmlIoManager::read_set(){

    const auto key        = read_attribute<int>(QSL("key"), true);
    const auto name       = read_attribute<QString>(QSL("name"), true);
    const auto occu       = read_attribute<int>(QSL("occu"), true);

    if(!key.has_value()     ||
       !name.has_value()    ||
       !occu.has_value()){
        QtLogger::error(QSL("[XML] Invalid set at line: ") + QString::number(r->lineNumber()));
        return {};
    }

    Set set(name.value(), SetKey{key.value()});
    set.occurencies = occu.value();
    return {set};
}

void XmlIoManager::write_routine(const Routine *routine){

    w->writeStartElement(QSL("Routine"));
    w->writeAttribute(QSL("key"), QString::number(routine->key()));
    w->writeAttribute(QSL("name"), routine->name());
    w->writeAttribute(QSL("randomizer"), routine->isARandomizer ? "1" : "0");

    for(const auto &cond : routine->conditions){
        write_condition(cond.get());
    }

    w->writeEndElement(); // /Routine
}

void XmlIoManager::write_settings(){

    auto settings = m_experiment->settings();

    w->writeStartElement(QSL("Settings"));{

        w->writeAttribute(QSL("debug"), settings->debug ? "1" : "0");
        w->writeAttribute(QSL("csharp_debug_info"), settings->csharpAddDebugInfo? "1" : "0");
        w->writeAttribute(QSL("catch_components_exceptions"), settings->catchComponentsExceptions ? "1" : "0");
        w->writeAttribute(QSL("positional_tracking"), settings->positionalTracking ? "1" : "0");
        w->writeAttribute(QSL("catch_external_keyboard_events"), settings->catchExternalKeyboardKeysEvents ? "1" : "0");

        w->writeStartElement(QSL("Display"));{
            w->writeAttribute(QSL("mode"), QString::number(static_cast<int>(settings->displayMode)));
            w->writeAttribute(QSL("stereo_fov"), QString::number(static_cast<int>(settings->stereoCameraFOV)));
            w->writeAttribute(QSL("fullscreen"), settings->fullscreen ? "1" : "0");
            w->writeAttribute(QSL("monitor_id"), QString::number(static_cast<int>(settings->monitorId)));
            w->writeAttribute(QSL("resolution_id"), QString::number(static_cast<int>(settings->resolutionId)));
            w->writeAttribute(QSL("custom_width"), QString::number(static_cast<int>(settings->customWidth)));
            w->writeAttribute(QSL("custom_height"), QString::number(static_cast<int>(settings->customHeight)));
        }w->writeEndElement(); // /Display

        w->writeStartElement(QSL("Camera"));{
            w->writeAttribute(QSL("neutral_x"), settings->neutralX ? "1" : "0");
            w->writeAttribute(QSL("neutral_y"), settings->neutralY ? "1" : "0");
            w->writeAttribute(QSL("neutral_z"), settings->neutralZ ? "1" : "0");
        }w->writeEndElement(); // /Camera

    }w->writeEndElement(); // /Settings
}

void XmlIoManager::write_resources(){

    auto resM = ResourcesManager::get();

    w->writeStartElement(QSL("Resources")); 
    w->writeAttribute(QSL("reload"), QString::number(resM->reload_code()));

    for(const auto resT : Resource::get_types()){

        const QString typeN = std::string(Resource::get_name(resT)).c_str();
        for(const auto &resource : resM->get_resources(resT)){
            w->writeStartElement(QSL("Resource"));
            w->writeAttribute(QSL("key"),       QString::number(resource->key()));
            w->writeAttribute(QSL("type"),      typeN);
            w->writeAttribute(QSL("alias"),     resource->alias);

            if(!resM->exportMode){
                if(QFileInfo(resource->path).exists()){ // write relative path if possible
                    auto dir = QFileInfo(expFileToSave).absoluteDir();
                    w->writeAttribute(QSL("path"),      dir.relativeFilePath(resource->path));
                }else{
                    w->writeAttribute(QSL("path"),      resource->path);
                }
            }else{
                w->writeAttribute(QSL("path"),  "./resources/" + typeN + "/" + resource->path.split("/").last());
            }

            w->writeEndElement(); // /resource
        }
    }
    w->writeEndElement(); // /resources
}

void XmlIoManager::write_components(){

    w->writeStartElement(QSL("Components"));{
        for(const auto &component : ComponentsManager::get()->components){
            write_component(component.get());
        }
    }w->writeEndElement(); // /Components
}

void XmlIoManager::write_flow_elements(){

    w->writeStartElement(QSL("FlowElements"));{
        w->writeStartElement(QSL("Routines"));{
            for(const auto &routine : m_experiment->get_elements_from_type<Routine>()){
                write_routine(routine);
            }
        }w->writeEndElement(); // /Routines

        w->writeStartElement(QSL("ISIs"));{
            for(const auto &isi : m_experiment->get_elements_from_type<Isi>()){
                write_isi(isi);
            }
        }w->writeEndElement(); // /ISIs

        w->writeStartElement(QSL("Loops"));{
            for(const auto &loop : m_experiment->loops){
                write_loop(loop.get());
            }
        }w->writeEndElement(); // /Loops

    }w->writeEndElement(); // /FlowElements
}

void XmlIoManager::write_flow_sequence(){

    w->writeStartElement(QSL("FlowSequence"));{
        for(const auto &elem : m_experiment->elements){
            write_element(elem.get());
        }
    }w->writeEndElement(); // /FlowSequence
}

void XmlIoManager::write_experiment(){

    w->writeStartElement(QSL("Experiment"));{

        w->writeAttribute(QSL("name"), m_experiment->states.currentName);
        w->writeAttribute(QSL("version"), m_experiment->states.numVersion);
        w->writeAttribute(QSL("mode"), m_experiment->states.currentMode);
        w->writeAttribute(QSL("designer-used"), Paths::exe);        

        write_settings();
        write_resources();
        write_components();

        write_flow_elements();
        write_flow_sequence();

    }w->writeEndElement(); // /Experiment
}

bool XmlIoManager::save_instance_file(const Instance &instance, QString instanceFilePath){

    QFile instanceFile(instanceFilePath);
    if ( !instanceFile.open(QIODevice::WriteOnly) ){
        QtLogger::error(QSL("[XML] Cannot write instance file, invalid path ") + instanceFilePath);
        return false;
    }

    QXmlStreamWriter stream( &instanceFile );
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement(QSL("ExperimentFlow"));
    stream.writeAttribute(QSL("id_instance"), QString::number(instance.idInstance));
    for(auto &instElem : instance.flow){

        QString type = (instElem.elem->type == Element::Type::Routine) ? QSL("routine") : QSL("isi");
        stream.writeStartElement(QSL("Element"));
        stream.writeAttribute(QSL("key"),  QString::number(instElem.elem->key()));
        stream.writeAttribute(QSL("type"), type);
        stream.writeAttribute(QSL("name"), instElem.elem->name());
        stream.writeAttribute(QSL("cond"), instElem.condition);
        stream.writeAttribute(QSL("elem_iter"), QString::number(instElem.elementIteration));
        stream.writeAttribute(QSL("cond_iter"), QString::number(instElem.conditionIteration));
        stream.writeEndElement(); // /Element
    }
    stream.writeEndElement(); // /ExperimentFlow
    stream.writeEndDocument();
    return true;
}

std::unique_ptr<Instance> XmlIoManager::load_instance_file(QString instanceFilePath){

    QFile file(instanceFilePath);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QtLogger::error(QSL("[XML] Cannot read instance file ")  % instanceFilePath % QSL("."));
        return nullptr;
    }    

    // unpile xml
    r = std::make_unique<QXmlStreamReader>();
    r->setDevice(&file);

    std::unique_ptr<Instance> instance = std::make_unique<Instance>();
    instance->filePath = instanceFilePath;
    instance->fileName =  instanceFilePath.split("/").last();

    // unpile xml
    while(!r->atEnd()){
        if(check_start_node(QSL("ExperimentFlow"))){
            while(r->readNext()){
                if(check_start_node(QSL("Element"))){


                    const auto key      = read_attribute<int>(QSL("key"), true);
                    const auto name     = read_attribute<QString>(QSL("name"), true);
                    const auto type     = read_attribute<QString>(QSL("type"), true);
                    const auto cond     = read_attribute<QString>(QSL("cond"), true);
                    const auto elemIter = read_attribute<int>(QSL("elem_iter"), false);
                    const auto condIter = read_attribute<int>(QSL("cond_iter"), false);
                    if(!key.has_value() ||
                       !name.has_value() ||
                       !type.has_value() ||
                       !cond.has_value() ){
                        QtLogger::error(QSL("[XML] Invalid instance element at line: ") % QString::number(r->lineNumber()));
                        return nullptr;
                    }

                    if(type.value() == QSL("routine")){

                        auto routine = m_experiment->get_routine(ElementKey{key.value()});
                        if(!routine){
                            QtLogger::error(QSL("[XML] Invalid routine at line: ") % QString::number(r->lineNumber()));
                            return nullptr;
                        }

                        bool condFound = false;
                        for(const auto& condition : routine->conditions){
                            if(condition->name == cond.value()){
                                condFound = true;
                                break;
                            }
                        }

                        if(!condFound){
                            QtLogger::error(QSL("[XML] Condition ") % cond.value() % QSL(" not found in routine ") % routine->name());
                            return nullptr;
                        }

                        if(elemIter.has_value() && condIter.has_value()){
                            instance->flow.emplace_back(InstanceElement{elemIter.value(), condIter.value(), routine, cond.value()});
                        }else{
                            instance->flow.emplace_back(InstanceElement{0, 0, routine, cond.value()});
                        }

                    }else {

                        auto isi = m_experiment->get_isi(ElementKey{key.value()});
                        if(!isi){
                            QtLogger::error(QSL("[XML] Invalid ISI at line: ") % QString::number(r->lineNumber()));
                            return nullptr;
                        }

                        bool condFound = false;
                        for(const auto &interval : isi->intervals){
                            if(almost_equal<double>(interval, cond.value().toDouble())){
                                condFound = true;
                                break;
                            }
                        }

                        if(!condFound){
                            QtLogger::error(QSL("[XML] Interval ") % cond.value() % QSL(" not found in isi ") % isi->name());
                            return nullptr;
                        }

                        if(elemIter.has_value() && condIter.has_value()){
                            instance->flow.emplace_back(InstanceElement{elemIter.value(), condIter.value(), isi, cond.value()});
                        }else{
                            instance->flow.emplace_back(InstanceElement{0, 0, isi, cond.value()});
                        }
                    }

                }else if(check_end_node(QSL("ExperimentFlow"))){
                    return instance;
                }
            }
        }
        r->readNext();
    }

    return nullptr;
}

RoutineUP XmlIoManager::read_routine(){

    const auto key      = read_attribute<int>(QSL("key"), true);
    const auto name     = read_attribute<QString>(QSL("name"), true);
    const auto randomizer = read_attribute<bool>(QSL("randomizer"), false);
    if(!key.has_value() || !name.has_value() ){
        QtLogger::error(QSL("[XML] Invalid routine at line: ") % QString::number(r->lineNumber()));
        return nullptr;
    }

    RoutineUP routine = std::make_unique<Routine>(name.value(), key.value());
    if(randomizer.has_value()){
        routine->isARandomizer = randomizer.value();
    }

    if(!m_experiment->lastRoutineSelected){
        m_experiment->lastRoutineSelected = routine.get();
    }
    r->readNext();
    while(!r->atEnd()){
        if(check_start_node(QSL("Condition"))){
            if(auto condition = read_condition(routine.get()); condition != nullptr){
                routine->conditions.emplace_back(std::move(condition));
            }
        }else if(check_end_node(QSL("Routine"))){
            return routine;
        }
        r->readNext();
    }


    QtLogger::error(QSL("[XML] ") % invalid_bracket_error_message(key.value(), IdKey::Type::Element));

    return nullptr;
}

bool XmlIoManager::read_settings(){

    QtLogger::status(QSL("Read settings."), 2000);

    auto settings = m_experiment->settings();
    while(!r->atEnd()){

        if(check_start_node(QSL("Settings"))){
            assign_attribute(settings->debug, QSL("debug"), true);
            assign_attribute(settings->csharpAddDebugInfo, QSL("csharp_debug_info"), false);
            assign_attribute(settings->catchComponentsExceptions, QSL("catch_components_exceptions"), false);
            assign_attribute(settings->positionalTracking, QSL("positional_tracking"), false);
            assign_attribute(settings->catchExternalKeyboardKeysEvents, QSL("catch_external_keyboard_events"), false);
        }

        if(check_start_node(QSL("Display"))){           
            if(auto dMode = read_attribute<int>(QSL("mode"), true); dMode.has_value()){
                settings->displayMode = static_cast<Settings::ExpLauncherDisplayMode>(dMode.value());
            }
            assign_attribute(settings->monitorId, QSL("monitor_id"), false);
            assign_attribute(settings->stereoCameraFOV, QSL("stereo_fov"), false);
            assign_attribute(settings->fullscreen, QSL("fullscreen"), false);
            assign_attribute(settings->resolutionId, QSL("resolution_id"), false);
            assign_attribute(settings->customWidth, QSL("custom_width"), false);
            assign_attribute(settings->customHeight, QSL("custom_height"), false);
        }

        if(check_start_node(QSL("Camera"))){
            assign_attribute(settings->neutralX, QSL("neutral_x"), false);
            assign_attribute(settings->neutralY, QSL("neutral_y"), false);
            assign_attribute(settings->neutralZ, QSL("neutral_z"), false);
        }

        if(check_end_node(QSL("Settings"))){
            return true;
        }

        r->readNext();
    }

    return false;
}

bool XmlIoManager::read_components(){

    QtLogger::status("Read components.", 2000);
    BenchGuard bench("[XML::read_components]");
//    QCoreApplication::processEvents( QEventLoop::AllEvents, 5);

    r->readNext();

    while(!r->atEnd()){

        if(check_start_node(QSL("Component"))){
            if(auto component = read_component(); component != nullptr){
                ComponentsManager::get()->components.emplace_back(std::move(component));
            }            
        }

        if(check_end_node(QSL("Components"))){
            return true;
        }

//        QCoreApplication::processEvents( QEventLoop::AllEvents, 2);
        r->readNext();
    }

    QtLogger::error(QSL("[XML] Invalid xml Components, no end bracket. "));

    return false;
}



void XmlIoManager::write_isi(const Isi *isi){
    w->writeStartElement(QSL("Isi"));
    w->writeAttribute(QSL("key"), QString::number(isi->key()));
    w->writeAttribute(QSL("name"), isi->name());
    w->writeAttribute(QSL("set"), isi->str_intervals());
    w->writeAttribute(QSL("randomized"), (isi->randomized ? "1" : "0"));
    w->writeEndElement(); // /Isi
}

IsiUP XmlIoManager::read_isi(){

    const auto key      = read_attribute<int>(QSL("key"), true);
    const auto name     = read_attribute<QString>(QSL("name"), true);
    if(!key.has_value() || !name.has_value() ){
        QtLogger::error(QSL("[XML] Invalid Isi at line: ") + QString::number(r->lineNumber()));
        return nullptr;
    }

    IsiUP isi = std::make_unique<Isi>(name.value(), ElementKey{key.value()});
    isi->intervals.clear();
    if(auto set = read_attribute<QString>(QSL("set"), true); set.has_value()){
        for(const auto &split : set.value().split(" ")){
            isi->intervals.emplace_back(split.toDouble());
        }
    }
    assign_attribute(isi->randomized, QSL("randomized"), true);

    return isi;
}

bool XmlIoManager::read_ISIs(){

    BenchGuard bench("[XML::read_ISIs]");

    r->readNext();
    while(!r->atEnd()){

        if(check_start_node(QSL("Isi"))){

            if(auto isi = read_isi(); isi != nullptr){
                readXmlISIs.emplace_back(std::move(isi));
            }

        }else if(check_end_node(QSL("ISIs"))){
            return true;
        }

        //QCoreApplication::processEvents( QEventLoop::AllEvents, 2);
        r->readNext();
    }

    QtLogger::error(QSL("[XML] Invalid xml ISIs, no end bracket. "));

    return false;
}

bool XmlIoManager::read_loops(){

    BenchGuard bench("[XML::read_loops]");

    r->readNext();
    while(!r->atEnd()){
        if(check_start_node(QSL("Loop"))){

            if(auto [s,l,e] = read_loop(); s != nullptr){
                readXmlStartLoops.emplace_back(std::move(s));
                m_experiment->loops.emplace_back(std::move(l));
                readXmlEndLoops.emplace_back(std::move(e));
            }
        }else if(check_end_node(QSL("Loops"))){
            return true;
        }
        //QCoreApplication::processEvents( QEventLoop::AllEvents, 2);
        r->readNext();
    }
    QtLogger::error(QSL("[XML] Invalid xml Loops, no end bracket. "));

    return false;
}

bool XmlIoManager::read_routines(){

    BenchGuard bench("[XML::read_routines]");

    r->readNext();
    while(!r->atEnd()){
        if(check_start_node(QSL("Routine"))){

            if(auto routine = read_routine(); routine != nullptr){
                readXmlRoutines.emplace_back(std::move(routine));
            }

        }else if(check_end_node(QSL("Routines"))){

            return true;
        }
        //QCoreApplication::processEvents( QEventLoop::AllEvents, 2);
        r->readNext();
    }

    QtLogger::error(QSL("[XML] Invalid xml Routines, no end bracket. "));

    return false;
}

bool XmlIoManager::read_resources(){

    QtLogger::status("Read resources.", 2000);
    BenchGuard bench("[XML::read_resources]");
    //QCoreApplication::processEvents( QEventLoop::AllEvents, 5);

    r->readNext();
    while(!r->atEnd()){
        if(check_start_node(QSL("Resource"))){
            if(auto resource = read_resource();resource != nullptr){                
                ResourcesManager::get()->add_resource(std::move(resource));
            }
        }else if(check_end_node(QSL("Resources"))){
            return true;
        }

        //QCoreApplication::processEvents( QEventLoop::AllEvents, 2);
        r->readNext();
    }

    QtLogger::error(QSL("[XML] Invalid xml resources, no end bracket. "));
    return false;
}


bool XmlIoManager::read_flow_elements(){

    QtLogger::status("Read flow elements.", 2000);
    BenchGuard bench("[XML::read_flow_elements]");
    //QCoreApplication::processEvents( QEventLoop::AllEvents, 5);

    r->readNext();
    while(!r->atEnd()){

        if(check_start_node(QSL("Routines"))){
            if(!read_routines()){
                return false;
            }
        }else if(check_start_node(QSL("ISIs"))){
            if(!read_ISIs()){
                return false;
            }
        }else if(check_start_node(QSL("Loops"))){
            if(!read_loops()){
                return false;
            }
        }else if(check_end_node(QSL("FlowElements"))){            
            check_read_elements();
            return true;
        }
        r->readNext();
    }

    QtLogger::error(QSL("[XML] Invalid xml FlowElements, no end bracket. "));
    return false;
}



bool XmlIoManager::read_flow_sequence(){

    QtLogger::status("Read flow sequence.", 2000);
    BenchGuard bench("[XML::read_flow_sequence]");
    //QCoreApplication::processEvents( QEventLoop::AllEvents, 5);

    r->readNext();
    while(!r->atEnd()){
        if(check_start_node(QSL("Element"))){
            if(auto element = read_element(); element != nullptr){
                m_experiment->elements.emplace_back(std::make_unique<NodeFlow>());
                m_experiment->elements.emplace_back(std::move(element));
            }
        }else if(check_end_node(QSL("FlowSequence"))){
            // last node
            m_experiment->elements.emplace_back(std::make_unique<NodeFlow>());
            return true;
        }
        r->readNext();
    }

    QtLogger::error(QSL("[XML] Invalid xml FlowSequence, no end bracket. "));
    return false;
}


bool XmlIoManager::save_experiment(){

    if(m_experiment->states.currentExpfilePath.size() == 0){
        QtLogger::error(QSL("[XML] No current experiment file defined, use \"Save as\" instead. "));
        return false;
    }

    return save_experiment_file(m_experiment->states.currentExpfilePath);
}

bool XmlIoManager::save_experiment_to_temp(){
    QtLogger::message(QSL("[XML] Save experiment to temp location: ") % Paths::tempExp);
    return save_experiment_file(Paths::tempExp);
}

bool XmlIoManager::save_instance_to_temp(const Instance &instance){
    QtLogger::message(QSL("[XML] Save instance to temp location: ") % Paths::tempInstance);
    return save_instance_file(instance, Paths::tempInstance);
}

void XmlIoManager::open_temp_experiment_file(){
    QDesktopServices::openUrl(QUrl(Paths::tempExp, QUrl::TolerantMode));
}

void XmlIoManager::open_temp_instance_file(){
    QDesktopServices::openUrl(QUrl(Paths::tempInstance, QUrl::TolerantMode));
}

void XmlIoManager::open_experiment_directory(){
    QDesktopServices::openUrl(QUrl(Paths::expDir, QUrl::TolerantMode));
}

void XmlIoManager::open_current_exp_launcher_log_file(){
    QDesktopServices::openUrl(QUrl(Paths::expLogFile, QUrl::TolerantMode));
}

void XmlIoManager::open_current_designer_log_file(){
    QDesktopServices::openUrl(QUrl(Paths::designerLogFile, QUrl::TolerantMode));
}

void XmlIoManager::open_log_directory(){
    QDesktopServices::openUrl(QUrl(Paths::logsDir, QUrl::TolerantMode));
}

void XmlIoManager::export_experiment_to(){
    QString path = QFileDialog::getExistingDirectory(nullptr, "Export directory", "");
    if(path.length() > 0){
        QtLogger::message(QSL("[XML] Export experiment to directory: ") % path);
        QString expFilePath =  path % QSL("/") % m_experiment->states.currentName % QSL(".xml");
        auto resM = ResourcesManager::get();
        resM->exportMode = true;
        save_experiment_file(expFilePath);
        resM->exportMode = false;        
        resM->export_to(path);
    }
}

bool XmlIoManager::save_experiment_as(){

    QString path = QFileDialog::getSaveFileName(nullptr, "Experiment file", "", "XML (*.xml)");
    if(path.length() > 0){
        QtLogger::message(QSL("[XML] Save experiment as: ") % path);
        m_experiment->states.currentExpfilePath = path;
        m_experiment->states.currentName = m_experiment->states.currentExpfilePath.split('/').last().split('.').first();
        save_experiment();
        m_experiment->add_to_update_flag(UpdateUI);
        return true;
    }    
    return false;
}

bool XmlIoManager::load_experiment(){

    Bench::reset();

    QString path = QFileDialog::getOpenFileName(nullptr, "Experiment file", Paths::expDir, "XML (*.xml)");
    if(path.length() > 0){
        if(!load_experiment_file(path)){
            m_experiment->new_experiment();            
            return false;
        }
        Bench::display();
        m_experiment->add_to_update_flag(UpdateAll | ResetUI);
        return true;
    }
    return false;
}

bool XmlIoManager::load_dropped_experiment_file(QString path){

    Bench::reset();

    if(path.length() > 0){
        if(!load_experiment_file(path)){
            m_experiment->new_experiment();
            return false;
        }
        Bench::display();
        m_experiment->add_to_update_flag(UpdateAll | ResetUI);
        return true;
    }
    return false;
}


#include "moc_xml_io_manager.cpp"
