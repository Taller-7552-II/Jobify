#include "gtest/gtest.h"
#include "SignUpHandler.h"
#include "DatabaseMockRAM.h"
#include "HttpRequestConcrete.h"
#include "User.h"
#include "UserMetadata.h"

using namespace std;

TEST(SignUpHandlerTests, SignUpOK){
    Database* db = new DatabaseMockRAM;
    TokenAuthenticator* tk = new TokenAuthenticator;
    string token = tk->createToken("gonzalo");
    SignUpHandler handler(db, tk);

    struct mg_connection* conn = new struct mg_connection;
    struct http_message* hmsg = new_http_message("POST", "/users/","{\"username\":\"gonzalo\",\"password\":\"qwerty\"}");

    HttpRequestConcrete req;
    req.init(conn, hmsg);

    handler.handle(req);
    EXPECT_TRUE(req.getStatusCode() == HttpRequest::OK);

    User user(db);
    user.setUsername("gonzalo");
    user.setPassword("qwerty");
    Status s = user.DBget();
    EXPECT_TRUE(s.ok());

    delete_http_message(hmsg);
    delete conn;
}

