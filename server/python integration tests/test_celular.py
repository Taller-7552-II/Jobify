from server_test_func import *
import os

print "/********************************************************************************"
print "/***************INIT*TEST*FOTO***************************************************"
print "/********************************************************************************"

user = 'm@m.com'
password = 'gguzeta'
email = 'mati.carballo91@gmail.com'
pic = 'Panchito.jpg'
name = 'Mati Carballo'
place = 'Argentina'
user2='gguzeta'
password2='matias'


create_user(user, password)
token = log_in(user, password)
get_user(user, token)

create_user(user2,password2)
token2 = log_in(user2,password2)

modificar_perfil(user,token,'gonzaloguzzardi@gmail.com','','Trumplandia','Gonzalo Guzzardi')
modificar_perfil(user,token2,'gonzaloguzzardi@gmail.com',pic,'Trumplandia','Gonzalo Guzzardi')
get_profile(user,token)
get_profile(user,token2)
modificar_perfil(user2,token2,'gonzaloguzzardi@gmail.com',pic,'Trumplandia','Gonzalo Guzzardi')
get_profile(user2,token2)
print "/********************************************************************************"
print "/****************FIN*TEST*FOTO***************************************************"
print "/********************************************************************************"