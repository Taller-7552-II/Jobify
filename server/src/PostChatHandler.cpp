#include "PostChatHandler.h"
#include "ChatData.h"
#include "Logger.h"
#include <iostream>
using namespace std;
PostChatHandler::PostChatHandler(Database* db , TokenAuthenticator* a) : EventHandlerIgnoresAuthentication(db,a)
{
    //ctor
}

bool PostChatHandler::isMyRequest(HttpRequest &hmsg){
    // POST /chat/'username'/'username2'

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Verifica que se trate de un Handler tipo PostChatHandler",INFO);
    if(hmsg.getUriParsedByIndex(0) == HttpRequest::CHAT &&
        hmsg.getUriCantCampos() == 3 &&
        hmsg.getMethod() == HttpRequest::POST){
        log->Log("Confirma que es un Handler tipo PostChatHandler",INFO);
        return true;
    }
    return false;
}

void PostChatHandler::_handle(HttpRequest& hmsg){

    std::string username = hmsg.getUsername();
    if(username == ""){
        hmsg.setResponse(Status::InvalidArgument(""));
        return;
    }

    ChatData usu(db);
    usu.setUsername(username);

    std::string username2 = hmsg.getUriStringParsedByIndex(2);
    

    if(username.compare(username2) <= 0){username.append(username2);usu.setUsername(username);}else{username2.append(username);usu.setUsername(username2);} 

    Status s = usu.DBget();
    std::string frase = hmsg.getUriStringParsedByIndex(1);
    std::string response = hmsg.getCampo("mensaje");
    
    frase.append(": "); frase.append(response);    usu.DBaddMensajes(frase);

    
    

    Server_Logger* log = Server_Logger::getInstance();
    if(s.ok())
        hmsg.setResponse(s,usu.getProfile());
    else{
        log->Log("No se encontro el CHAT",WARNING);
        hmsg.setResponse(s,"chat not found");
    }
}

PostChatHandler::~PostChatHandler()
{
    //dtor
}
