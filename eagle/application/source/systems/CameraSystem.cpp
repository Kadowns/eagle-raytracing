//
// Created by Novak on 09/04/2020.
//

#include <eagle/application/systems/CameraSystem.h>
#include <eagle/application/components/Transform.h>
#include <eagle/application/components/Camera.h>
#include <eagle/application/components/CameraController.h>
#include <eagle/application/components/Sphere.h>
#include <eagle/application/components/SceneData.h>
#include <eagle/application/components/SingletonComponent.h>

EG_RAYTRACER_BEGIN


void CameraSystem::configure(entityx::EntityManager &entities, entityx::EventManager &events) {
    using namespace entityx;
    auto& window = Application::instance().window();
    entities.each<Camera, CameraController, Transform>([&](Entity e, Camera& camera, CameraController& controller, Transform& transform){
        camera.set_view(transform.position(), transform.position() + transform.front(), transform.up());
        camera.set_projection(70.0f, window.get_width() / (float)window.get_height());
        controller.originalRotation = transform.rotation();
    });
}

void CameraSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    entities.each<Camera, CameraController, Transform>([&](entityx::Entity e, Camera& camera, CameraController& controller, Transform& transform){

        glm::vec3 direction = glm::vec3(0);

        if (Input::instance().key_down(EG_KEY_W)) {
            direction += transform.front();
        }

        if (Input::instance().key_down(EG_KEY_S)) {
            direction -= transform.front();
        }

        if (Input::instance().key_down(EG_KEY_Q)) {
            direction += glm::vec3(0.0f, 1.0f, 0.0f);
        }

        if (Input::instance().key_down(EG_KEY_E)) {
            direction += glm::vec3(0.0f, -1.0f, 0.0f);
        }

        if (Input::instance().key_down(EG_KEY_A)) {
            direction -= transform.right();
        }

        if (Input::instance().key_down(EG_KEY_D)) {
            direction += transform.right();
        }

        if (Input::instance().key_pressed(EG_KEY_G)){
            SceneData& scene = SingletonComponent::get<SceneData>();

            auto s = entities.create();
            auto tr = s.assign<Transform>(transform);
            auto sphere = s.assign<Sphere>();

            sphere->radius = Random::range(0.3, 8.0f);
            glm::vec3 color = glm::vec3(Random::value(), Random::value(), Random::value());
            bool metal = Random::value() < scene.metalPercent;
            sphere->albedo = metal ? glm::vec3(0.01f) : glm::vec3(color.r, color.g, color.b);
            sphere->specular = metal ? glm::vec3(color.r, color.g, color.b) : glm::vec3(0.01f);
            tr->translate(transform.front() * sphere->radius * 2.0f);
        }

        transform.translate(controller.speed * Time::delta_time() * direction);


        if (Input::instance().mouse_button_pressed(EG_MOUSE_BUTTON_LEFT)) {
            controller.dragging = true;
            Application::instance().window().set_cursor_visible(false);
        }
        else if(Input::instance().mouse_button_released(EG_MOUSE_BUTTON_LEFT)) {
            controller.dragging = false;
            Application::instance().window().set_cursor_visible(true);
        }

        controller.rotAverageX = 0.0f;
        controller.rotAverageY = 0.0f;

        if (controller.dragging) {
            auto delta = Input::instance().mouse_move_delta();
            controller.rotationX -= delta.first * controller.sensitivity;
            controller.rotationY += delta.second * controller.sensitivity;
        }

        controller.rotArrayX.emplace_back(controller.rotationX);
        controller.rotArrayY.emplace_back(controller.rotationY);

        controller.frameCounter = controller.frameCounterTime / Time::delta_time();

        if (controller.rotArrayX.size() >= controller.frameCounter) {
            controller.rotArrayX.erase(controller.rotArrayX.begin());
        }
        if (controller.rotArrayY.size() >= controller.frameCounter) {
            controller.rotArrayY.erase(controller.rotArrayY.begin());
        }

        for(int i = 0; i < controller.rotArrayX.size(); i++) {
            controller.rotAverageX += controller.rotArrayX[i];
        }
        for(int j = 0; j < controller.rotArrayY.size(); j++) {
            controller.rotAverageY += controller.rotArrayY[j];
        }

        controller.rotAverageX /= controller.rotArrayX.size();
        controller.rotAverageY /= controller.rotArrayY.size();

        controller.rotAverageX = clamp_angle(controller.rotAverageX, controller.minimumX, controller.maximumX);
        controller.rotAverageY = clamp_angle(controller.rotAverageY, controller.minimumY, controller.maximumY);

        glm::quat xQuat = glm::angleAxis(glm::radians(controller.rotAverageX), glm::vec3(0, 1, 0));
        glm::quat yQuat = glm::angleAxis(glm::radians(controller.rotAverageY), glm::vec3(-1, 0, 0));

        transform.set_rotation(controller.originalRotation * xQuat * yQuat);
        transform.set_rotation(glm::normalize(transform.rotation()));

        if (transform.hasChanged){
            camera.set_view(transform.position(), transform.position() + transform.front(), transform.up());
            events.emit<OnCameraUpdate>(camera);
            transform.hasChanged = false;
        }
    });
}

float CameraSystem::clamp_angle(float angle, float min, float max) {
    angle = std::fmod(angle, 360.0f);
    if ((angle >= -360.f) && (angle <= 360.f)) {
        if (angle < -360.f) {
            angle += 360.f;
        }

        if (angle > 360.f) {
            angle -= 360.f;
        }
    }
    return std::clamp(angle, min, max);
}



EG_RAYTRACER_END

