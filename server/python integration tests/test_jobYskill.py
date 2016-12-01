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

get_user(user, token)
#a intenta editar ambos perfiles
modificar_perfil(user, token, email, pic, place, name)
modificar_perfil(user2, token, email, pic, place, name)

add_skill(user,token,"mati")
#a ve perfil de b y viceversa
get_profile(user,token2)
get_profile(user2,token)
get_profile("Tom",token)
#borro b
delete_user(user2,token2)
get_user(user2, token2)
get_user(user2, token)
get_profile(user2,token)

#me deslogeo y verifico
log_out(user, token)
get_user(user, token)

#vuelvo a logear
token = log_in(user, password)
get_user(user, token)

#me borro
delete_user(user, token)
get_user(user, token)
get_profile(user2,token)
print "/********************************************************************************"
print "/****************TEST*SERVER*****************************************************"
print "/********************************************************************************"