//#pragma once
//
//#include <windows.h>
//#include <tchar.h>
//#include <string>
//
//#define SERVICE_NAME _T("CurrencyService")
//
//class Service {
//public:
//	Service() = default;
//	~Service() = default;
//    static VOID WINAPI ServiceCtrlHandler(DWORD dwCtrl);
//	static VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv, bool isService);
//	void ServiceWorkerThread();
//	void start(DWORD dwArgc, LPTSTR *lpszArgv);
//	void Stop();
//	void readCurrency();
//private:
//	static SERVICE_STATUS_HANDLE   g_StatusHandle;
//	static SERVICE_STATUS          g_ServiceStatus;
//	static HANDLE                  g_ServiceStopEvent;
//};
