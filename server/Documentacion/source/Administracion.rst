=======================================
Administración
=======================================

Manual de instalación
============================================================================================================

La aplicación Jobify está pensada para correr en linux 64 bits. A su vez se requieren tener ciertas librerías y programas instalados.
Por esto se pueden proseguir dos métodos distintos con la intención de ejecutar el servidor.
Si se desea instalar las librerías y programas sobre el equipo y luego correr el servidor sobre estas instalaciones se puede seguir la guía de instalación sobre el equipo.


Instalación en Equipo
============================================================================================================

La aplicación Jobify está pensada para correr en linux 64 bits. A su vez se requieren tener ciertas librerías y programas instalados.
Esta guía de instalación detalla como conseguir esto, orientando las consignas para la versión Ubuntu 14.04. Sin embargo esto debería poder funcionar con otras versiones de Ubuntu y ser análoga a otras versiones de Linux.


CMake
------------------------------------------------------------------------------------------------------------
En caso de no tener cmake instalado:

.. code-block:: bash
   
	$ sudo apt-get update
	$ sudo apt-get install cmake


Clonando el github
------------------------------------------------------------------------------------------------------------
Primero se debe clonar nuestro github, usando el siguiente comando:

.. code-block:: bash

	$ git clone https://github.com/Taller-7552-II/Jobify

En el caso de no tener git instalado:
   
.. code-block:: bash

        $ sudo apt-get install git


Compilando el server
------------------------------------------------------------------------------------------------------------
Para compilar  el servidor hay que situarse en la carpeta /server/ y correr el script build.sh

.. code-block:: bash

   $ cd server/
   $ ./build.sh

Corriendo el server
------------------------------------------------------------------------------------------------------------
Para correr el servidor hay que situarse en la carpeta /server/build/ y ejecutar ./Server. Si se quiere cambiar el directorio donde se va a crear la base de datos, -Ddb_path,/home/mi_path. Tambien se puede cambiar el puerto de la siguiente manera, -Dport,:8000. A continuacion se mostrará un ejemplo de un server abierto en el puerto 8080 con la base de datos en /home/new_path

.. code-block:: bash

   $ cd server/
   $ ./build.sh -Ddb_path,/home/new_path -Dport,:8080



Correr tests de python
------------------------------------------------------------------------------------------------------------
Situado en la carpeta /server/python\ integration\ tests, correr el script test_server_func.py. Esto ejecutara los test de integracion de python. Se debe tener instalado python 2.7

.. code-block:: bash

   $ python server_test.py


Correr unit test del server
------------------------------------------------------------------------------------------------------------
Se debe estar situado en la carpeta server. Para correr las unit test se debe haber compilado el server con ./build.sh. A su vez, se debe tener instalado lcov y coveralls-lcov. De no ser el caso, correr el script install-coveralls. Luego se podrá correr el script run_tests.sh el cual ejecuta todas las unit test.

.. code-block:: bash
   
   $ ./build.sh
   $ sudo ./install_coveralls
   $ ./run_tests.sh

Correr coverage del server
------------------------------------------------------------------------------------------------------------
Se debe estar situado en la carpeta server. Para correr el coverage se debe haber compilado el server con ./build.sh. A su vez, se debe tener instalado lcov y coveralls-lcov. De no ser el caso, correr el script install-coveralls como root. Luego se podrá correr el script run_coverage.sh el cual ejecuta todas las unit test y se realiza el coverage del server.

.. code-block:: bash
   
   $ ./build.sh
   $ sudo ./install_coveralls
   $ ./run_coverage.sh


Ejecución en Equipo
============================================================================================================

Corriendo el server
=================================================================================================
Para correr el servidor hay que situarse en la carpeta /server/build/ y ejecutar ./Server. Si se quiere cambiar el directorio donde se va a crear la base de datos, -Ddb_path,/home/mi_path. Tambien se puede cambiar el puerto de la siguiente manera, -Dport,:8000. A continuacion se mostrará un ejemplo de un server abierto en el puerto 8080 con la base de datos en /home/new_path

.. code-block:: bash

   $ cd server/
   $ ./build.sh -Ddb_path,/home/new_path -Dport,:8080



Otras opciones
==================================================================================================

Correr tests de python
------------------------------------------------------------------------------------------------------------
Situado en la carpeta /server/python\ integration\ tests, correr el script test_server_func.py. Esto ejecutara los test de integracion de python. Se debe tener instalado python 2.7

.. code-block:: bash

   $ python server_test.py


Correr unit test del server
------------------------------------------------------------------------------------------------------------
Se debe estar situado en la carpeta server. Para correr las unit test se debe haber compilado el server con ./build.sh. A su vez, se debe tener instalado lcov y coveralls-lcov. De no ser el caso, correr el script install-coveralls. Luego se podrá correr el script run_tests.sh el cual ejecuta todas las unit test.

.. code-block:: bash
   
   $ ./build.sh
   $ sudo ./install_coveralls
   $ ./run_tests.sh

Correr coverage del server
------------------------------------------------------------------------------------------------------------
Se debe estar situado en la carpeta server. Para correr el coverage se debe haber compilado el server con ./build.sh. A su vez, se debe tener instalado lcov y coveralls-lcov. De no ser el caso, correr el script install-coveralls como root. Luego se podrá correr el script run_coverage.sh el cual ejecuta todas las unit test y se realiza el coverage del server.

.. code-block:: bash
   
   $ ./build.sh
   $ sudo ./install_coveralls
   $ ./run_coverage.sh


Mantenimiento
============================================================================================================

El mantenimiento del Server de Jobify es un aspecto de suma importancia para el correcto funcionamiento del sistema. Para esto se deben considerar dos factores:
					+ La base de datos
					+ El Log

La base de datos es una parte fundamental en cuento al desarrollo del sistema ya que es la encargada de mantener todos los archivos y datos de los usuarios. Esta suele encontrarse en la carpeta /tmp/prod/ pero puede cambiarse su ubicación como fue indicado en la sección  Instalación , más especificamente en "Corriento el Server". Si se cambia de directorio base, los datos no se trasladan así que al hacer este cambio se debe tener en cuenta que se tiene una base de datos nueva.


Base de Datos
<<<<<<<<<<<<<<<<
Como se aclaró anteriormente, la base de datos se encarga de guardar usuarios y chats al mismo tiempo, además de las sesiones. La manera de identificar rapidamente con que tipo de dato estamos tratando es al ver la clave que poseen en la base de datos. Los elementos de la base de datos son:

			+ User : (clave : "$username") Guarda el nombre de usuario y su contraseña.
			+ User Metadata : (clave : "$username.usertoken") : Guarda todos los datos del usuario, desde el perfil hasta la cantidad de archivos que tiene y cuales puede acceder.
			+ Chat Data : (clave : "usernameusername2)") : Guarda una lista de mensajes del chat entre 2 usuarios en el orden que llegaron 
 

Log
<<<<<<<<
Dentro de la carpeta *build* se encuentra un archivo llamado log.txt en el cual se encuentran todas las actividades importantes que debe realizar el servidor. A medida que se agregan funcionalidades o se actualiza el código es fundamental seguir logeando para poder detectar errores o fallas en el server. 


Known Issues
================================================================================================
Si el servidor se cae mientras corre el cliente, el cliente no se entera que el server murió

