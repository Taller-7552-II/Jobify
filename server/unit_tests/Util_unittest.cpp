
#include <openssl/md5.h>
#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include "Util.h"
#include <fstream>

TEST(UtilTests, MD5Test){
    unsigned char digest[MD5_DIGEST_LENGTH];
    std::string str = "happy";

    MD5((unsigned char*)str.c_str(), str.size(), (unsigned char*)&digest);

    char mdString[33];

    std::ofstream log;
    log.open("Util_test_LOG.txt", std::ios::app);
    if(!log){
        log.open("Util_test_LOG.txt", std::ios::trunc);
    }

    for(int i = 0; i < 16; i++)
         sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    log << "md5 digest: " << mdString << std::endl;

    std::string res = "";
    get_md5_hash(str, res);

    log << "md5 in str: " << res << std::endl;

    log.close();
}
