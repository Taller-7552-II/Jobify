from server_test_func import *
import os

print "/********************************************************************************"
print "/***************INIT*TEST*FOTO***************************************************"
print "/********************************************************************************"

user = 'Tom'
password = 'calamardo'

create_user(user, password)
token = log_in(user, password)
get_user(user, token)

print "/********************************************************************************"
print "/****************FIN*TEST*FOTO***************************************************"
print "/********************************************************************************"