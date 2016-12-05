#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "EventHandlerChecksAuthentication.h"
#include "DatabaseMockRAM.h"
#include "TokenAuthenticator.h"
#include "HttpRequestMock.h"

class MockEventHandlerChecksAuthentication : public EventHandlerChecksAuthentication {
    public:
        MockEventHandlerChecksAuthentication(TokenAuthenticator *t) : EventHandlerChecksAuthentication(new DatabaseMockRAM, t) { called = false; }
        void _handle(HttpRequest &hmsg) { called = true; }

        bool called;
    private:
        bool isMyRequest(HttpRequest &hmsg) { return true; }
};

TEST(EventHandlerChecksAuthenticationTests, NoLLamaAlHandleSiNoMeRegistre){
    MockEventHandlerChecksAuthentication h(new TokenAuthenticator);
    EXPECT_FALSE(h.called);
    h.handle(*(new HttpRequestMock("gonzalo", "qwerty")));
    EXPECT_FALSE(h.called);
}

TEST(EventHandlerChecksAuthenticationTests, LLamaAlHandleSiMeRegistre){
    TokenAuthenticator tka;
    MockEventHandlerChecksAuthentication h(&tka);
    EXPECT_FALSE(h.called);

    std::string user = "gonzalo";
    std::string token = tka.createToken(user);

    h.handle(*(new HttpRequestMock(user, token)));
    EXPECT_TRUE(h.called);
}

TEST(EventHandlerChecksAuthenticationTests, NoLlamaAlHandleSiElTokenEsIncorrecto){
    TokenAuthenticator tka;
    MockEventHandlerChecksAuthentication h(&tka);
    EXPECT_FALSE(h.called);

    std::string user = "gonzalo";
    std::string token = tka.createToken(user);

    h.handle(*(new HttpRequestMock(user, "qwerty")));
    EXPECT_FALSE(h.called);
}

TEST(EventHandlerChecksAuthenticationTests, NoLlamaAlHandleSiUsoElTokenDeOtroUsuario){
    TokenAuthenticator tka;
    MockEventHandlerChecksAuthentication h(&tka);
    EXPECT_FALSE(h.called);

    std::string user1 = "gonzalo";
    std::string token1 = tka.createToken(user1);

    std::string user2 = "matias";
    h.handle(*(new HttpRequestMock(user2, token1)));
    EXPECT_FALSE(h.called);

    std::string token2 = tka.createToken(user2);
    h.handle(*(new HttpRequestMock(user2, token1)));
    EXPECT_FALSE(h.called);
}