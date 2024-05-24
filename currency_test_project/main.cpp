//#pragma comment(lib, "libcurl_a.lib")

#include "currencyAPI.hpp"
#include "currencyJSON.hpp"
#include "service.hpp"

#include <iostream>


int main(int argc, TCHAR *argv[]) {
    // Останній аргумент визначає, що служба запускається як звичайна програма
    Service serv;
    serv.ServiceMain(argc, argv, true);
    return 0;
}



//int _tmain(int argc, TCHAR *argv[]) {
//    SERVICE_TABLE_ENTRY ServiceTable[] =
//    {
//        {(TCHAR *)SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION)Service::ServiceMain},
//        {NULL, NULL}
//    };
//
//    if (StartServiceCtrlDispatcher(ServiceTable) == FALSE) {
//        OutputDebugString(_T("My Sample Service: Main: StartServiceCtrlDispatcher returned error"));
//        return GetLastError();
//    }
//
//    std::cout << "hi";
//
//    return 0;
//}


//int main() {
//	try {
//        system("chcp 65001");
//        printf("\n\n");
//
//        CurrencyAPI curAPI;
//		curAPI.readCurrency();
//
//		CurrencyJSON curJSON(curAPI.getReadBuffer());
//		curJSON.parseBuffer();
//		curJSON.saveToFileJSON();
//		curJSON.saveToFileXML();
//		curJSON.saveToFileCSV();
//		curJSON.readConfigJSON();
//		std::cout << curJSON.getFormat() << std::endl << curJSON.getInterval() << std::endl;
//
//		return 0;
//	}
//	catch (const std::exception &ex) {
//		std::cerr << "main error: " << ex.what() << std::endl;
//		return 1;
//	}
//	catch (...) {
//		std::cerr << "unknown main error" << std::endl;
//		return 1;
//	}
//}
