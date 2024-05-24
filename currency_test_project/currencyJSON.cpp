#define _CRT_SECURE_NO_WARNINGS

#include "currencyJSON.hpp"

#include "rapidjson/filereadstream.h"

#include <fstream>
#include <iostream>

void CurrencyJSON::saveToFileJSON() {
	std::ofstream file("currency.json", std::ios::out | std::ios::trunc);
	if (!file.is_open())
		throw std::runtime_error("currensyJSON: error opening file currency.json");
	file << buffer;
    file.close();
}

void CurrencyJSON::saveToFileXML() {
    if (!bufferDoc.IsArray())
        throw std::runtime_error("currencyJSON: JSON buffer is not an array");
    std::ofstream file("currency.xml", std::ios::out | std::ios::trunc);
    if (!file.is_open())
        throw std::runtime_error("currensyJSON: error opening file currency.xml");
    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    file << "<currencies>\n";
    for (rapidjson::SizeType i = 0; i < bufferDoc.Size(); i++) {
        const rapidjson::Value &currency = bufferDoc[i];
        file << "  <currency>\n";
        file << "    <r030>" << currency["r030"].GetUint() << "</r030>\n";
        file << "    <txt>" << currency["txt"].GetString() << "</txt>\n";
        file << "    <rate>" << currency["rate"].GetDouble() << "</rate>\n";
        file << "    <cc>" << currency["cc"].GetString() << "</cc>\n";
        file << "    <exchangedate>" << currency["exchangedate"].GetString() << "</exchangedate>\n";
        file << "  </currency>\n";
    }
    file.close();
}

void CurrencyJSON::saveToFileCSV() {
    if (!bufferDoc.IsArray())
        throw std::runtime_error("currencyJSON: JSON buffer is not an array");
    std::ofstream file("currency.csv", std::ios::out | std::ios::trunc);
    if (!file.is_open())
        throw std::runtime_error("currensyJSON: error opening file currency.csv");
    file << "r030;txt;rate;cc;exchangedate\n";
    for (rapidjson::SizeType i = 0; i < bufferDoc.Size(); i++) {
        const rapidjson::Value &currency = bufferDoc[i];
        file << currency["r030"].GetUint() << ";";
        file << "\"" << currency["txt"].GetString() << "\";";
        file << currency["rate"].GetDouble() << ";";
        file << currency["cc"].GetString() << ";";
        file << currency["exchangedate"].GetString() << "\n";
    }
    file.close();
}

void CurrencyJSON::readConfigJSON() {
    FILE *conf = fopen("config.json", "rb");
    if (!conf)
        throw std::runtime_error("currensyJSON: unable to open config.json");
    char buffer[2048] = "\0";
    rapidjson::FileReadStream is(conf, buffer, sizeof(buffer));
    rapidjson::Document confDoc;
    confDoc.ParseStream(is);
    fclose(conf);
    if (confDoc.HasParseError())
        throw std::runtime_error("currensyJSON: error parsing config.json");
    if (confDoc.HasMember("interval") && confDoc["interval"].IsInt())
        interval = confDoc["interval"].GetInt();
    else
        std::cerr << "missing or invalid 'interval' in config file" << std::endl;
    if (confDoc.HasMember("format") && confDoc["format"].IsString())
        format = confDoc["format"].GetString();
    else
        std::cerr << "missing or invalid 'format' in config file" << std::endl;
}

void CurrencyJSON::parseBuffer() {
    bufferDoc.Parse(buffer.c_str());
    if (!bufferDoc.IsArray())
        throw std::runtime_error("currencyJSON: JSON buffer is not an array");
}
