#include "WebSocketServer.h"
#include <sstream>
#include <locale>

WebSocketServer::WebSocketServer(UserInterface* ui)
    : m_ui(ui)
{}

WebSocketServer::~WebSocketServer()
{
    m_server.stop();
}

void WebSocketServer::Start()
{
    CROW_ROUTE(m_server, "/foo")
        .websocket()
        .onopen([this](crow::websocket::connection& conn){
                CROW_LOG_INFO << "new websocket connection";
                m_ui->UiLog("New websocket connection\n");
                })
        .onclose([this](crow::websocket::connection& conn, const std::string& reason){
                CROW_LOG_INFO << "websocket connection closed: " << reason;
                m_ui->UiLog("Websocket connection closed. Reason : %s\n", reason.c_str());
                })
        .onmessage([this](crow::websocket::connection& conn, const std::string& data, bool is_binary){
                    std::stringstream ss;
                    std::string name;
                    std::string version;
                    int intVersion;
                    name = data.substr(0, data.find_first_of(':'));
                    version = data.substr(data.find_first_of(':') + 1);
                    ss << version;
                    ss >> intVersion;
                    m_ui->UiLog("Received message: %s\n", data.c_str());
                    //m_ui->UiLog("Received message: Name %s, Version %d\n", name.c_str(), intVersion);
                    CROW_LOG_INFO << "Received message: Name " << name << ", Version " << intVersion; 
                    m_ui->UpdateNodeVersion(name, intVersion);
                });
    m_serverThread = std::async(std::launch::async, [this](){
        m_server.port(8126)
            .multithreaded()
            .run();
    });
}
