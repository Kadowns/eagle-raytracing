//
// Created by Novak on 18/06/2019.
//
#include <eagle/Eagle.h>

Eagle::ApplicationCreateInfo create_application_info() {
    Eagle::ApplicationCreateInfo config = {};
    config.appName = "Dummy";
    config.windowType = new Eagle::WindowGLFW(1280, 720);
    config.layers.push_back(std::make_shared<Eagle::Raytracer::SceneLayer>());
    config.layers.push_back(std::make_shared<Eagle::Raytracer::EditorLayer>());
    config.layers.push_back(std::make_shared<Eagle::Raytracer::RenderLayer>());
    config.layers.push_back(std::make_shared<Eagle::InputLayer>());
    config.coreLogLevel = Eagle::Log::TRACE;
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
