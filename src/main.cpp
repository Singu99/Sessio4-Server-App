#include "Controller.h"

void LayerWindow(const std::string& name);
void NodeWindow(const std::string& name);
void ShowExampleAppDockSpace(bool* p_open);

int main(int argc, char *argv[]) {
    Controller controller;
    controller.Run();
    return 0;
}