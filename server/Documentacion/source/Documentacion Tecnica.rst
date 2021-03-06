=======================================================
Documentación Técnica Servidor
=======================================================

Ambiente de desarrollo
======================

Servidor
--------

Para el desarrollo del servidor, se utilizó `Codeblocks <https://codeblocks.org>`_ .

Sin embargo, más allá de su uso para facilitar el desarrollo, la compilación se hizo siempre a partir de `cmake <https://cmake.org/>`_.

Librerías
===========================================================


Para manejar distintos recursos en el proceso de desarrollo se emplearon librerías open source.

Servidor http
---------------------------------------------------------------------

Para realizar las operaciones para manejar el servidor http se empleó `mongoose <https://github.com/cesanta/mongoose>`_, el cual facilitó en gran medida el manejo de http requests.


Base de datos
---------------------------------------------------------------------

Para el manejo de la base de datos por parte del servidor, se utilizó una base de datos no relacional del tipo *clave/valor* llamada `leveldb <https://github.com/google/leveldb>`_.


Datos json
---------------------------------------------------------------------

Para la manipulación de datos json se hizo uso de la librerías `jsoncpp <https://github.com/open-source-parsers/jsoncpp>`_. Los json se usaron tanto para el envío de datos a través de los mensajes http como en la persistencia de datos del lado del servidor.


Diseño
===========================================================

Para poder visualizar la arquitectura del proyecto se presenta aquí un diagrama UML que muestra las clases más importantes del programa.


.. figure:: diagrama/ServerDiagrama.png
	:scale: 100%



Aquí se puede ver como Server es quien se encarga de mantener la conexión, pero HandlerManager es la clase que maneja todas las httprequests, seleccionando cada handler acorde a la acción que deba hacer. A su vez, cada handler empleará los DBElements que necesite par subir, modificar o extraer datos de la clase Database, que es quien se encarga de manejar la base de datos.


Documentación de REST API
==============================================================================


Endpoints validos
------------------------------------------------------------------------------


        * POST /users/ sign up
        * POST /sessions/ login
        * DELETE /sessions/ logout
        * DELETE /users/ borrar usuario
        * GET /users/'username' traer info del usuario
        * PUT /users/'username' modificar perfil de tal usuario
        * PUT /like/'username'/'username2' like del 1er usuario al 2do
        * DELETE /like/'username'/'username2' dislike del 1er usuario al 2do
        * POST /users/'username'/addFriend/'username2' manda solicitud de amistad username a username2
        * POST /users/'username'/acceptFriend/'username2' username acepta la solicitud de amistad de username2
        * GET /top_skill/ devuelve el skill con mayor ranking
        * GET /top_job/ devuelve el job con mayor ranking
        * GET /users/'username'/profile/ trae el perfil del usuario username
        * GET /chat/'username'/'username2' trae el chat entre el username y el username2
        * POST /chat/'username'/'username2' postea un mensaje al chat


Otros
-----------------------------------------------------------------------------
    * cualquier otro request es invalido, y se devuelve error
