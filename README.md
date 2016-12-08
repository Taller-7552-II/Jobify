# Taller de Programacion 2 - Jobify


Trabajo Practico - Taller de Programacion II - 2do cuatrimestre 2016

##Integrantes
* [Corballo Matias](https://github.com/matisyo) 93762
* [Guzzardi Gonzalo](https://github.com/gonzaloguzzardi) 94258
* [Marshall Juan Patricio](https://github.com/JuanPatricioMarshall) 95471

##Travis Integration
[![Build Status](https://travis-ci.org/Taller-7552-II/Jobify.svg?branch=master)

##Code Coverage
[![Coverage Status](https://coveralls.io/repos/github/Taller-7552-II/Jobify/badge.svg)](https://coveralls.io/github/Taller-7552-II/Jobify)

============================================================================================================
Manual de instalación y uso para el Servidor
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

Generar documentacion html con doxygen
------------------------------------------------------------------------------------------------------------
Se debe estar situado en la carpeta server/src. Va a generar una carpeta html (donde hay que abrir el index.html) y una carpeta con la documentacion en latex (para pasarlo a un pdf, hay que hacer " $ make pdf " en consola)

.. code-block:: bash
   
   $ sudo apt-get install doxygen
   $ doxygen Doxyfile
 

