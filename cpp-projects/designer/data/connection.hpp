
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// local
#include "component.hpp"
#include "states.hpp"

namespace tool::ex {

    struct Connection;
    using ConnectionUP = std::unique_ptr<Connection>;

    struct Connection{

        explicit Connection(ConnectionKey id) : key(IdKey::Type::Connection, id.v){
        }

        enum class Type{
            Component,Connector
        };

        static ConnectionUP copy_with_new_element_id(const Connection &connectionToCopy, std::unordered_map<int,int> keysMapping){

            ConnectionUP connection = std::make_unique<Connection>(ConnectionKey{-1});

            if(connectionToCopy.startType == Type::Component){
                connection->startKey = connectionToCopy.startKey;
            }else{
                connection->startKey = keysMapping[connectionToCopy.startKey];
            }

            if(connectionToCopy.endType == Type::Component){
                connection->endKey = connectionToCopy.endKey;
            }else{
                connection->endKey = keysMapping[connectionToCopy.endKey];
            }

            connection->startType       = connectionToCopy.startType;
            connection->endType         = connectionToCopy.endType;
            connection->startIndex      = connectionToCopy.startIndex;
            connection->endIndex        = connectionToCopy.endIndex;
            connection->slot            = connectionToCopy.slot;
            connection->signal          = connectionToCopy.signal;
            connection->startDataType   = connectionToCopy.startDataType;
            connection->endDataType     = connectionToCopy.endDataType;

            return connection;
        }

        inline QString to_string() const{
            return
                QSL("Connection(") % QString::number(key()) %
                QSL("|signal:") % signal % QSL("|startDataType:") % startDataType %
                QSL("|endDataType:")  % endDataType % QSL("|slot:") % slot % QSL(")");
        }

        Type startType;
        Type endType;

        int startKey;
        int endKey;

        int startIndex;
        int endIndex;

        QString slot;
        QString signal;

        QString startDataType;
        QString endDataType;

        IdKey key;

        bool selected = false;
    };

    // TODO: add component/connector pointers instead of id
    // TOOD: add integrity check here

    [[maybe_unused]] static bool operator==(const Connection &l, const Connection &r){
        return  (l.key()  == r.key());
    }

}






