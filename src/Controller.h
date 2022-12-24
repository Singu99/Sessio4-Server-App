#pragma once
#include "Server/WebSocketServer.h"
#include "Ui/UserInterface.h"

class Controller
{
public:
    Controller();
    ~Controller();

    void Run();

private:
    UserInterface m_Ui;
    WebSocketServer m_WebSocketServer;
};