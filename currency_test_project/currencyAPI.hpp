#pragma once

#include <string>

class CurrencyAPI {
public:
	CurrencyAPI() = default;
	~CurrencyAPI() = default;
	const std::string &getReadBuffer() const;
	void readCurrency();
private:
	// callback функція для обробки відповіді від сервера
	static size_t writeCurrency(void *data, size_t size, size_t n, std::string *buffer);
	std::string readBuffer;
};
