
#ver docs.python-requests.org/en/latest/user/quickstart/

#funca con python 2.7, creo que en 3.0 cambiaron el print (por si a alguien no le anda)

"""
Si se corre este archivo solo, se corren las unit tests definidas en el mismo con unittest de python. No hace falta haber abierto el server (pero tiene q estar el ejecutable en /build)
Para correr las pruebas viejas que imprimen en pantalla, correr en una consola el server, y en otra llamar a los otros archivos (no a este)
"""

import requests
import json
import os
import time
import subprocess
import base64
import random
import threading
import sys

data = ""
path = os.getcwd()
path_files = path + '/files/'
verbose = False
#ip = "http://172.17.0.2:8000"
ip = "http://"
start_server = True
if len(sys.argv) > 1:
	if sys.argv[1] == 'docker':
		ip = 'http://172.17.0.2:8000'
	else:
		ip += sys.argv[1]
		sys.argv.remove(sys.argv[1])
		start_server = False
else:
	ip += "localhost:8000"

def create_user(username, password):
	data = json.dumps({'username':username, 'password': password})
	r = requests.post(ip+"/users/", data=data)
	if verbose:
		print "POST", r.url, data
		print "content:", r.content
		print
	else:
		return r

def log_in(username, password):
	data = json.dumps({'username':username, 'password':password})
	r = requests.post(ip+"/sessions/", data=data)
	if verbose:
		print "POST", r.url, data
		print "content:", r.content
		content_temp = json.loads(r.content)
		token = str(content_temp["conn_token"])
		print "token:", token
		print
		return token
	else:
		return r

def log_out(username, token):
	r = requests.delete(ip+"/sessions/"+username, headers={'conn_token' : token})
	if verbose:
		print "DELETE", r.url, data
		print "content:", r.content
		print
	else:
		return r

def delete_user(username, token):
	r = requests.delete(ip+"/users/"+username, headers={'conn_token' : token})
	if verbose:
		print "DELETE", r.url, data
		print "content:", r.content
		print
	else:
		return r

def get_user(username, token):
	r = requests.get(ip+"/users/"+username, headers={'conn_token' : token})
	json_respuesta = json.loads(r.content, strict = False)
	if "picture" in json_respuesta.keys():
		json_respuesta["picture"] = "devuelto_"+username+".jpg"
	if verbose:
		print "GET", r.url, data
		print "content:", json.dumps(json_respuesta)
		print
	else:
		return r


def modificar_perfil(username, token, email, picture, place, name):
	if(picture == ""):
		picture="Default.jpg"	
	pic = base64.b64encode(open(path_files+picture, mode='rb').read())
	data = json.dumps({'email':email, 'picture':pic, 'place':place, 'name':name})
	data2 = json.dumps({'email':email, 'picture':picture, 'place':place, 'name':name})
	r = requests.put(ip+"/users/"+username, data=data, headers={'conn_token' : token})
	if verbose:
		print "PUT", r.url, data2
		print "content:", r.content
		print
	else:
		return r

def add_skill(username,token,skill):
	data = json.dumps({'skillList':skill})
	r = requests.put(ip+"/users/"+username, data=data, headers={'conn_token' : token})
	if verbose:
		print "PUT", r.url, data
		print "content:", r.content
		print
	else:
		return r

def like(username,token,username2):
	data = json.dumps({'skillList':"nada"})
	r = requests.put(ip+"/like/"+username+"/"+username2, data=data, headers={'conn_token' : token})
	if verbose:
		print "PUT", r.url, data
		print "content:", r.content
		print
	else:
		return r


def dislike(username,token,username2):
	data = json.dumps({'skillList':"nada"})
	r = requests.delete(ip+"/like/"+username+"/"+username2, data=data, headers={'conn_token' : token})
	if verbose:
		print "DELETE", r.url, data
		print "content:", r.content
		print
	else:
		return r


def agregar_usuario(username, token, amigo):
	data = json.dumps({})

	r = requests.post(ip+"/users/"+username+"/addFriend/"+amigo, data=data, headers={'conn_token' : token})
	if verbose:
		print "POST", r.url, data
		print "content:", r.content
		print
	else:
		return r


def edito(username, token):
	data = json.dumps({'skillList':[{'name':username , 'description':'jaja','category':'orden'}]})
	r = requests.post(ip+"/users/"+username, data=data, headers={'conn_token' : token})
	if verbose:
		print "PUT", r.url, data
		print "content:", r.content
		print
	else:
		return r


def accept_user(username, token, amigo,resp):
	data = json.dumps({"response":resp})

	r = requests.post(ip+"/users/"+username+"/acceptFriend/"+amigo, data=data, headers={'conn_token' : token})
	if verbose:
		print "POST", r.url, data
		print "content:", r.content
		print
	else:
		return r

def topRankSkill():

	r = requests.get(ip+"/top_skill/[")

	
	print r.content
def topRankJob():

	r = requests.get(ip+"/top_job/[")

	
	print r.content
def topRank():

	r = requests.get(ip+"/top/")

	
	print r.content

def get_profile(username, token):

	r = requests.get(ip+"/users/"+username+"/profile/", headers={'conn_token' : token})

	json_respuesta = json.loads(r.content, strict=False);
	if "picture" in json_respuesta.keys():
		f = open(path_files+"devuelto_"+username+".jpg",'wb')
		f.write(base64.b64decode(json_respuesta["picture"]))
		f.close()
		json_respuesta["picture"] = "devuelto_"+username+".jpg"
	if verbose:
		print "GET", r.url, data
		print "content:", json.dumps(json_respuesta)
		print
	else:
		return r


import unittest

class TestServerIntegration(unittest.TestCase):

	server = ""

	# aca se deberia poner que arrance el server en modo debug (o nivel de log de debug), especialmente para ver cuantos threads corren en paralelo
	def setUp(self):
		if start_server:
			with open(os.devnull, 'w') as devnull:
				subprocess.Popen(args=["rm", "-rf", "/tmp/py_integration_tests/"], stdout=devnull)
				self.server = subprocess.Popen(args=[path+"/../build/Server",  "-db_path=/tmp/py_integration_tests"], stdout=devnull)
				devnull.close()
			time.sleep(1) # esto es medio feo, pero si no corre los tests antes de que se haya abierto posta el server, y fallan pq no les responde

	def tearDown(self):
		if start_server:
			self.server.terminate()
			with open(os.devnull, 'w') as devnull:
				subprocess.Popen(args=["rm", "-rf", "/tmp/py_integration_tests/"], stdout=devnull)
				devnull.close()	

	def test_multithreading(self):
		global num_requests
		users = ["mati", "gonzalo", "fede", "juam"]
		tokens = []
		stop_events = []
		num_requests = 0

		def do_stuff(num, stop_event):
			global num_requests
			while not stop_event.is_set():
				index = random.randint(0, len(users)-1)
				if index < len(users) and index < len(tokens):
					if num_requests < 1000:
						r = get_user(users[index], tokens[index])
						self.assertTrue(r.status_code == requests.codes.ok)
						num_requests += 1

		i = 0
		for user in users:
			r = create_user(user, user)
			self.assertTrue(r.status_code == 200)
			r = log_in(user, user)
			self.assertTrue(r.status_code == 200)
			response_json = json.loads(r.content, strict = False)
			self.assertTrue("conn_token" in response_json.keys())
			tokens.append(response_json["conn_token"])

			t_stop = threading.Event()
			stop_events.append(t_stop)
			t = threading.Thread(target=do_stuff, args=(i, t_stop))
			t.daemon = True
			t.start()
			i += 1

		while True:
			if num_requests > 1000:
				i = 0
				for user in users:
					stop_events[i].set()
				break
		i = 0
		for user in users:
			r = delete_user(user, tokens[i])
			i += 1

if __name__ == '__main__':
	unittest.main()
else:
	verbose = True


