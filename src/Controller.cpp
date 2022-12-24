#include "Controller.h"

Controller::Controller()
    : m_Ui(), m_WebSocketServer(&m_Ui)
{}

Controller::~Controller()
{

}

void Controller::Run()
{
    m_WebSocketServer.Start();
    m_Ui.RenderUi();
}
