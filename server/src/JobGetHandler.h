#ifndef JOBGETHANDLER_H
#define JOBGETHANDLER_H

#include "EventHandlerIgnoresAuthentication.h"

//!Clase handler que obtiene un usuario.
/*!Hereda de EventHandlerChecksAuthentication.
*/
class JobGetHandler : public EventHandlerIgnoresAuthentication
{
    public:
        //!Funcion que inicializa la clase.
        /*!Recibe punteros a Database y a TokenAuthenticator al divino boton pero queda poco tiempo
        */
        JobGetHandler(Database *db, TokenAuthenticator *a);
        virtual ~JobGetHandler();

    protected:
    private:
        //!Funcion que maneja httprequests.
        /*!Extrae de la httprequest la categoria filtro y la busca en el heroku
        */
        void _handle(HttpRequest &hmsg);
        bool isMyRequest(HttpRequest &hmsg);
};

#endif // JOBGETHANDLER_H
