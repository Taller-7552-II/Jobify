#include "gtest/gtest.h"
#include "TokenAuthenticator.h"

TEST(TokenAuthenticatorTest, CrearTokenCreaUnTokenNoVacio){
    TokenAuthenticator tka;
    EXPECT_FALSE(tka.createToken("gonzalo") == "");
}

TEST(TokenAuthenticatorTest, IsValidTokenFunciona){
    TokenAuthenticator tka;
    std::string tk1 = tka.createToken("gonzalo");
    EXPECT_FALSE(tk1 == "");
    std::string tk2 = tka.createToken("matias");
    EXPECT_FALSE(tk2 == "");
    EXPECT_FALSE(tka.isValidToken("gonzalo", tk2));
    EXPECT_FALSE(tka.isValidToken("matias", tk1));
    EXPECT_TRUE(tka.isValidToken("gonzalo", tk1));
    EXPECT_TRUE(tka.isValidToken("matias", tk2));
}

TEST(TokenAuthenticatorTest, SiCreoDosTokenParaElMismoUserValeSoloElUltimo){
    TokenAuthenticator tka;
    std::string tk1 = tka.createToken("gonzalo");
    EXPECT_FALSE(tk1 == "");
    std::string tk2 = tka.createToken("gonzalo");
    EXPECT_FALSE(tk1 == tk2);
    EXPECT_FALSE(tka.isValidToken("gonzalo", tk1));
    EXPECT_TRUE(tka.isValidToken("gonzalo", tk2));
}

TEST(TokenAuthenticatorTest, BorrarTokenFuncionaSiEseTokenExiste){
    TokenAuthenticator tka;
    EXPECT_FALSE(tka.removeToken("gonzalo"));
    EXPECT_FALSE(tka.createToken("gonzalo") == "");
    EXPECT_TRUE(tka.removeToken("gonzalo"));
}