#ifndef GETCHATHANDLER_H
#define GETCHATHANDLER_H

#include "EventHandlerIgnoresAuthentication.h"

//!Clase que devuelve el perfil de otros usuarios
/*!Ignora el token ya que deberian ser publicos los perfiles
*/

class GetChatHandler : public EventHandlerIgnoresAuthentication
{
    public:
        //!Funcion que inicializa la clase.
        /*!Recibe punteros a Database y a TokenAuthenticator y los guarda en db y auth.
        */
        GetChatHandler(Database *db,TokenAuthenticator *a);
        virtual ~GetChatHandler();
    protected:

    private:
        //!Funcion que maneja httprequests.
        /*!Extrae de la httprequest el nombre del chat a buscar y
        y luego busca su conversacion en la base de datos.
        */
        void _handle(HttpRequest& hmsg);
        bool isMyRequest(HttpRequest &hmsg);
};

#endif // GETCHATHANDLER_H
