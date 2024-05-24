#define CURL_STATICLIB

#include "currencyAPI.hpp"

#include "curl/curl.h"
#include <iostream>

const std::string &CurrencyAPI::getReadBuffer() const {
	return readBuffer;
}

void CurrencyAPI::readCurrency() {
    readBuffer.clear();
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL); // ����������� libcurl
    curl = curl_easy_init(); // ��������� ��'���� CURL
    if (curl) {
        // ������������ URL ��� ������ ��� ��������� ����� � JSON
        curl_easy_setopt(curl, CURLOPT_URL, "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?json");
        // ������������ ��������� ��������� UTF-8
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "UTF-8");
        // ������������ callback ������� ��� ������� ������
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurrencyAPI::writeCurrency);
        // �������� ������ ��� ���������� ������ 
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // ��������� HTTP-������ �� ��� ������������ ������
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            throw std::runtime_error(curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }
    else
        throw std::runtime_error("currencyAPI: error creating curl object");
    curl_global_cleanup();
}

size_t CurrencyAPI::writeCurrency(void *data, size_t size, size_t n, std::string *buffer) {
    buffer->append((char *)data, size * n);
    return size * n;
}
