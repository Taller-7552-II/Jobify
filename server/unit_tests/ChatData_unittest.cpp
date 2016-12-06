#include "gtest/gtest.h"
#include "ChatData.h"
#include "DatabaseMockRAM.h"

TEST(UserTest, GettersYSettersTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;
	ChatData chatData(db);
	
	chatData.addMensajes("Hola");
	chatData.setUsername("gonzalo");
	EXPECT_TRUE(chatData.getUsername() == "gonzalo");
}
