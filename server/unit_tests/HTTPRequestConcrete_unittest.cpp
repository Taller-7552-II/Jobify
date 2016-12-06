#include "gtest/gtest.h"
#include "HttpRequestConcrete.h"
#include "json/json.h"

using namespace std;
using namespace leveldb;
using namespace Json;

TEST(HttpRequestConcreteTests, InitOK){
	struct mg_connection* conn = new struct mg_connection;
	struct http_message* hmsg = new_http_message("GET", "users/", "");

	HttpRequestConcrete req;
	req.init(conn, hmsg);

	delete_http_message(hmsg);
}


TEST(HttpRequestConcreteTests, getUri){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;

	struct http_message* hmsg = new_http_message("GET", "/users/", "");
	req.init(conn, hmsg);
	EXPECT_TRUE(req.getUri().compare("/users/") == 0);
	delete_http_message(hmsg);

}

TEST(HttpRequestConcreteTests, getUriParsed){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;
	vector<string> parsed;

	struct http_message* hmsg = new_http_message("GET", "users/matias", "");
	req.init(conn, hmsg);
	req.getUriParsed(&parsed);
	EXPECT_TRUE(parsed[0] == "users");
	EXPECT_TRUE(parsed[1] == "matias");
	delete_http_message(hmsg);

	parsed.clear();
}

TEST(HttpRequestConcreteTests, getUriParsedByIndex){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;

	struct http_message* hmsg = new_http_message("GET", "users/matias", "");
	req.init(conn, hmsg);
	EXPECT_TRUE(req.getUriParsedByIndex(0) == HttpRequest::USERS);
	EXPECT_TRUE(req.getUriParsedByIndex(1) == HttpRequest::INVALID_URI_FIELD);
	delete_http_message(hmsg);

	hmsg = new_http_message("POST", "/sessions/", "");
	req.init(conn, hmsg);
	EXPECT_TRUE(req.getUriParsedByIndex(0) == HttpRequest::SESSIONS);
	delete_http_message(hmsg);

	hmsg = new_http_message("GET", "users/matias/profile/", "");
	req.init(conn, hmsg);
	EXPECT_FALSE(req.getUriParsedByIndex(0) == HttpRequest::PROFILE);
	delete_http_message(hmsg);
}

TEST(HttpRequestConcreteTests, getUriStringParsedByIndex){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;

	struct http_message* hmsg = new_http_message("GET", "users/matias", "");
	req.init(conn, hmsg);
	EXPECT_TRUE(req.getUriStringParsedByIndex(0) == "users");
	EXPECT_TRUE(req.getUriStringParsedByIndex(1) == "matias");
	delete_http_message(hmsg);
}

TEST(HttpRequestConcreteTests, getUriType){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;

	struct http_message* hmsg = new_http_message("GET", "users/matias", "");
	req.init(conn, hmsg);
	EXPECT_TRUE(req.getUriType() == HttpRequest::ELEMENT_URI);
	delete_http_message(hmsg);

}

TEST(HttpRequestConcreteTests, getMethod){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;

	struct http_message* hmsg = new_http_message("GET", "users/matias", "");
	req.init(conn, hmsg);
	EXPECT_TRUE(req.getMethod() == HttpRequest::GET);
	delete_http_message(hmsg);

}

TEST(HttpRequestConcreteTests, getCampo){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;

	struct http_message* hmsg = new_http_message("GET", "users/matias", "{\"user\":\"matias\"}");
	req.init(conn, hmsg);
	EXPECT_TRUE(req.getCampo("user") == "matias");
	delete_http_message(hmsg);
}

TEST(HttpRequestConcreteTests, getCampoDeArray){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;

	struct http_message* hmsg = new_http_message("GET", "users/matias", "{\"users\":[\"matias\", \"gonza\"]}");
	req.init(conn, hmsg);
	EXPECT_TRUE(req.getCampoDeArray("users", 0) == "matias");
	EXPECT_TRUE(req.getCampoDeArray("users", 1) == "gonza");
	delete_http_message(hmsg);
}

TEST(HttpRequestConcreteTests, getUsername){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;

	struct http_message* hmsg = new_http_message("GET", "users/matias", "");
	req.init(conn, hmsg);
	EXPECT_TRUE(req.getUsername() == "matias");
	delete_http_message(hmsg);

	hmsg = new_http_message("GET", "users/juampa", "");
	req.init(conn, hmsg);
	EXPECT_TRUE(req.getUsername() == "juampa");
	delete_http_message(hmsg);
}


TEST(HttpRequestConcreteTests, setResponseOK){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;
	Reader reader;
	Value response_parsed;
	string response;

	struct http_message* hmsg = new_http_message("GET", "users/matias/profile", "");
	req.init(conn, hmsg);

	req.setResponse(Status::OK());
	response = req.getResponse();
	reader.parse(response.c_str(), response_parsed);
	EXPECT_TRUE(response_parsed["status"] == Status::OK().ToString());
	EXPECT_TRUE(req.getStatusCode() == 200);

	req.setResponse(Status::OK(), "todo bien");
	response = req.getResponse();
	reader.parse(response.c_str(), response_parsed);
	EXPECT_TRUE(response_parsed["status"] == "todo bien");
	EXPECT_TRUE(req.getStatusCode() == 200);
	delete_http_message(hmsg);
}

TEST(HttpRequestConcreteTests, setResponseError){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;
	Reader reader;
	Value response_parsed;
	string response;

	struct http_message* hmsg = new_http_message("GET", "users/matias/profile", "");
	req.init(conn, hmsg);

	req.setResponse(Status::InvalidArgument("El request recibido no es valido"));
	response = req.getResponse();
	reader.parse(response.c_str(), response_parsed);
	EXPECT_TRUE(req.getStatusCode() != 200);

	req.setResponse(Status::InvalidArgument("El request recibido no es valido"), "todo mal");
	response = req.getResponse();
	reader.parse(response.c_str(), response_parsed);
	EXPECT_TRUE(response_parsed["status"] == "todo mal");
	EXPECT_TRUE(req.getStatusCode() != 200);
	delete_http_message(hmsg);
}

TEST(HttpRequestConcreteTests, addValueToBody){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;
	Reader reader;
	Value response_parsed;
	string response;

	struct http_message* hmsg = new_http_message("GET", "users/matias/profile", "");
	req.init(conn, hmsg);

	req.setResponse(Status::InvalidArgument("El request recibido no es valido"));
	req.addValueToBody("conn_token", "1111");
	response = req.getResponse();
	reader.parse(response.c_str(), response_parsed);
	EXPECT_TRUE(response_parsed["conn_token"] == "1111");
	EXPECT_TRUE(req.getStatusCode() != 200);

	req.setResponse(Status::InvalidArgument("El request recibido no es valido"), "todo mal");
	req.addValueToBody("conn_token", "12345");
	response = req.getResponse();
	reader.parse(response.c_str(), response_parsed);
	EXPECT_TRUE(response_parsed["status"] == "todo mal");
	EXPECT_TRUE(response_parsed["conn_token"] == "12345");
	EXPECT_TRUE(req.getStatusCode() != 200);
	delete_http_message(hmsg);
}

TEST(HttpRequestConcreteTests, getHeaderValue){
	struct mg_connection* conn = new struct mg_connection;
	HttpRequestConcrete req;

	vector<string> header_names;
	header_names.push_back("conn_token");
	vector<string> header_values;
	header_values.push_back("1111");
	struct http_message* hmsg = new_http_message("GET", "users/matias/profile", "", &header_names, &header_values);
	req.init(conn, hmsg);
	EXPECT_TRUE(req.getConnToken() == "1111");
	EXPECT_TRUE(req.getHeaderValue("conn_token") == "1111");
	delete_http_message(hmsg);
}
