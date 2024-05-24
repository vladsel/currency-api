#include "service.hpp"
#include "currencyAPI.hpp"
#include "currencyJSON.hpp"

SERVICE_STATUS_HANDLE   Service::g_StatusHandle = NULL;
SERVICE_STATUS          Service::g_ServiceStatus = { 0 };
HANDLE                  Service::g_ServiceStopEvent = INVALID_HANDLE_VALUE;

VOID __stdcall Service::ServiceCtrlHandler(DWORD dwCtrl) {
    switch (dwCtrl) {
        case SERVICE_CONTROL_STOP:
            g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
            SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
            // Signal the service to stop.
            SetEvent(g_ServiceStopEvent);
            return;
        case SERVICE_CONTROL_INTERROGATE:
            break;
        default:
            break;
    }
}

VOID __stdcall Service::ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv, bool isService) {
    DWORD Status = E_FAIL;

    g_ServiceStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (g_ServiceStopEvent == NULL) {
        OutputDebugString(_T("My Sample Service: ServiceMain: CreateEvent returned error"));
        return;
    }

    // Створення об'єкта служби як динамічного об'єкта
    Service *service = new Service();
    if (service == nullptr) {
        OutputDebugString(_T("My Sample Service: ServiceMain: Failed to create service object"));
        return;
    }

    service->start(dwArgc, lpszArgv);

    // Очікуємо завершення робочої нитки служби
    WaitForSingleObject(g_ServiceStopEvent, INFINITE);

    // Зупиняємо службу і звільняємо пам'ять
    service->Stop();
    delete service;
}

void Service::ServiceWorkerThread() {
    CurrencyAPI curAPI;
    while (WaitForSingleObject(g_ServiceStopEvent, 0) != WAIT_OBJECT_0) {
        // Perform main service function here
        //readCurrency();
        curAPI.readCurrency();
        Sleep(3600000);  // 1 hour
    }
    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
}

void Service::start(DWORD dwArgc, LPTSTR *lpszArgv) {
    g_ServiceStatus.dwServiceType = SERVICE_WIN32;
    g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    g_ServiceStatus.dwWin32ExitCode = NO_ERROR;
    g_ServiceStatus.dwServiceSpecificExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;

    g_StatusHandle = RegisterServiceCtrlHandler(SERVICE_NAME, ServiceCtrlHandler);
    if (g_StatusHandle == NULL) {
        OutputDebugString(_T("My Sample Service: Start: RegisterServiceCtrlHandler returned error"));
        return;
    }

    g_ServiceStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (g_ServiceStopEvent == NULL) {
        OutputDebugString(_T("My Sample Service: Start: CreateEvent returned error"));
        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        g_ServiceStatus.dwWin32ExitCode = GetLastError();
        g_ServiceStatus.dwCheckPoint = 1;
        SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
        return;
    }

    g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(g_StatusHandle, &g_ServiceStatus);

    ServiceWorkerThread();
}

void Service::Stop() {
    g_ServiceStatus.dwControlsAccepted = 0;
    g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
    g_ServiceStatus.dwWin32ExitCode = NO_ERROR;
    g_ServiceStatus.dwCheckPoint = 4;

    SetServiceStatus(g_StatusHandle, &g_ServiceStatus);

    // Perform cleanup tasks here.
    if (g_ServiceStopEvent != NULL) {
        CloseHandle(g_ServiceStopEvent);
        g_ServiceStopEvent = NULL;
    }

    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
}

void Service::readCurrency() {

}
