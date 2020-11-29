//
// Created by Novak on 18/06/2019.
//
#include <eagle/Eagle.h>
#include "test/TestLayer.h"

Eagle::ApplicationCreateInfo create_application_info() {
    Eagle::ApplicationCreateInfo config = {};
    config.appName = "Dummy";
    config.windowType = new Eagle::WindowGLFW(1280, 720);
    config.layers.push_back(std::make_shared<Eagle::Engine::SceneLayer>());
    config.layers.push_back(std::make_shared<Eagle::Editor::EditorLayer>());
    config.layers.push_back(std::make_shared<Eagle::Engine::RenderLayer>());
    config.layers.push_back(std::make_shared<Eagle::InputLayer>());
//    config.layers.emplace_back(std::make_shared<TestLayer>());
    config.coreLogLevel = Eagle::Log::INFO;
    config.clientLogLevel = Eagle::Log::TRACE;
    return config;
}

int main(){

    Eagle::ApplicationCreateInfo createInfo = create_application_info();
    Eagle::Scope<Eagle::Application> app = std::make_unique<Eagle::Application>(createInfo);

    try{
        app->run();
    }catch(std::exception& e){
        EG_CORE_FATAL_F("Exception: {0}", e.what());
        return 1;
    }

    return 0;
}
