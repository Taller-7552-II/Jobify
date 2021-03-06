#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "EventHandlerIgnoresAuthentication.h"
#include "DatabaseMockRAM.h"
#include "TokenAuthenticator.h"
#include "HttpRequestMock.h"

bool called = false;

class MockEventHandlerIgnoresAuthentication : public EventHandlerIgnoresAuthentication {
    public:
        MockEventHandlerIgnoresAuthentication() : EventHandlerIgnoresAuthentication(new DatabaseMockRAM, new TokenAuthenticator) {}
        void _handle(HttpRequest &hmsg) { called = true; }
    private:
        bool isMyRequest(HttpRequest &hmsg) { return true; }
};

TEST(EventHandlerIgnoresAuthenticationTest, SiempreLlamaAHandle){
    MockEventHandlerIgnoresAuthentication h;
    EXPECT_FALSE(called);
    h.handle(*(new HttpRequestMock));
    EXPECT_TRUE(called);
}
