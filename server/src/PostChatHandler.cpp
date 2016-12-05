#include "PostChatHandler.h"
#include "ChatData.h"
#include "Logger.h"
#include <iostream>
using namespace std;
#define hasheoDatos(a,b,u) if(a.compare(b) <= 0){a.append(b);u.setUsername(a);}else{b.append(a);u.setUsername(b);} 
#define appendeoAlFinal(a,b,u) a.append(": "); a.append(b);    u.DBaddMensajes(a);

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
    hasheoDatos(username,username2,usu);
    Status s = usu.DBget();
    std::string frase = hmsg.getUriStringParsedByIndex(1);
    std::string response = hmsg.getCampo("mensaje");
    appendeoAlFinal(frase,rseponse,usu);
    

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
