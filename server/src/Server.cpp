#include "Server.h"
#include <iostream>
#include "HttpRequestConcrete.h"

Server* Server::open_server = NULL;

Server::Server(std::string db_path, bool create_if_missing, bool clean_on_start)
{
    // levantar exepcion si ya fue seteada 'open_server'
    server_mgr = new struct mg_mgr;
    handlerManager = new HandlerManager(db_path, create_if_missing, clean_on_start);
    mg_mgr_init(server_mgr, this);
    active = false;
}

Server::~Server()
{
    if(active){
        stop();
    }
}

void Server::poll(){
    mg_mgr_poll(server_mgr, 1000);
}

void Server::stop(){
    active = false;
    mg_mgr_free(server_mgr);
}

bool Server::createListeningConnection(const char * addr){
    //tal vez guardar la mg_connection como var de clase? todavia no se si hace falta
    struct mg_connection* nc = mg_bind(server_mgr, addr, Server::staticHandler);
    if(nc == NULL){ //error
        return false;
    }
    mg_set_protocol_http_websocket(nc);
    mg_enable_multithreading(nc);
    Server::open_server = this;

    return true;
}

//int count = 0;
void Server::staticHandler(struct mg_connection *nc, int ev, void* ev_data){
    Server* server_m = Server::open_server;
    server_m->handler(nc, ev, ev_data);
}

void Server::handler(struct mg_connection* nc, int ev, void* ev_data){
    int connect_status;
    struct http_message* hmsg = (struct http_message*) ev_data;
    HttpRequestConcrete req;

    std::string content = "";

    switch(ev){
        case MG_EV_HTTP_REQUEST:
            req.init(nc, hmsg);
            handlerManager->handle(req);

            content.append(req.getResponse());

            mg_printf(nc, "HTTP/1.1 %d\r\n"
                            "Transfer-Encoding: chunked\r\n"
                            "\r\n", req.getStatusCode());
            mg_printf_http_chunk(nc, "%s", content.c_str());
            mg_send_http_chunk(nc, "", 0);
            break;
        default:
            break;
    }
}
