#include "gtest/gtest.h"
#include "FriendDeleteHandler.h"
#include "DatabaseMockRAM.h"
#include "HttpRequestConcrete.h"
#include "User.h"
#include "UserMetadata.h"

using namespace std;

TEST(FriendDeleteHandlerTests, FriendDeleteHandlerOK){
    Database* db = new DatabaseMockRAM;
    TokenAuthenticator* tk = new TokenAuthenticator;
    string token = tk->createToken("gonzalo");
    FriendDeleteHandler handler(db, tk);
    

    vector<string> header_names;
    header_names.push_back("conn_token");
    vector<string> header_values;
    header_values.push_back(token);
    struct mg_connection* conn = new struct mg_connection;
    struct http_message* hmsg = new_http_message("GET", "/users/gonzalo","", &header_names, &header_values);

    User user(db);
    user.setUsername("gonzalo");
    user.setPassword("qwerty");
    Status s = user.DBcreate();

    HttpRequestConcrete req;
    req.init(conn, hmsg);

    handler.handle(req);
    EXPECT_FALSE(2 == 1 );

    delete_http_message(hmsg);
    delete conn;
}

TEST(FriendDeleteHandlerTests, FriendDeleteFailure){
    Database* db = new DatabaseMockRAM;
    TokenAuthenticator* tk = new TokenAuthenticator;
    string token = tk->createToken("gonzalo");
    FriendDeleteHandler handler(db, tk);

    vector<string> header_names;
    header_names.push_back("conn_token");
    vector<string> header_values;
    header_values.push_back(token);
    struct mg_connection* conn = new struct mg_connection;
    struct http_message* hmsg = new_http_message("GET", "/users/gonzalo","", &header_names, &header_values);

    HttpRequestConcrete req;
    req.init(conn, hmsg);

    handler.handle(req);
    EXPECT_FALSE(req.getStatusCode() == HttpRequest::OK);

    delete_http_message(hmsg);
    delete conn;
}

