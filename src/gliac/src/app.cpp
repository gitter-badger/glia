#include "gliac/app.h"

gliac::Application::Application(gliac::Options &options) {
    this->options = &options;
}

gliac::Application::~Application() {
    cout << "Object is being deleted" << endl;
}