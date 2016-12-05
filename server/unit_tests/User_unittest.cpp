#include "gtest/gtest.h"
#include "User.h"
#include "DatabaseMockRAM.h"
#include "UserMetadata.h"

TEST(UserTest, GettersYSettersTest){
    DatabaseMockRAM* db = new DatabaseMockRAM;
    User user(db);
    user.setUsername("gonzalo");
    EXPECT_TRUE(user.getUsername() == "gonzalo");
    user.setPassword("qwerty");
    EXPECT_TRUE(user.getPassword() == "qwerty");
}

TEST(UserTest, CrearTest){
    DatabaseMockRAM* db = new DatabaseMockRAM;

    User user(db);
    user.setUsername("gonzalo");
    user.setPassword("qwerty");

    Status s = user.DBcreate();
    EXPECT_TRUE(s.ok());
    s = user.DBcreate();
    EXPECT_FALSE(s.ok());
}

TEST(UserTest, CrearUsuarioCreaMetadata){
    DatabaseMockRAM* db = new DatabaseMockRAM;

    User user(db);
    user.setUsername("gonzalo");
    user.setPassword("qwerty");
    Status s = user.DBcreate();
    EXPECT_TRUE(s.ok());

    UserMetadata um(db);
    um.setUsername("gonzalo");
    s = um.DBget();
    EXPECT_TRUE(s.ok());
}

TEST(UserTest, GetTest){
    DatabaseMockRAM* db = new DatabaseMockRAM;

    User user(db);
    user.setUsername("gonzalo");

    Status s = user.DBget();
    EXPECT_FALSE(s.ok());

    user.setPassword("qwerty");
    user.reSync();
    s = user.DBcreate();
    EXPECT_TRUE(s.ok());
    user.setPassword("ytrewq");
    user.reSync();
    s = user.DBget();
    EXPECT_TRUE(s.ok());
    EXPECT_TRUE(user.getPassword() == "qwerty");
}

TEST(UserTest, EraseTest){
    DatabaseMockRAM* db = new DatabaseMockRAM;

    User user(db);
    user.setUsername("gonzalo");
    user.setPassword("qwerty");

    Status s = user.DBerase();
    EXPECT_FALSE(s.ok());
    s = user.DBcreate();
    EXPECT_TRUE((db->get(user)).ok());
    s = user.DBerase();
    EXPECT_FALSE((db->get(user)).ok());
}

TEST(UserTest, BorrarUsuarioBorraMetadata){
    DatabaseMockRAM* db = new DatabaseMockRAM;

    User user(db);
    user.setUsername("gonzalo");
    user.setPassword("qwerty");
    Status s = user.DBcreate();
    EXPECT_TRUE(s.ok());

    UserMetadata um(db);
    um.setUsername("gonzalo");
    s = um.DBget();
    EXPECT_TRUE(s.ok());

    s = user.DBerase();
    EXPECT_FALSE((db->get(user)).ok());
    um.reSync();
    s = um.DBget();
    EXPECT_FALSE(s.ok());
}