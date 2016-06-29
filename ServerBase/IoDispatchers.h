#pragma once

#include "IApiService.h"
#include "ApiMessage.h"
#include "ApiResponderEmpty.h"
#include "DeviceProtocol.h"

class IoDispatchers : public IApiService
{
public:
    IoDispatchers(_In_ DeviceProtocol* const pProtocol);
    ~IoDispatchers();

    void ServiceIoOperation(_In_ CONSOLE_API_MSG* const pMsg);

    void NotifyInputReadWait();
    void NotifyOutputWriteWait();

private:

    void _NotifyWait(_In_ queue<CONSOLE_API_MSG>* const pQueue);

    DWORD _ServiceIoOperation(_In_ CONSOLE_API_MSG* const pMsg);
    static DWORD _IoConnect(_In_ IApiResponders* const pResponder, _In_ DeviceProtocol* Server, _In_ CONSOLE_API_MSG* const pMsg);
    static DWORD _IoDisconnect(_In_ CONSOLE_API_MSG* const pMsg);
    static DWORD _IoDefault();

    ApiResponderEmpty _Responder;
    DeviceProtocol* const _pProtocol;

    mutex ioOperation;
    queue<CONSOLE_API_MSG> _QueuedReadInput;
    queue<CONSOLE_API_MSG> _QueuedWriteOutput;

};
