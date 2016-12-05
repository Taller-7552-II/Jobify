#include "JobGetHandler.h"
#include "UserMetadata.h"
#include "Logger.h"
#include "HerokuComHandler.h"
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>

JobGetHandler::JobGetHandler(Database *db, TokenAuthenticator *a) : EventHandlerIgnoresAuthentication(db, a)
{
    //ctor
}

JobGetHandler::~JobGetHandler()
{
    //dtor
}

bool JobGetHandler::isMyRequest(HttpRequest &hmsg){
    // GET /job/'categoria' quiere decir pedir info del usuario
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Verifica que se trate de un Handler tipo JobGetHandler",INFO);
    if(hmsg.getUriParsedByIndex(0) == HttpRequest::JOB &&
        hmsg.getUriCantCampos() <= 2 &&
        hmsg.getUriType() ==  HttpRequest::ELEMENT_URI &&
        hmsg.getMethod() == HttpRequest::GET){
        log->Log("Confirma que es un Handler tipo JobGetHandler",INFO);
        return true;
    }
    return false;
}

void JobGetHandler::_handle(HttpRequest &hmsg){
    Status s = Status::OK();

    if(hmsg.getUriCantCampos() ==1){

        std::string url2("http://jobify-professional.herokuapp.com/");

        HerokuComHandler comandanteChocolateFortTipaso2;


        char* izard="";
        url2.append("job_positions/");




        char *cstr2 = new char[url2.length() + 1];
        strcpy(cstr2, url2.c_str());


        izard=comandanteChocolateFortTipaso2.GET(cstr2);


        std::string loco2(izard);
        hmsg.setResponse(Status::OK(), loco2);
    return;
    }
    std::string categoria = hmsg.getUriStringParsedByIndex(1);

    Server_Logger* log = Server_Logger::getInstance();
    log->Log("El campo recibido por categoria es : "+categoria,DEBUG);
    if(categoria == ""){
        hmsg.setResponse(Status::InvalidArgument(""));
        return;
    }

    std::string url("http://jobify-professional.herokuapp.com/");

    HerokuComHandler comandanteChocolateFortTipaso;

    char* mander="";
    url.append("job_positions/categories/");
    url.append(categoria);



    char *cstr = new char[url.length() + 1];
    strcpy(cstr, url.c_str());


    mander=comandanteChocolateFortTipaso.GET(cstr);



    if(!s.ok()){
        hmsg.setResponse(Status::InvalidArgument("El request recibido no es valido"));
        return;
    }
    std::string loco(mander);
    hmsg.setResponse(Status::OK(), loco);
}
