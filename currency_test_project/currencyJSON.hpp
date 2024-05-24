#pragma once

#include <string>

#include "rapidjson/document.h"

class CurrencyJSON {
public:
	CurrencyJSON(std::string _buffer) : buffer(_buffer) {}
	~CurrencyJSON() = default;
	void saveToFileJSON();
	void saveToFileXML();
	void saveToFileCSV();
	void readConfigJSON();
	void parseBuffer();
	uint16_t getInterval() const { return interval; }
	std::string getFormat() const { return format; }
private:
	std::string buffer;
	std::string format;
	uint16_t interval = 0;
	rapidjson::Document bufferDoc;
};
