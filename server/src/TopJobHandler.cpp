#include "TopJobHandler.h"
#include "UserMetadata.h"
#include "Logger.h"
#include "HerokuComHandler.h"
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>

TopJobHandler::TopJobHandler(Database *db, TokenAuthenticator *a) : EventHandlerIgnoresAuthentication(db, a)
{
    //ctor
}

TopJobHandler::~TopJobHandler()
{
    //dtor
}

bool TopJobHandler::isMyRequest(HttpRequest &hmsg){
    // GET /top/ quiere decir pedir info del usuario
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Verifica que se trate de un Handler tipo TopJobHandler",INFO);
    if( (hmsg.getUriParsedByIndex(0) == HttpRequest::TOP_JOB ||
         hmsg.getUriParsedByIndex(0) == HttpRequest::TOP_SKILL )&&
        hmsg.getUriCantCampos() == 2 &&
        hmsg.getMethod() == HttpRequest::GET){
        log->Log("Confirma que es un Handler tipo TopJobHandler",INFO);
        return true;
    }
    return false;
}

void TopJobHandler::_handle(HttpRequest &hmsg){
    Status s = Status::OK();

    std::string job = hmsg.getUriStringParsedByIndex(1);

    std::string chit = hmsg.getUriStringParsedByIndex(0);

    UserMetadata user(db);
    user.setUsername("Tom");
    user.DBget();
    std::vector<std::string> lista = user.likeList;
    std::vector<int> vec;
    std::vector<std::string>  names;
    bool salir = true;
    for(int i=0; i<lista.size();i++){
        UserMetadata use2r(db);
        use2r.setUsername(lista[i]);
        use2r.DBget();

        std::string::size_type    chec = use2r.jobList.find(job);

        if(chit.compare("top_skill")==0){
            chec = use2r.skillList.find(job);
        }

        if (chec != std::string::npos){
            salir = false;
            std::vector<std::string> lista2  = use2r.likeList;
            vec.push_back(lista2.size());
            names.push_back(lista[i]);
        }
    }


     while( !salir){
            salir = true;
       for(int i=0;i< lista.size()-1;i++){
            if(vec[i+1]>vec[i]){
                salir = false;
                int aux = vec[i+1];
                std::string aux2 = names[i+1];
                vec[i+1] =  vec[i];
                names[i+1] = names[i];
                vec[i]=aux;
                names[i] =aux2;
            }
        }

    }

    std::string loco("{\"Global\": [\"");
    int aux = 10;
    if(aux>names.size()){
        aux=names.size();
    }
    for(int i =0;i<aux;i++){
        loco.append(names[i]);
        loco.append("\":");
        loco.append(std::to_string(vec[i]));

        if(i<aux-1){
            loco.append(",\"");
        }

    }
    loco.append("]}");
    hmsg.setResponse(Status::OK(), loco);
}
