#include "SendFriendRequestHandler.h"
#include "UserMetadata.h"
#include "Logger.h"
#include "Notifications.h"

SendFriendRequestHandler::SendFriendRequestHandler(Database *db, TokenAuthenticator *a) : EventHandlerChecksAuthentication(db, a)
{
    //ctor
}

SendFriendRequestHandler::~SendFriendRequestHandler()
{
    //dtor
}

bool SendFriendRequestHandler::isMyRequest(HttpRequest &hmsg){
    // POST /users/'username'/addFriend/'username2' quiere decir modificar perfil de tal usuario
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Verifica que se trate de un Handler tipo SendFriendRequestHandler",INFO);
    if(hmsg.getUriParsedByIndex(0) == HttpRequest::USERS &&
       hmsg.getUriParsedByIndex(2) == HttpRequest::ADD_FRIEND &&
        hmsg.getUriCantCampos() == 4 &&
        hmsg.getUriType() ==  HttpRequest::ELEMENT_URI &&
        hmsg.getMethod() == HttpRequest::POST){
        log->Log("Confirma que es un Handler tipo SendFriendRequestHandler",INFO);
        return true;
    }
    return false;
}

void SendFriendRequestHandler::_handle(HttpRequest &hmsg){
    Status s;

    Server_Logger* log = Server_Logger::getInstance();
    std::string username = hmsg.getUsername();
    log->Log("El campo recibido por username es : "+username,DEBUG);
    if(username == ""){
        hmsg.setResponse(Status::InvalidArgument(""));
        return;
    }

    std::string friend_username = hmsg.getUriStringParsedByIndex(3);
    log->Log("El campo recibido por friend_username es : "+friend_username,DEBUG);
    if(friend_username == ""){
        hmsg.setResponse(Status::InvalidArgument(""));
        return;
    }

    UserMetadata user_metadata(db);
    user_metadata.setUsername(friend_username);

    std::string notificacion = std::to_string(N_ADD_FRIEND) + "." + username;
    s = user_metadata.DBaddNotification(notificacion);

    // ver status
    if(s.ok()){
        hmsg.setResponse(s, "Notification sent");
    } else {
        hmsg.setResponse(s);
    }
}
