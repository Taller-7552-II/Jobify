#include "DisLikeHandler.h"
#include "UserMetadata.h"
#include "Logger.h"
#include <iostream>
DisLikeHandler::DisLikeHandler(Database *db, TokenAuthenticator *a) : EventHandlerIgnoresAuthentication(db, a)
{
    //ctor
}

DisLikeHandler::~DisLikeHandler()
{
    //dtor
}

bool DisLikeHandler::isMyRequest(HttpRequest &hmsg){
    // DELETE /users/'username'/delete/'otrouser' quiere decir borrar el usuario
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Verifica que se trate de un Handler tipo DisLikeHandler",INFO);
    if(hmsg.getUriParsedByIndex(0) == HttpRequest::LIKE &&
        hmsg.getUriCantCampos() == 3 &&
        hmsg.getUriType() ==  HttpRequest::ELEMENT_URI &&
        hmsg.getMethod() == HttpRequest::DELETE){
        log->Log("Confirma que es un Handler tipo DisLikeHandler",INFO);
        return true;
    }
    return false;
}

void DisLikeHandler::_handle(HttpRequest &hmsg){
    Status s;

    Server_Logger* log = Server_Logger::getInstance();
    std::string username = hmsg.getUsername();
    log->Log("El campo recibido por username es : "+username,DEBUG);
    if(username == ""){
        hmsg.setResponse(Status::InvalidArgument(""));
        return;
    }

    std::string username2 = hmsg.getUriStringParsedByIndex(2);
    log->Log("El campo recibido por username2 es : " + username2, DEBUG);
    if(username2 == ""){
        hmsg.setResponse(Status::InvalidArgument(""));
        return;
    }
    UserMetadata user(db);
    user.setUsername(username2);
    s = user.DBremoveLike(username);
    // devolver mensaje de error

    if(s.ok()){
        hmsg.setResponse(s, "Dislike! successfully");
    }

    hmsg.setResponse(s);
}
