#include "gtest/gtest.h"
#include "LikeHandler.h"
#include "DatabaseMockRAM.h"
#include "HttpRequestConcrete.h"
#include "User.h"
#include "UserMetadata.h"

using namespace std;

TEST(LikeHandlerTests, LikeOK){
	Database* db = new DatabaseMockRAM;
	TokenAuthenticator* tk = new TokenAuthenticator;
	string token = tk->createToken("juampa");
	LikeHandler handler(db, tk);

	User user(db);
	user.setUsername("juampa");
	user.setPassword("qwerty");
	Status s = user.DBcreate();
	EXPECT_TRUE(s.ok());

	vector<string> header_names;
	header_names.push_back("conn_token");
	vector<string> header_values;
	header_values.push_back(token);
	struct mg_connection* conn = new struct mg_connection;
	struct http_message* hmsg = new_http_message("PUT", "/like/juampa/matias", "", &header_names, &header_values);


	HttpRequestConcrete req;
	req.init(conn, hmsg);

	handler.handle(req);
	EXPECT_TRUE(req.getStatusCode() == HttpRequest::OK);

	delete_http_message(hmsg);
	delete conn;
}
