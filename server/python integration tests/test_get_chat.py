from server_test_func import *
import os

print "/********************************************************************************"
print "/******************TEST*SERVER***************************************************"
print "/********************************************************************************"

user = 'matias'
password = 'gguzeta'
email = 'mati.carballo91@gmail.com'
pic = 'Panchito.jpg'
name = 'Mati Carballo'
place = 'Argentina'
user2='gguzeta'
password2='matias'


create_user(user, password)
create_user(user2,password2)

token = log_in(user, password)
token2 = log_in(user2,password2)
print "jaja"
get_chat(user,user2)

agregar_usuario(user, token, user2)
accept_user(user2,token2,user,"yes")

get_chat(user,user2)
post_chat(user,user2,"hola")
post_chat(user,user2,"como va")
post_chat(user2,user,"bien y vos?")
delete_user(user, token)
delete_user(user2, token2)


get_chat(user,user2)
print "/********************************************************************************"
print "/****************TEST*CHAT*****************************************************"
print "/********************************************************************************"