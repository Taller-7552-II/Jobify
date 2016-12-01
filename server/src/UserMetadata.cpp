#include "UserMetadata.h"
#include "JsonSerializer.h"
#include <string>
#include "json/json.h"
#include "Database.h"
#include "Util.h"
#include "Logger.h"
#include "Notifications.h"

using namespace Json;

UserMetadata::UserMetadata(Database* db, DatabaseWriteBatch* dbbatch) : DBElement(db, dbbatch), join_date(""), email(""), ultima_ubicacion("")
{
   this->name="";
   this->email="";
   this->picture="";
   this->jobList="[]";
   this->skillList="[]";
   this->ultima_ubicacion="";
   this->resume="";
}

UserMetadata::~UserMetadata()
{
    //dtor
}


void UserMetadata::_setKey(){
    this->key = this->username;
    this->key.append(".usertoken");
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Key seteada para abrir db", INFO);
    log->Log("UserMetadata : Key db : "+this->username+".usertoken", TRACE);
}

void UserMetadata::_setValueVars(){
    Reader reader;
    Value json_value;
    reader.parse(this->value, json_value);

    setJoinDate(JsonSerializer::removeBegAndEndQuotes(json_value["join_date"].toStyledString()));
    changeEmail(JsonSerializer::removeBegAndEndQuotes(json_value["email"].toStyledString()));
    changeJobList(JsonSerializer::removeBegAndEndQuotes(json_value["jobList"].toStyledString()));
    changeSkillList(JsonSerializer::removeBegAndEndQuotes(json_value["skillList"].toStyledString()));


    changeUltimaUbicacion(JsonSerializer::removeBegAndEndQuotes(json_value["ultima_ubicacion"].toStyledString()));

    //changeNotificaciones(JsonSerializer::removeBegAndEndQuotes(json_value["notificaciones"].toStyledString()));
    //changeFriendList(JsonSerializer::removeBegAndEndQuotes(json_value["friendList"].toStyledString()));

    notificaciones.clear();
    for(ValueIterator it = json_value["notificaciones"].begin(); it != json_value["notificaciones"].end(); ++it){
        addNotificacion(JsonSerializer::removeBegAndEndQuotes((*it).asString()));
    }
    friendList.clear();
    for(ValueIterator it = json_value["friendList"].begin(); it != json_value["friendList"].end(); ++it){
        addFriend(JsonSerializer::removeBegAndEndQuotes((*it).asString()));
    }
   likeList.clear();
    for(ValueIterator it = json_value["likeList"].begin(); it != json_value["likeList"].end(); ++it){
        addLike(JsonSerializer::removeBegAndEndQuotes((*it).asString()));
    }


    changeName(JsonSerializer::removeBegAndEndQuotes(json_value["name"].toStyledString()));
    changePic(JsonSerializer::removeBegAndEndQuotes(json_value["picture"].toStyledString()));
    changeResume(JsonSerializer::removeBegAndEndQuotes(json_value["resume"].toStyledString()));

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("UserMetadata : Values recuperados de la db", INFO);
    log->Log("UserMetadata : Values db : "+this->value, TRACE);
}

void UserMetadata::_setValue(){
    JsonSerializer serializer;

    std::string val_date_joined = "";
    serializer.addValueToObjectList(val_date_joined, "join_date", join_date);
    std::string val_email = "";
    serializer.addValueToObjectList(val_email, "email", email);

    std::string val_resume = "";
    serializer.addValueToObjectList(val_resume, "resume", resume);

    std::string val_jobList = "";
    serializer.addValueToObjectList(val_jobList, "jobList", jobList);
    std::string val_skillList = "";
    serializer.addValueToObjectList(val_skillList, "skillList", skillList);

    std::string val_ultima_ubicacion = "";
    serializer.addValueToObjectList(val_ultima_ubicacion, "ultima_ubicacion", ultima_ubicacion);

    std::string val_notificaciones = "";
    serializer.turnVectorToArray(notificaciones, "notificaciones", val_notificaciones);
    std::string val_friendList = "";
    serializer.turnVectorToArray(friendList, "friendList", val_friendList);
    std::string val_likeList = "";
    serializer.turnVectorToArray(likeList, "likeList", val_likeList);


    std::string val_name = "";
    serializer.addValueToObjectList(val_name,"name",this->name);
    std::string val_pic = "";
    serializer.addValueToObjectList(val_pic,"picture",this->picture);

    std::string val_json = "";
    serializer.joinValueIntoList(val_json, val_date_joined);
    serializer.joinValueIntoList(val_json, val_email);
    serializer.joinValueIntoList(val_json, val_resume);
    serializer.joinValueIntoList(val_json, val_skillList);
    serializer.joinValueIntoList(val_json, val_jobList);
    serializer.joinValueIntoList(val_json, val_ultima_ubicacion);
    serializer.joinValueIntoList(val_json, val_notificaciones);
    serializer.joinValueIntoList(val_json, val_friendList);
    serializer.joinValueIntoList(val_json, val_likeList);
    serializer.joinValueIntoList(val_json,val_name);
    serializer.joinValueIntoList(val_json,val_pic);
    serializer.turnObjectListToObject(val_json);
    this->value = val_json;

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Values serializados para la db", INFO);
    log->Log("UserMetadata : Values db : "+this->value, TRACE);
}

void UserMetadata::removeNotification(std::string u) {
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Eliminando notificacion",INFO);
    notificaciones.erase(std::remove(notificaciones.begin(), notificaciones.end(), u), notificaciones.end());
}
void UserMetadata::removeLike(std::string u) {
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Eliminando Like",INFO);
    likeList.erase(std::remove(likeList.begin(), likeList.end(), u), likeList.end());
}

void UserMetadata::removeFriend(std::string u) {
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Eliminando amigo",INFO);
    friendList.erase(std::remove(friendList.begin(), friendList.end(), u), friendList.end());
}

// asumo que me dieron el username correcto
Status UserMetadata::DBerase(){
    Status s;

    Server_Logger* log = Server_Logger::getInstance();

    s = this->DBget();
    if(!s.ok()){
        log->Log("No se encontro el user metadata en la db de "+this->username,ERROR);
        return s;
    }

    for(int i = 0; i < friendList.size(); ++i) {
        std::string myfriend = friendList[i];
        UserMetadata friend_metadata(db);
        friend_metadata.setUsername(myfriend);
        s = friend_metadata.DBremoveFriend(this->username);
        // ver error
    }

    s = this->erase();
    log->Log("Se elimino la metadata de la db de"+this->username,INFO);
    return s;
}

Status UserMetadata::DBget(){
    Status s;

    s = this->get();
    if(s.IsNotFound()){
        return Status::NotFound("User not found");
    }

    return s;
}

Status UserMetadata::DBcreate(){
    Status s;

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Corrobora que el puntero db vaya a una base de datos",INFO);
    s = this->get();
    if(!s.IsNotFound()){
        //s = this->DBerase();
        log->Log("UserMetadata de "+this->username+" ya existe",WARNING);
        return Status::Corruption("el usuario ya existe");
    }

    this->setJoinDate(get_date_and_time());
    s = this->put();
    // ver status
    return s;
}



Status UserMetadata::DBchange_email(std::string n_email){
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Cambiando email "+this->email+" a "+n_email,INFO);

    this->changeEmail(n_email);
    s = this->put();
    // ver status
    return this->endBatch();
}

Status UserMetadata::DBchange_name(std::string new_name){
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Cambiando nombre "+this->name+" a "+new_name,INFO);

    this->name = new_name;
    s = this->put();
    // ver status
    return this->endBatch();
}


Status UserMetadata::DBchange_resume(std::string new_name){
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Cambiando nombre "+this->resume+" a "+new_name,INFO);

    this->resume = new_name;
    s = this->put();
    // ver status
    return this->endBatch();
}
//EDITE
Status UserMetadata::DBchange_skill_list(std::string new_pic){
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Cambiando foto",INFO);

    this->skillList = new_pic;
    s = this->put();
    // ver status
    return this->endBatch();
}
Status UserMetadata::DBchange_job_list(std::string new_pic){
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Cambiando foto",INFO);

    this->jobList = new_pic;
    s = this->put();
    // ver status
    return this->endBatch();
}

//EDITE FIN
Status UserMetadata::DBchange_profile_pic(std::string new_pic){
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Cambiando foto",INFO);

    this->picture = new_pic;
    s = this->put();
    // ver status
    return this->endBatch();
}

Status UserMetadata::DBchange_last_place(std::string new_place){
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    this->ultima_ubicacion = new_place;

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Cambiando ultima ubicacion "+this->ultima_ubicacion+" a "+new_place,INFO);
    s = this->put();
    // ver status
    return this->endBatch();
}

Status UserMetadata::DBchange_ultima_ubicacion(std::string new_place){
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();
    // ver status
    this->changeUltimaUbicacion(new_place);

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Cambiando ultima ubicacion "+this->ultima_ubicacion+" a "+new_place,INFO);
    s = this->put();
    // ver status
    return this->endBatch();
}

Status UserMetadata::DBaddNotification(std::string u) {
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    this->addNotificacion(u);

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Agregando notificacion "+ u,INFO);
    s = this->put();
    // ver status
    return this->endBatch();
}

Status UserMetadata::DBremoveNotification(std::string u) {
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    this->removeNotification(u);

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Borrando notificacion "+ u,INFO);
    s = this->put();
    // ver status
    return this->endBatch();
}

Status UserMetadata::DBaddFriend(std::string u, bool cyclic) {
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    this->addFriend(u);
    this->removeNotification(std::to_string(N_ADD_FRIEND) + "." + u);

    if(cyclic) {
        UserMetadata user_metadata(this->db);
        user_metadata.setUsername(u);
        s = user_metadata.DBaddFriend(this->username);
    }

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Agregando amigo 2" + u,INFO);
    s = this->put();
    // ver status
    return this->endBatch();
}

Status UserMetadata::DBremoveFriend(std::string u) {
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    this->removeFriend(u);

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Borrando amigo " + u,INFO);
    s = this->put();
    // ver status
    return this->endBatch();
}


Status UserMetadata::DBaddLike(std::string u) {
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    this->addLike(u);

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Agregando Like" + u,INFO);
    s = this->put();
    // ver status
    return this->endBatch();
}

Status UserMetadata::DBremoveLike(std::string u) {
    Status s;

    s = this->get();
    if(!s.ok())
        return s;

    this->startBatch();

    this->removeLike(u);

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Borrando amigo " + u,INFO);
    s = this->put();
    // ver status
    return this->endBatch();
}


std::string UserMetadata::getProfile(){
    JsonSerializer serializer;

    std::string json_to_return = "";
    serializer.addValueToObjectList(json_to_return,"username",this->username);
    serializer.addValueToObjectList(json_to_return,"name",this->name);
    serializer.addValueToObjectList(json_to_return,"picture",this->picture);
    serializer.addValueToObjectList(json_to_return,"email",this->email);
    serializer.addValueToObjectList(json_to_return,"place",this->ultima_ubicacion);
    serializer.addValueToObjectList(json_to_return,"jobList",this->jobList);//EDITE
    serializer.addValueToObjectList(json_to_return,"skillList",this->skillList);//EDITE
    serializer.addValueToObjectList(json_to_return,"resume",this->resume);//EDITE
    std::string val_friendList = "";
    serializer.turnVectorToArray(friendList, "friendList", val_friendList);
        std::string val_likeList = "";
    serializer.turnVectorToArray(likeList, "likeList", val_likeList);
    serializer.joinValueIntoList(json_to_return, val_likeList);

    serializer.turnObjectListToObject(json_to_return);

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Perfil de "+this->username+" es "+json_to_return,INFO);

    return json_to_return;

}
