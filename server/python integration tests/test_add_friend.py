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

user3 = 'matias2'
password = 'gguzeta'
email = 'mati.carballo91@gmail.com'
pic = 'Panchito.jpg'
name = 'Mati Carballo'
place = 'Argentina'
user4='gguzeta2'
password2='matias'

create_user(user3, password)
create_user(user4,password2)

token3 = log_in(user3, password)
token4 = log_in(user4,password2)


create_user(user, password)
create_user(user2,password2)

token = log_in(user, password)
token2 = log_in(user2,password2)

get_user(user, token)
#a intenta editar ambos perfiles
agregar_usuario(user, token, user2)
agregar_usuario(user, token, user2)
agregar_usuario(user, token, user4)
agregar_usuario(user, token, user4)
agregar_usuario(user, token, user3)
agregar_usuario(user, token, user3)
accept_user(user2,token2,user,"yes")
accept_user(user3,token3,user,"no")

#a intenta editar ambos perfiles
agregar_usuario(user, token, user2)
agregar_usuario(user, token, user3)
agregar_usuario(user, token, user4)

accept_user(user2,token2,user,"yes")
accept_user(user4,token4,user,"yes")
accept_user(user3,token3,user,"yes")






#mando notificacion
get_user(user,token)
get_user(user3,token3)
get_user(user4,token4)

get_user(user2,token2)




#borro b
delete_user(user,token)
#me borro
get_user(user3,token3)
delete_user(user2, token2)
delete_user(user3, token3)
delete_user(user4, token4)


print "/********************************************************************************"
print "/****************TEST*SERVER*****************************************************"
print "/********************************************************************************"