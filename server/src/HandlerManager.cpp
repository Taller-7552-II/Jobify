#include "HandlerManager.h"

#include "DatabaseLevelDB.h"
#include <iostream>
#include <string>
#include "json/json.h"
#include "SignUpHandler.h"
#include "LogInHandler.h"
#include "LogOutHandler.h"
#include "UserGetHandler.h"
#include "UserDeleteHandler.h"
#include "UserModifyHandler.h"
#include "UserGetProfileHandler.h"
#include "FriendDeleteHandler.h"
#include "DisLikeHandler.h"
#include "LikeHandler.h"
#include "SendFriendRequestHandler.h"
#include "RespondFriendRequestHandler.h"
#include "TopRankGetHandler.h"
#include "GetChatHandler.h"
#include "JobGetHandler.h"
#include "TopJobHandler.h"
#include "SkillGetHandler.h"
#include "PostChatHandler.h"
#include "DefaultHandler.h"
#include "Logger.h"


HandlerManager::HandlerManager(std::string db_path, bool create_if_missing, bool clean_on_start)
{
	db = new DatabaseLevelDB();
	db->config(db_path, create_if_missing, clean_on_start);
	db->open(); // se abre al principio y queda asi o se abre y cierra para procesar cada pedido?

	auth = new TokenAuthenticator();

    /// EL NUMERO DE HANDLERS TIENE QUE COINCIDIR CON LOS ENMUS EN EL .H
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Se comienza a llenar la lista de Handlers del HandlerManager",INFO);
    handlers.push_back(new SignUpHandler(db, auth));
	handlers.push_back(new LogInHandler(db, auth));
	handlers.push_back(new LogOutHandler(db, auth));
	handlers.push_back(new UserGetHandler(db, auth));
	handlers.push_back(new UserDeleteHandler(db, auth));
	handlers.push_back(new UserModifyHandler(db, auth));
	handlers.push_back(new UserGetProfileHandler(db,auth));
	handlers.push_back(new SendFriendRequestHandler(db,auth));
	handlers.push_back(new LikeHandler(db,auth));
	handlers.push_back(new DisLikeHandler(db,auth));
	handlers.push_back(new RespondFriendRequestHandler(db,auth));
	handlers.push_back(new JobGetHandler(db, auth));
	handlers.push_back(new FriendDeleteHandler(db, auth));
	handlers.push_back(new SkillGetHandler(db, auth));
	handlers.push_back(new TopRankGetHandler(db, auth));
	handlers.push_back(new TopJobHandler(db, auth));
	handlers.push_back(new GetChatHandler(db, auth));
	handlers.push_back(new PostChatHandler(db, auth));
	handlers.push_back(new DefaultHandler(db, auth)); // este tiene q ir ultimo pq acepta cualquier uri
	log->Log("Se inicializo correctamente el HandlerManager",INFO);
}

HandlerManager::~HandlerManager()
{
    for(std::vector<EventHandler*>::iterator it = handlers.begin(); it != handlers.end(); ++it){
		EventHandler* temp = *it;
		handlers.erase(it);
		delete temp;
	}
}

/// USERS
    /// COLLECTION
        // POST /users/ quiere decir sign up
        // GET /users/'username'/profile/
    /// ELEMENT
        // GET /users/'username' quiere decir pedir info del usuario
        // DELETE /users/'username' quiere decir borrar el usuario
        // PUT /users/'username' quiere decir modificar perfil de tal usuario

/// SESSIONS
    /// COLLECTION
        // POST /sessions/ quiere decir log in
    /// ELEMENT
        // DELETE /sessions/'username' quiere decir log out
/// OTHER
    // cualquier otro request es invalido, y se devuelve error

void HandlerManager::handle(HttpRequest &hmsg){
    Server_Logger* log = Server_Logger::getInstance();
    log->Log("Se busca que handler debe manejar la request",INFO);
    for(int i = 0; i < handlers.size(); ++i){
        //std::cout << i << std::endl;
        if(handlers[i]->handle(hmsg)) break;
    }
}

