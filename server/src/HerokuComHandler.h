#ifndef HEROKUCOMHANDLER_H
#define HEROKUCOMHANDLER_H
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>


class HerokuComHandler
{
    public:
        HerokuComHandler();
        virtual ~HerokuComHandler();
        static size_t matiMethodComeback(char * data, size_t size, size_t nmemb,struct url_data *datax, void * p);
        size_t write_data(char *ptr, size_t size, size_t nmemb, struct url_data *data);
        char* GET(char* url);
        char* DELETE(char* statham);
        char* POST(char* jason,char* statham);
    protected:

    private:
};


struct url_data {
    size_t size;
    char* data;
};
#endif // HEROKUCOMHANDLER_H
