#include "service_http.h"

CURLcode service_http_get(char uri[]) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, uri);
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, );
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}