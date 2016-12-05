#include "TopRankGetHandler.h"
#include "UserMetadata.h"
#include "Logger.h"
#include "HerokuComHandler.h"
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>

TopRankGetHandler::TopRankGetHandler(Database *db, TokenAuthenticator *a) : EventHandlerIgnoresAuthentication(db, a)
{
    //ctor
}

TopRankGetHandler::~TopRankGetHandler()
{
    //dtor
}

bool TopRankGetHandler::isMyRequest(HttpRequest &hmsg){
    // GET /top/ quiere decir pedir info del usuario
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Verifica que se trate de un Handler tipo TopRankGetHandler",INFO);
    if(hmsg.getUriParsedByIndex(0) == HttpRequest::TOP &&
        hmsg.getUriCantCampos() <= 1 &&
        hmsg.getMethod() == HttpRequest::GET){
        log->Log("Confirma que es un Handler tipo TopRankGetHandler",INFO);
        return true;
    }
    return false;
}

void TopRankGetHandler::_handle(HttpRequest &hmsg){
    Status s = Status::OK();

    UserMetadata user(db);
    user.setUsername("Tom");
    user.DBget();
    std::vector<std::string> lista = user.likeList;
    std::vector<int> vec;
    std::vector<std::string>  names;

    for(int i=0; i<lista.size();i++){
        UserMetadata use2r(db);
        use2r.setUsername(lista[i]);
        use2r.DBget();
        std::vector<std::string> lista2  = use2r.likeList;
        vec.push_back(lista2.size());
        names.push_back(lista[i]);
        std::cout << lista[i] << std::endl;
    }

    bool salir = false;
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
        std::cout << loco << std::endl;
        if(i<aux-1){
            loco.append(",\"");
        }

    }
    loco.append("]}");
    hmsg.setResponse(Status::OK(), loco);
}
