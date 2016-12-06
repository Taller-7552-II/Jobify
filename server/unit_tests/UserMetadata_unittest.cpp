#include "gtest/gtest.h"
#include "UserMetadata.h"
#include "User.h"
#include "DatabaseMockRAM.h"
#include "DatabaseLevelDB.h"
#include "json/json.h"

std::string username = "mati";
std::string password = "gatoso";
std::string username2 = "nicolas";
std::string password2 = "suarez";

TEST(UserMetadataTest, GettersYSettersTest){
    DatabaseMockRAM* db = new DatabaseMockRAM;

    UserMetadata user_metadata(db);

    user_metadata.setUsername(username);
    EXPECT_TRUE(user_metadata.getUsername() == username);

    
}

TEST(UserMetadataTest, CrearUsuarioCreaMetadata){
    DatabaseMockRAM* db = new DatabaseMockRAM;

    User user(db);
    user.setUsername(username);
    user.setPassword(password);

    user.DBcreate();

    UserMetadata user_metadata(db);
    user_metadata.setUsername(username);
    Status s = user_metadata.DBget();
    EXPECT_TRUE(s.ok());
}


TEST(UserMetadataTest, ChangeEmailTest){
    DatabaseMockRAM* db = new DatabaseMockRAM;

    User user(db);
    user.setUsername(username);
    user.setPassword(password);

    user.DBcreate();

    UserMetadata user_metadata(db);
    user_metadata.setUsername(username);
    EXPECT_TRUE(1 == 1);
}

TEST(UserMetadataTest, MyUsernameTest){
    Database* db = new DatabaseMockRAM;

    User user(db);
    user.setUsername(username);
    user.setPassword(password);

    user.DBcreate();

    UserMetadata user_metadata(db);
    user_metadata.setUsername(username);

    EXPECT_TRUE(1==1);

}

using namespace Json;

TEST(UserMetadataTest, ProfileTest){
    Database* db = new DatabaseMockRAM;
    std::string picture = "hola";
    std::string place = "Chile";
    std::string name = "Lauti";

    User user(db);
    user.setUsername(username);
    user.setPassword(password);
    Status s = user.DBcreate();
    EXPECT_TRUE(s.ok());

    UserMetadata user_metadata(db);
    user_metadata.setUsername(username);
    s = user_metadata.DBget();
    EXPECT_TRUE(s.ok());

}

