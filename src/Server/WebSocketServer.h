#pragma once 
#include <crow.h>
#include "Ui/UserInterface.h"
#include <future>

class WebSocketServer
{
public:
    WebSocketServer(UserInterface* ui);
    ~WebSocketServer();

    void Start();

private:
    crow::SimpleApp m_server;
    UserInterface* m_ui;
    std::future<void> m_serverThread;
};