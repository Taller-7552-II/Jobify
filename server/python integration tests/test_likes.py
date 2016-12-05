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
user3='gguzeta2'

user4='gguzeta3'




create_user(user, password)
create_user(user2,password2)
create_user(user3, password2)
create_user(user4,password2)

token = log_in(user, password)
token2 = log_in(user2,password2)
token3 = log_in(user3,password2)
token4 = log_in(user4,password2)

edito(user,token)

like(user2,token,user)
like(user3,token,user)
like(user4,token,user)
dislike(user3,token,user)
like(user2,token,user3);

topRank()
topRankJob()
topRankSkill()
get_user(user, token)
get_profile(user,token2)
get_profile(user2,token)

get_profile("Tom",token2)

#borro b
delete_user(user,token)
delete_user(user2,token2)
get_profile("Tom",token2)
delete_user(user3,token3)
delete_user(user4,token4)
get_profile("Tom",token2)
print "/********************************************************************************"
print "/****************TEST*SERVER*****************************************************"
print "/********************************************************************************"