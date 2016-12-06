#!/bin/bash

echo "Checkeando existencia de docker"
if ! which docker > /dev/null; then
	echo "Docker no se encuentra instalado. Se precisa de su instalacion para poder correr el script. Consultar http://docs.docker.com/engine/installation/ubuntulinux/ para poder instalarlo"
	exit
fi

echo "Docker se encuentra instalado. Procediendo a ejecutar server como daemon"
sudo docker pull matisyo/jobify-docker:latest
sudo docker run -d --add-host="localhost:10.0.0.2" matisyo/jobify-docker:latest
cd /home/user
git clone https://github.com/Taller-7552-II/Jobify
cd Jobify
cd server
chmod +x build.sh
./build.sh

 

echo "ID proceso:"
sudo docker ps | grep "matisyo/jobify-docker"

echo "IP a conectarse: 172.17.0.2:8000"

echo "Para detener el server correr :~$ sudo docker stop <container-id>"
