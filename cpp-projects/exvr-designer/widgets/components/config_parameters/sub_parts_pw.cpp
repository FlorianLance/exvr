
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#include "sub_parts_pw.hpp"


using namespace tool::ex;

TransformSubPart::TransformSubPart(QString name) : tr({name}), doNotApply({name + QSL("_do_not_apply")}){
    frame = ui::F::gen(ui::L::VB(),{tr()}, LStretch{false},LMargins{false});
    tr.w->layout()->addWidget(doNotApply());
}

TransformSubPart *TransformSubPart::init_widget(QString title){

    DsbSettings s1 = {MinV<qreal>{-10000.}, V<qreal>{0}, MaxV<qreal>{10000.}, StepV<qreal>{0.01}, 3};
    DsbSettings s2 = {MinV<qreal>{-10000.}, V<qreal>{0}, MaxV<qreal>{10000.}, StepV<qreal>{0.1},  3};
    DsbSettings s3 = {MinV<qreal>{-10000.}, V<qreal>{1}, MaxV<qreal>{10000.}, StepV<qreal>{0.01}, 3};

    Vector3dSettings trS    = {s1,s1,s1};
    Vector3dSettings rotS   = {s2,s2,s2};
    Vector3dSettings scS    = {s3,s3,s3};

    inputUiElements.emplace_back(UiElementKey{tr.key()}, tr.init_widget(title,trS,rotS,scS));
    inputUiElements.emplace_back(UiElementKey{doNotApply.key()}, doNotApply.init_widget(QSL("Do not apply"), false));

    return this;
}

WordSpaceCameraCanvasSubPart::WordSpaceCameraCanvasSubPart(){

    auto f0 = ui::F::gen(ui::L::HB(),{ui::W::txt("Distance: "),distance()}, LStretch{true},LMargins{false});
    auto f1 = ui::F::gen(ui::L::HB(),{ui::W::txt("Scale factor: "), scaleFactor(),
                                      ui::W::txt("Width: "),width(), ui::W::txt("Heght: "),height()}, LStretch{true},LMargins{false});
    auto f2 = ui::F::gen(ui::L::HB(),{ui::W::txt("Pivots x: "),pivotX(), ui::W::txt("y: "),pivotY()}, LStretch{true},LMargins{false});
    auto f3 = ui::F::gen(ui::L::HB(),{rotation()}, LStretch{true},LMargins{false});
    frame   = ui::F::gen(ui::L::VB(),{f0,f1,f2,f3}, LStretch{false},LMargins{true},QFrame::Shape::Box);
}

WordSpaceCameraCanvasSubPart *WordSpaceCameraCanvasSubPart::init_widget(){
    inputUiElements.emplace_back(UiElementKey{scaleFactor.key()}, scaleFactor.init_widget({MinV<qreal>{-10000.}, V<qreal>{1}, MaxV<qreal>{10000.}, StepV<qreal>{0.01}, 2}));
    inputUiElements.emplace_back(UiElementKey{distance.key()}, distance.init_widget({MinV<qreal>{-10000.}, V<qreal>{10}, MaxV<qreal>{10000.}, StepV<qreal>{0.1}, 1}));
    inputUiElements.emplace_back(UiElementKey{width.key()},    width.init_widget(MinV<int>{-10000}, V<int>{500}, MaxV<int>{10000}, StepV<int>{1}));
    inputUiElements.emplace_back(UiElementKey{height.key()},   height.init_widget(MinV<int>{-10000}, V<int>{500}, MaxV<int>{10000}, StepV<int>{1}));
    inputUiElements.emplace_back(UiElementKey{pivotX.key()},  pivotX.init_widget({MinV<qreal>{-10.}, V<qreal>{0.5}, MaxV<qreal>{10.}, StepV<qreal>{0.01}, 2}));
    inputUiElements.emplace_back(UiElementKey{pivotY.key()},  pivotY.init_widget({MinV<qreal>{-10.}, V<qreal>{0.5}, MaxV<qreal>{10.}, StepV<qreal>{0.01}, 2}));
    inputUiElements.emplace_back(UiElementKey{rotation.key()}, rotation.init_widget("Rotation: "));
    rotation.set_steps({1.,1.,1.});

    return this;
}

WordSpaceCanvasSubPart::WordSpaceCanvasSubPart(){

    auto l = new QGridLayout();
    l->addWidget(ui::W::txt("<b>Size</b>"),     0, 0, 1, 6);
    l->addWidget(ui::W::txt("scale factor: "),  1, 0, 1, 1);
    l->addWidget(scaleFactor(),                 1, 1, 1, 1);
    l->addWidget(ui::W::txt("width: "),         1, 2, 1, 1);
    l->addWidget(width(),                       1, 3, 1, 1);
    l->addWidget(ui::W::txt("height: "),        1, 4, 1, 1);
    l->addWidget(height(),                      1, 5, 1, 1);

    l->addWidget(position.laTitle,  2, 0, 1, 6);
    l->addWidget(position.xText,    3, 0, 1, 1);
    l->addWidget(position.x(),      3, 1, 1, 1);
    l->addWidget(position.yText,    3, 2, 1, 1);
    l->addWidget(position.y(),      3, 3, 1, 1);
    l->addWidget(position.zText,    3, 4, 1, 1);
    l->addWidget(position.z(),      3, 5, 1, 1);

    l->addWidget(rotation.laTitle,  4, 0, 1, 6);
    l->addWidget(rotation.xText,    5, 0, 1, 1);
    l->addWidget(rotation.x(),      5, 1, 1, 1);
    l->addWidget(rotation.yText,    5, 2, 1, 1);
    l->addWidget(rotation.y(),      5, 3, 1, 1);
    l->addWidget(rotation.zText,    5, 4, 1, 1);
    l->addWidget(rotation.z(),      5, 5, 1, 1);

    frame = ui::F::gen_frame(l, {}, 0, LMarginsD{6,4,6,4,4}, QFrame::Shape::Box);
}

WordSpaceCanvasSubPart *WordSpaceCanvasSubPart::init_widget(){
    inputUiElements.emplace_back(UiElementKey{scaleFactor.key()}, scaleFactor.init_widget({MinV<qreal>{-1000.}, V<qreal>{0.25}, MaxV<qreal>{1000.}, StepV<qreal>{0.01}, 2}));
    inputUiElements.emplace_back(UiElementKey{width.key()}, width.init_widget(MinV<int>{-10000}, V<int>{400}, MaxV<int>{10000}, StepV<int>{1}));
    inputUiElements.emplace_back(UiElementKey{height.key()}, height.init_widget(MinV<int>{-10000}, V<int>{400}, MaxV<int>{10000}, StepV<int>{1}));
    inputUiElements.emplace_back(UiElementKey{position.key()}, position.init_widget("<b>Position</b>"));
    inputUiElements.emplace_back(UiElementKey{rotation.key()}, rotation.init_widget("<b>Rotation</b>"));
    rotation.set_steps({1.,1.,1.});
    position.set_values({0.,0.,10.});
    return this;
}

EyeRendererSubPart::EyeRendererSubPart(){
    frame = ui::F::gen(ui::L::HB(),{&t,eye()}, LStretch{false},LMargins{true});
}

EyeRendererSubPart *EyeRendererSubPart::init_widget(){
    ui::W::init_label(&t, "Eyes to render: ", true);
    inputUiElements.emplace_back(UiElementKey{eye.key()}, eye.init_widget({"Both eyes", "Left eye", "Right eye"}, Index{0}, true));
    return this;
}

void ConfigParametersSubPart::block_signals(bool state){
    for(auto &element : inputUiElements){
        element.second->blockSignals(state);
    }
}

//if(!noInputText){
//    inputUiElements.emplace_back(std::make_pair(baseName + "", richtext.init_widget("Use rich text", true)));
//    inputUiElements.emplace_back(std::make_pair(baseName + "", text.init_widget(defaultText)));
//    inputUiElements.emplace_back(std::make_pair(baseName + "_text_resource", resourceText.init_widget(Resource::Type::Text, "Text resource: ")));
//}

//inputUiElements.emplace_back(std::make_pair(baseName + "_wrap", wrapping.init_widget("Wrap text", true)));
//inputUiElements.emplace_back(std::make_pair(baseName + "_auto_size", automaticFontSize.init_widget("Automatic", false)));
//inputUiElements.emplace_back(std::make_pair(baseName + "_font_size", fontSize.init_widget(fontSizeSettings)));


TextSubPart::TextSubPart(QString name, bool removeInputText) :
    resourceText({name + "_text_resource"}),
    text({name + "_text"}),
    wrapping({name + "_wrap"}),
    richtext({name + "_rich_text"}),
    automaticFontSize({name + "_auto_size"}),
    fontSize({name + "_font_size"}),
    italic({name + "_italic"}),
    bold({name + "_bold"}),
    highlight({name + "_highlight"}),
    underline({name + "_under_line"}),
    none({name + "_normal"}),
    lowerCase({name + "_lower_case"}),
    upperCase({name + "_upper_case"}),
    alignment({name + "_alignment"}),
    paragraphSpacing({name + "_paragraph_spacing"}),
    lineSpacing({name + "_line_spacing"}),
    wordSpacing({name + "_word_spacing"}),
    characterSpacing({name + "_character_spacing"}),
    faceColor({name + "_face_color"}),
    outlineColor({name + "_outline_color"}),
    outlineWidth({name + "_outline_width"}),
    noInputText(removeInputText)
{

    // text
    textW = new QWidget();
    QVBoxLayout *textL = new QVBoxLayout();
    textW->setLayout(textL);
    textL->setContentsMargins(2,2,2,2);

    if(!noInputText){
        auto text1  = ui::F::gen(ui::L::HB(), {resourceText()}, LStretch{false}, LMargins{true}, QFrame::NoFrame);
        auto text2  = ui::F::gen(ui::L::HB(), {text()}, LStretch{false}, LMargins{true}, QFrame::NoFrame);
        auto text3  = ui::F::gen(ui::L::HB(), {ui::W::txt("Font size"), fontSize(), automaticFontSize()}, LStretch{true}, LMargins{true}, QFrame::NoFrame);
        textL->addWidget(ui::F::gen(ui::L::VB(), {ui::W::txt("Text"), text1, text2, text3, richtext(), wrapping()}, LStretch{true}, LMargins{true}, QFrame::Box));
    }else{
        textL->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("Font size"), fontSize(), automaticFontSize()}, LStretch{true}, LMargins{true}, QFrame::NoFrame));
    }
    textL->addStretch();

    // settings
    settingsW = new QWidget();
    QVBoxLayout *settingsL = new QVBoxLayout();
    settingsW->setLayout(settingsL);
    settingsL->setContentsMargins(2,2,2,2);

    auto style1 = ui::F::gen(ui::L::HB(), {none(), lowerCase(), upperCase()}, LStretch{true}, LMargins{false}, QFrame::NoFrame);
    auto style2 = ui::F::gen(ui::L::HB(), {italic(), bold(), highlight(), underline()}, LStretch{true}, LMargins{false}, QFrame::NoFrame);
    settingsL->addWidget(ui::F::gen(ui::L::VB(), {ui::W::txt("Style"), style1, style2}, LStretch{true}, LMargins{true}, QFrame::Box));

    auto spacing1 = ui::F::gen(ui::L::HB(), {ui::W::txt("Paragraph"),paragraphSpacing(),ui::W::txt("Line"), lineSpacing()}, LStretch{true}, LMargins{false}, QFrame::NoFrame);
    auto spacing2 = ui::F::gen(ui::L::HB(), {ui::W::txt("Word"),wordSpacing(),ui::W::txt("Character"), characterSpacing()}, LStretch{true}, LMargins{false}, QFrame::NoFrame);
    settingsL->addWidget(ui::F::gen(ui::L::VB(), {ui::W::txt("Spacing"), spacing1, spacing2}, LStretch{true}, LMargins{true}, QFrame::Box));

    auto colors = ui::F::gen(ui::L::HB(), {ui::W::txt("Text"),ui::W::txt("Face"),faceColor(), ui::W::txt("Outline"), outlineColor()}, LStretch{true}, LMargins{false}, QFrame::NoFrame);
    settingsL->addWidget(ui::F::gen(ui::L::VB(), {ui::W::txt("Colors"), colors}, LStretch{true}, LMargins{true}, QFrame::Box));
    settingsL->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("Outline width"), outlineWidth()}, LStretch{true}, LMargins{true}, QFrame::Box));
    settingsL->addWidget(ui::F::gen(ui::L::HB(), {ui::W::txt("Alignment"), alignment()}, LStretch{true}, LMargins{true}, QFrame::Box));
    settingsL->addStretch();
}

TextSubPart *TextSubPart::init_widget(QString defaultText){

    DsbSettings spacingSettings= {MinV<qreal>{-10.}, V<qreal>{0.}, MaxV<qreal>{10.}, StepV<qreal>{0.01}, 2};
    DsbSettings fontSizeSettings= {MinV<qreal>{0.5}, V<qreal>{25.}, MaxV<qreal>{150.}, StepV<qreal>{0.1}, 1};
    DsbSettings outlineSettings= {MinV<qreal>{0.}, V<qreal>{0.}, MaxV<qreal>{10.}, StepV<qreal>{0.01}, 2};

    inputUiElements.emplace_back(UiElementKey{paragraphSpacing.key()}, paragraphSpacing.init_widget(spacingSettings));
    inputUiElements.emplace_back(UiElementKey{lineSpacing.key()}, lineSpacing.init_widget(spacingSettings));
    inputUiElements.emplace_back(UiElementKey{wordSpacing.key()}, wordSpacing.init_widget(spacingSettings));
    inputUiElements.emplace_back(UiElementKey{characterSpacing.key()}, characterSpacing.init_widget(spacingSettings));
    inputUiElements.emplace_back(UiElementKey{faceColor.key()}, faceColor.init_widget("Select face color", QColor(0,0,0,255)));
    inputUiElements.emplace_back(UiElementKey{outlineColor.key()}, outlineColor.init_widget("Select outline color", QColor(0,0,0,255)));
    inputUiElements.emplace_back(UiElementKey{outlineWidth.key()}, outlineWidth.init_widget(outlineSettings));
    inputUiElements.emplace_back(UiElementKey{none.key()},none.init_widget("Normal", true));
    inputUiElements.emplace_back(UiElementKey{lowerCase.key()}, lowerCase.init_widget("Lower case", false));
    inputUiElements.emplace_back(UiElementKey{upperCase.key()}, upperCase.init_widget("Upper case", false));
    inputUiElements.emplace_back(UiElementKey{italic.key()}, italic.init_widget("Italic", false));
    inputUiElements.emplace_back(UiElementKey{bold.key()}, bold.init_widget("Bold", false));
    inputUiElements.emplace_back(UiElementKey{highlight.key()}, highlight.init_widget("Highlight", false));
    inputUiElements.emplace_back(UiElementKey{underline.key()}, underline.init_widget("Underline", false));
    inputUiElements.emplace_back(UiElementKey{alignment.key()}, alignment.init_widget({
        "Middle left","Middle right", "Middle justified", "Middle centered",
        "Bottom left","Bottom right", "Bottom justified", "Bottom centered",
        "Top left","Top right", "Top justified", "Top centered"},
        Index({3})
    ));

    if(!noInputText){
        inputUiElements.emplace_back(UiElementKey{richtext.key()}, richtext.init_widget("Use rich text", true));
        inputUiElements.emplace_back(UiElementKey{text.key()}, text.init_widget(defaultText));
        inputUiElements.emplace_back(UiElementKey{resourceText.key()}, resourceText.init_widget(Resource::Type::Text, "Text resource: "));
    }

    inputUiElements.emplace_back(UiElementKey{wrapping.key()}, wrapping.init_widget("Wrap text", true));
    inputUiElements.emplace_back(UiElementKey{automaticFontSize.key()}, automaticFontSize.init_widget("Automatic", false));
    inputUiElements.emplace_back(UiElementKey{fontSize.key()}, fontSize.init_widget(fontSizeSettings));

    return this;
}

