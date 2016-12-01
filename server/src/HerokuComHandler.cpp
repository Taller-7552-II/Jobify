#include "HerokuComHandler.h"

HerokuComHandler::HerokuComHandler()
{
    //ctor
}

HerokuComHandler::~HerokuComHandler()
{
    //dtor
}



size_t HerokuComHandler::write_data(char *ptr, size_t size, size_t nmemb, struct url_data *data) {
    size_t index = data->size;
    size_t n = (size * nmemb);
    char* tmp;

    data->size += (size * nmemb);

    tmp = (char*)realloc(data->data, data->size + 1);

    if(tmp) {
        data->data = tmp;
    } else {
        if(data->data) {
            free(data->data);
        }
        fprintf(stderr, "Failed to allocate memory.\n");
        return 0;
    }

    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';

    return size * nmemb;
}

size_t HerokuComHandler::matiMethodComeback(char * data, size_t size, size_t nmemb, struct url_data *datax,void * p)
{
    return static_cast<HerokuComHandler*>(p)->write_data(data, size, nmemb,datax);
}


char* HerokuComHandler::POST(char* jason,char* statham)
{
    CURL *curl;

    struct url_data data;
    data.size = 0;
    data.data = (char*) malloc(4096); /* reasonable size initial buffer */
    if(NULL == data.data) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return NULL;
    }

    data.data[0] = '\0';

    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        curl_slist_append(headers, "Accept: application/json");
       curl_slist_append(headers, "Content-Type: application/json");
        curl_slist_append(headers, "charsets: utf-8");
        curl_slist_append(headers,"conn_token: ");

        curl_easy_setopt(curl, CURLOPT_URL, statham);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jason);

        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcrp/0.1");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &HerokuComHandler::matiMethodComeback );
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        res = curl_easy_perform(curl);


        if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);

    }
    return data.data;
}

char* HerokuComHandler::DELETE(char* statham)
{
    CURL *curl;

    struct url_data data;
    data.size = 0;
    data.data = (char*) malloc(4096); /* reasonable size initial buffer */
    if(NULL == data.data) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return NULL;
    }

    data.data[0] = '\0';

    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        curl_slist_append(headers, "Accept: application/json");
       curl_slist_append(headers, "Content-Type: application/json");
        curl_slist_append(headers, "charsets: utf-8");
        curl_slist_append(headers,"conn_token: 1008060183");

        curl_easy_setopt(curl, CURLOPT_URL, statham);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");

        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcrp/0.1");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &HerokuComHandler::matiMethodComeback );
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        res = curl_easy_perform(curl);


        if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);

    }
    return data.data;
}

char* HerokuComHandler::GET(char* url) {
    CURL *curl;

    struct url_data data;
    data.size = 0;
    data.data = (char*) malloc(4096); /* reasonable size initial buffer */
    if(NULL == data.data) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return NULL;
    }

    data.data[0] = '\0';

    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &HerokuComHandler::matiMethodComeback );
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);

    }
    return data.data;
}
