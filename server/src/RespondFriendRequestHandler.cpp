#include "RespondFriendRequestHandler.h"
#include "UserMetadata.h"
#include "Logger.h"
#include "Notifications.h"
#include <iostream>

RespondFriendRequestHandler::RespondFriendRequestHandler(Database *db, TokenAuthenticator *a) : EventHandlerChecksAuthentication(db, a)
{
    //ctor
}

RespondFriendRequestHandler::~RespondFriendRequestHandler()
{
    //dtor
}

bool RespondFriendRequestHandler::isMyRequest(HttpRequest &hmsg){
    // POST /users/'username'/acceptFriend/'username2' quiere decir modificar perfil de tal usuario
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Verifica que se trate de un Handler tipo RespondFriendRequestHandler",INFO);
    if(hmsg.getUriParsedByIndex(0) == HttpRequest::USERS &&
       hmsg.getUriParsedByIndex(2) == HttpRequest::ACCEPT_FRIEND &&
        hmsg.getUriCantCampos() == 4 &&
        hmsg.getUriType() ==  HttpRequest::ELEMENT_URI &&
        hmsg.getMethod() == HttpRequest::POST){
        log->Log("Confirma que es un Handler tipo RespondFriendRequestHandler",INFO);
        return true;
    }
    return false;
}

void RespondFriendRequestHandler::_handle(HttpRequest &hmsg){
    Status s;

    Server_Logger* log = Server_Logger::getInstance();
    std::string username = hmsg.getUsername();
    log->Log("El campo recibido por username es : "+username,DEBUG);
    if(username == ""){
        hmsg.setResponse(Status::InvalidArgument(""));
        return;
    }

    std::string username2 = hmsg.getUriStringParsedByIndex(3);
    log->Log("El campo recibido por username2 es : " + username2, DEBUG);
    if(username2 == ""){
        hmsg.setResponse(Status::InvalidArgument(""));
        return;
    }

    std::string response = hmsg.getCampo("response");
    log->Log("El campo recibido por response es : "+response,DEBUG);

    UserMetadata user_metadata(db);
    user_metadata.setUsername(username);
    if(response.compare("yes") == 0) {
        s = user_metadata.DBaddFriend(username2, true);
    } else {
        s = user_metadata.DBremoveNotification(std::to_string(N_ADD_FRIEND) + "." + username2);
    }

    // ver status
    if(s.ok()){
        hmsg.setResponse(s, "Request answered");
    } else {
        hmsg.setResponse(s);
    }
}
