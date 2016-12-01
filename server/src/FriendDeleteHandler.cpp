#include "FriendDeleteHandler.h"
#include "UserMetadata.h"
#include "Logger.h"

FriendDeleteHandler::FriendDeleteHandler(Database *db, TokenAuthenticator *a) : EventHandlerChecksAuthentication(db, a)
{
    //ctor
}

FriendDeleteHandler::~FriendDeleteHandler()
{
    //dtor
}

bool FriendDeleteHandler::isMyRequest(HttpRequest &hmsg){
    // DELETE /users/'username'/delete/'otrouser' quiere decir borrar el usuario
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Verifica que se trate de un Handler tipo FriendDelete",INFO);
    if(hmsg.getUriParsedByIndex(0) == HttpRequest::USERS &&
       hmsg.getUriParsedByIndex(2) == HttpRequest::DELETE_FRIEND &&
        hmsg.getUriCantCampos() == 4 &&
        hmsg.getUriType() ==  HttpRequest::ELEMENT_URI &&
        hmsg.getMethod() == HttpRequest::DELETE){
        log->Log("Confirma que es un Handler tipo FriendDelete",INFO);
        return true;
    }
    return false;
}

void FriendDeleteHandler::_handle(HttpRequest &hmsg){
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
    UserMetadata user(db);
    user.setUsername(username);
    s = user.DBremoveFriend(username2);
    // devolver mensaje de error

    if(s.ok()){
        hmsg.setResponse(s, "Friend deleted successfully");
    }

    hmsg.setResponse(s);
}
