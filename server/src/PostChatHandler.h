#ifndef POSTCHATHANDLER_H
#define POSTCHATHANDLER_H

#include "EventHandlerIgnoresAuthentication.h"

//!Clase que devuelve el perfil de otros usuarios
/*!Ignora el token ya que deberian ser publicos los perfiles
*/

class PostChatHandler : public EventHandlerIgnoresAuthentication
{
    public:
        //!Funcion que inicializa la clase.
        /*!Recibe punteros a Database y a TokenAuthenticator y los guarda en db y auth.
        */
        PostChatHandler(Database *db,TokenAuthenticator *a);
        virtual ~PostChatHandler();
    protected:

    private:
        //!Funcion que maneja httprequests.
        /*!Extrae de la httprequest el nombre del chat a buscar y
        y luego busca su conversacion en la base de datos.
        */
        void _handle(HttpRequest& hmsg);
        bool isMyRequest(HttpRequest &hmsg);
};

#endif // POSTCHATHANDLER_H
