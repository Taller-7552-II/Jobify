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

std::string email = "matute@yopmail.com";
std::string location = "loc";
std::string fecha = "fecha";
std::string resumen = "Mi resumen";

TEST(UserMetadataTest, GettersYSettersTest){
    DatabaseMockRAM* db = new DatabaseMockRAM;

    UserMetadata user_metadata(db);

    user_metadata.setUsername(username);
    EXPECT_TRUE(user_metadata.getUsername() == username);

	user_metadata.setJoinDate(fecha);
	EXPECT_TRUE(user_metadata.getJoinDate() == fecha);

	user_metadata.changeEmail(email);
	EXPECT_TRUE(user_metadata.getEmail() == email);

	user_metadata.changeUltimaUbicacion(location);
	EXPECT_TRUE(user_metadata.getUltimaUbicacion() == location);

	user_metadata.changeResume(resumen);

	user_metadata.changeJobList("jobs");
	EXPECT_TRUE(user_metadata.jobList.empty() == false);

	user_metadata.changeSkillList("skills");
	EXPECT_TRUE(user_metadata.skillList.empty() == false);

	user_metadata.addNotificacion("notification");

	user_metadata.removeNotification("notification");

	user_metadata.addFriend("juampa");

	user_metadata.removeFriend("juampa");

	user_metadata.addLike("mati");
	std::vector<std::string>* likeList = user_metadata.getLikeList();
	EXPECT_TRUE(likeList->empty() == false);

	user_metadata.removeLike("mati");

	user_metadata.changeName("Horacio");

	user_metadata.changePic("super foto");

	EXPECT_TRUE(user_metadata.likeList.empty() == true);
    
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

TEST(UserMetadataTest, BorrarUsuarioTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	User user(db);
	user.setUsername(username);
	user.setPassword(password);
	Status s = user.DBcreate();
	EXPECT_TRUE(s.ok());

	User user2(db);
	user2.setUsername(username2);
	user2.setPassword(password2);
	s = user2.DBcreate();
	EXPECT_TRUE(s.ok());

	UserMetadata um2(db);
	um2.setUsername(username2);
	s = um2.DBget();
	EXPECT_TRUE(s.ok());

	s = user.DBerase();
	EXPECT_TRUE(s.ok());
	um2.reSync();
	s = um2.DBget();
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
	Status s = user_metadata.DBchange_email(email);
	s = user_metadata.DBget();
	EXPECT_TRUE(user_metadata.getEmail() == email);
}

TEST(UserMetadataTest, ChangeProfilePicTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	User user(db);
	user.setUsername(username);
	user.setPassword(password);

	user.DBcreate();

	UserMetadata user_metadata(db);
	user_metadata.setUsername(username);
	Status s = user_metadata.DBchange_profile_pic("picture");
	s = user_metadata.DBget();
	EXPECT_TRUE(s.ok());
}

TEST(UserMetadataTest, ChangeNameTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	User user(db);
	user.setUsername(username);
	user.setPassword(password);

	user.DBcreate();

	UserMetadata user_metadata(db);
	user_metadata.setUsername(username);
	Status s = user_metadata.DBchange_name("Horacio");
	EXPECT_TRUE(s.ok());
}

TEST(UserMetadataTest, ChangeUltimaUbicacionTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	User user(db);
	user.setUsername(username);
	user.setPassword(password);

	user.DBcreate();

	UserMetadata user_metadata(db);
	user_metadata.setUsername(username);
	Status s = user_metadata.DBchange_last_place("nuevaUbicacion");
	s = user_metadata.DBget();
	EXPECT_TRUE(user_metadata.getUltimaUbicacion() == "nuevaUbicacion");
}

TEST(UserMetadataTest, ChangeResumeTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	User user(db);
	user.setUsername(username);
	user.setPassword(password);

	user.DBcreate();

	UserMetadata user_metadata(db);
	user_metadata.setUsername(username);
	Status s = user_metadata.DBchange_resume("resumen");
	EXPECT_TRUE(s.ok());
}

TEST(UserMetadataTest, ChangeSkillListTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	User user(db);
	user.setUsername(username);
	user.setPassword(password);

	user.DBcreate();

	UserMetadata user_metadata(db);
	user_metadata.setUsername(username);
	Status s = user_metadata.DBchange_skill_list("skills");
	EXPECT_TRUE(s.ok());
}

TEST(UserMetadataTest, ChangeJobsListTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	User user(db);
	user.setUsername(username);
	user.setPassword(password);

	user.DBcreate();

	UserMetadata user_metadata(db);
	user_metadata.setUsername(username);
	Status s = user_metadata.DBchange_job_list("jobs");
	EXPECT_TRUE(s.ok());
}

TEST(UserMetadataTest, AddAndRemoveNotificationTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	User user(db);
	user.setUsername(username);
	user.setPassword(password);

	user.DBcreate();

	UserMetadata user_metadata(db);
	user_metadata.setUsername(username);
	Status s = user_metadata.DBaddNotification("nuevaNotificacion");
	EXPECT_TRUE(s.ok());
	s = user_metadata.DBremoveNotification("nuevaNotificacion");
	EXPECT_TRUE(s.ok());
}

TEST(UserMetadataTest, AddAndRemoveFriendTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	User user(db);
	user.setUsername(username);
	user.setPassword(password);

	user.DBcreate();

	UserMetadata user_metadata(db);
	user_metadata.setUsername(username);
	Status s = user_metadata.DBaddFriend("nuevoAmigo");
	EXPECT_TRUE(s.ok());
	s = user_metadata.DBremoveFriend("nuevoAmigo");
	EXPECT_TRUE(s.ok());
}

TEST(UserMetadataTest, AddAndRemoveLikeTest){
	DatabaseMockRAM* db = new DatabaseMockRAM;

	User user(db);
	user.setUsername(username);
	user.setPassword(password);

	user.DBcreate();

	UserMetadata user_metadata(db);
	user_metadata.setUsername(username);
	Status s = user_metadata.DBaddLike("like");
	EXPECT_TRUE(s.ok());
	s = user_metadata.DBremoveLike("like");
	EXPECT_TRUE(s.ok());
}

using namespace Json;

TEST(UserMetadataTest, ProfileTest){
    Database* db = new DatabaseMockRAM;
    std::string picture = "picture";
    std::string place = "Arg";
    std::string name = "Juampa";

    User user(db);
    user.setUsername(username);
    user.setPassword(password);
    Status s = user.DBcreate();
    EXPECT_TRUE(s.ok());

    UserMetadata user_metadata(db);
    user_metadata.setUsername(username);
    s = user_metadata.DBget();
    EXPECT_TRUE(s.ok());

	s = user_metadata.DBchange_email(email);
	EXPECT_TRUE(s.ok());
	s = user_metadata.DBchange_profile_pic("foto");
	EXPECT_TRUE(s.ok());
	s = user_metadata.DBchange_last_place("lugar");
	EXPECT_TRUE(s.ok());
	s = user_metadata.DBchange_name("nombre");
	EXPECT_TRUE(s.ok());

	Reader reader;
	Value response_parsed;
	std::string profile = user_metadata.getProfile();

	reader.parse(profile.c_str(), response_parsed);
	EXPECT_TRUE(response_parsed["email"] == email);
	EXPECT_TRUE(response_parsed["picture"] == "foto");
	EXPECT_TRUE(response_parsed["name"] == "nombre");
	EXPECT_TRUE(response_parsed["place"] == "lugar");

}
