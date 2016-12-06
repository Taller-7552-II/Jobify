#include "gtest/gtest.h"
#include "ChatData.h"
#include "DatabaseMockRAM.h"
#include "UserMetadata.h"

TEST(ChatDataTest, GettersYSettersTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;
	ChatData chatData(db);
	
	chatData.addMensajes("Hola");
	chatData.setUsername("matias");
	EXPECT_TRUE(chatData.getUsername() == "matias");
}

TEST(ChatDataTest, CrearTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	ChatData chatData(db);
	chatData.setUsername("gonzalo");

	Status s = chatData.DBcreate();
	EXPECT_TRUE(s.ok());
	s = chatData.DBcreate();
	EXPECT_FALSE(s.ok());
}

TEST(ChatDataTest, CrearChatDataCreaMetadata){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	ChatData chatData(db);
	chatData.setUsername("matias");

	Status s = chatData.DBcreate();
	EXPECT_TRUE(s.ok());

	UserMetadata um(db);
	um.setUsername("matias");
	s = um.DBget();
	EXPECT_FALSE(s.ok());
}

TEST(ChatDataTest, GetTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	ChatData chatData(db);
	chatData.setUsername("matias");

	Status s = chatData.DBget();
	EXPECT_FALSE(s.ok());

	s = chatData.DBcreate();
	EXPECT_FALSE(s.ok());

	s = chatData.DBget();
	EXPECT_TRUE(s.ok());
	EXPECT_TRUE(chatData.getUsername() == "matias");
}

TEST(UserTest, BorrarChatDataBorraMetadata){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	ChatData chatData(db);
	chatData.setUsername("gonzalo");

	Status s = chatData.DBcreate();
	EXPECT_TRUE(s.ok());

	UserMetadata um(db);
	um.setUsername("matias");
	s = um.DBget();
	EXPECT_FALSE(s.ok());
}
