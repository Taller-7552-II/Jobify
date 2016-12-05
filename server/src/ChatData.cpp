#include "ChatData.h"
#include "JsonSerializer.h"
#include <string>
#include "json/json.h"
#include "Database.h"
#include "Util.h"
#include "Logger.h"


using namespace Json;

ChatData::ChatData(Database* db, DatabaseWriteBatch* dbbatch) : DBElement(db, dbbatch)
{
}

ChatData::~ChatData()
{
    //dtor
}


void ChatData::_setKey(){
    this->key = this->username;
    this->key.append(".chattoken");
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Key seteada para abrir db", INFO);
    log->Log("ChatData : Key db : "+this->username+".chattoken", TRACE);
}

void ChatData::_setValueVars(){
    Reader reader;
    Value json_value;
    reader.parse(this->value, json_value);
    mensajes.clear();
    for(ValueIterator it = json_value["mensajes"].begin(); it != json_value["mensajes"].end(); ++it){
        addMensajes(JsonSerializer::removeBegAndEndQuotes((*it).asString()));
    }

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("ChatData : Values recuperados de la db", INFO);
    log->Log("ChatData : Values db : "+this->value, TRACE);
}

void ChatData::_setValue(){
    JsonSerializer serializer;

    std::string val_mensajes = "";
    serializer.turnVectorToArray(mensajes, "mensajes", val_mensajes);

    std::string val_json = "";
    serializer.joinValueIntoList(val_json, val_mensajes);
    serializer.turnObjectListToObject(val_json);
    this->value = val_json;

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Values serializados para la db", INFO);
    log->Log("ChatData : Values db : "+this->value, TRACE);
}
// asumo que me dieron el username correcto
Status ChatData::DBerase(){
    Status s;

    Server_Logger* log = Server_Logger::getInstance();

    s = this->DBget();
    if(!s.ok()){
        log->Log("No se encontro el user metadata en la db de "+this->username,ERROR);
        return s;
    }

    s = this->erase();
    log->Log("Se elimino la metadata de la db de"+this->username,INFO);
    return s;
}

Status ChatData::DBget(){
    Status s;

    s = this->get();
    if(s.IsNotFound()){
        return Status::NotFound("User not found");
    }

    return s;
}

Status ChatData::DBcreate(){
    Status s;

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Corrobora que el puntero db vaya a una base de datos",INFO);
    s = this->get();
    if(!s.IsNotFound()){
        //s = this->DBerase();
        log->Log("ChatData de "+this->username+" ya existe",WARNING);
        return Status::Corruption("el usuario ya existe");
    }


    s = this->put();
    // ver status
    return s;
}


Status ChatData::DBaddMensajes(std::string u) {
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    this->addMensajes(u);

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Agregando notificacion "+ u,INFO);
    s = this->put();
    // ver status
    return this->endBatch();
}



std::string ChatData::getProfile(){
    JsonSerializer serializer;

    std::string json_to_return = "";
    serializer.addValueToObjectList(json_to_return,"username",this->username);
    std::string val_mensajes = "";
    serializer.turnVectorToArray(mensajes, "mensajes", val_mensajes);
    serializer.joinValueIntoList(json_to_return, val_mensajes);

    serializer.turnObjectListToObject(json_to_return);

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Perfil de "+this->username+" es "+json_to_return,INFO);

    return json_to_return;

}
