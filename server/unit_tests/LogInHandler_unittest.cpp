#include "gtest/gtest.h"
#include "LogInHandler.h"
#include "DatabaseMockRAM.h"
#include "HttpRequestConcrete.h"
#include "User.h"
#include "UserMetadata.h"
#include "json/json.h"
#include "JsonSerializer.h"

using namespace std;
using namespace Json;

TEST(LogInHandlerTests, LogInOK){
    Database* db = new DatabaseMockRAM;
    TokenAuthenticator* tk = new TokenAuthenticator;
    LogInHandler handler(db, tk);

    struct mg_connection* conn = new struct mg_connection;
    struct http_message* hmsg = new_http_message("POST", "/sessions/","{\"username\":\"gonzalo\", \"password\":\"qwerty\"}");

    HttpRequestConcrete req;
    req.init(conn, hmsg);

    User user(db);
    user.setUsername("gonzalo");
    user.setPassword("qwerty");
    Status s = user.DBcreate();
    EXPECT_TRUE(s.ok());

    handler.handle(req);
    EXPECT_TRUE(req.getStatusCode() == HttpRequest::OK);

    Reader reader;
    Value parsed_response;
    string str_response = req.getResponse();
    reader.parse(str_response.c_str(), parsed_response);
    JsonSerializer serializer;
    string token = "";
    token = serializer.get(parsed_response, "conn_token", "", parsed_response, token);
    EXPECT_TRUE(tk->isValidToken("gonzalo", token));

    delete_http_message(hmsg);
    delete conn;
}

TEST(LogInHandlerTests, LogInWrongPassword){
    Database* db = new DatabaseMockRAM;
    TokenAuthenticator* tk = new TokenAuthenticator;
    LogInHandler handler(db, tk);

    struct mg_connection* conn = new struct mg_connection;
    struct http_message* hmsg = new_http_message("POST", "/sessions/","{\"username\":\"gonzalo\", \"password\":\"qwerty\"}");

    HttpRequestConcrete req;
    req.init(conn, hmsg);

    User user(db);
    user.setUsername("gonzalo");
    user.setPassword("ytrewq");
    Status s = user.DBcreate();
    EXPECT_TRUE(s.ok());

    handler.handle(req);
    EXPECT_FALSE(req.getStatusCode() == HttpRequest::OK);

    delete_http_message(hmsg);
    delete conn;
}

TEST(LogInHandlerTests, LogInUserWrongUser){
    Database* db = new DatabaseMockRAM;
    TokenAuthenticator* tk = new TokenAuthenticator;
    LogInHandler handler(db, tk);

    struct mg_connection* conn = new struct mg_connection;
    struct http_message* hmsg = new_http_message("POST", "/sessions/","{\"username\":\"gonzalo\", \"password\":\"qwerty\"}");

    HttpRequestConcrete req;
    req.init(conn, hmsg);

    handler.handle(req);
    EXPECT_FALSE(req.getStatusCode() == HttpRequest::OK);

    delete_http_message(hmsg);
    delete conn;
}

