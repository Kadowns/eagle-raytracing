#include <cmath>

//
// Created by Novak on 29/03/2020.
//

#include <eagle/application/raytracer/CameraController.h>

EG_RAYTRACER_BEGIN

void CameraController::init() {
    auto& window = Application::instance().window();
    m_camera.set_projection(70.0f, window.get_width() / (float)window.get_height());
    m_transform.set_position(glm::vec3(0, 10, 30));
    m_originalRotation = m_transform.rotation();
}

void CameraController::update() {

    glm::vec3 direction = glm::vec3(0);

    if (Input::instance().key_down(EG_KEY_W)) {
        direction += m_transform.front();
    }

    if (Input::instance().key_down(EG_KEY_S)) {
        direction -= m_transform.front();
    }

    if (Input::instance().key_down(EG_KEY_Q)) {
        direction += glm::vec3(0.0f, 1.0f, 0.0f);
    }

    if (Input::instance().key_down(EG_KEY_E)) {
        direction += glm::vec3(0.0f, -1.0f, 0.0f);
    }

    if (Input::instance().key_down(EG_KEY_A)) {
        direction -= m_transform.right();
    }

    if (Input::instance().key_down(EG_KEY_D)) {
        direction += m_transform.right();
    }

     m_transform.translate(m_speed * Time::delta_time() * direction);

    if (Input::instance().mouse_button_pressed(EG_MOUSE_BUTTON_LEFT)) {
        m_dragging = true;
        Application::instance().window().set_cursor_visible(false);
    }
    else if(Input::instance().mouse_button_released(EG_MOUSE_BUTTON_LEFT)) {
        m_dragging = false;
        Application::instance().window().set_cursor_visible(true);
    }

    m_rotAverageX = 0.0f;
    m_rotAverageY = 0.0f;

    if (m_dragging) {
        auto delta = Input::instance().mouse_move_delta();
        m_rotationX -= delta.first * m_sensitivity;
        m_rotationY += delta.second * m_sensitivity;
    }

    m_rotArrayX.emplace_back(m_rotationX);
    m_rotArrayY.emplace_back(m_rotationY);

    m_frameCounter = m_frameCounterTime / Time::delta_time();

    if (m_rotArrayX.size() >= m_frameCounter) {
        m_rotArrayX.erase(m_rotArrayX.begin());
    }
    if (m_rotArrayY.size() >= m_frameCounter) {
        m_rotArrayY.erase(m_rotArrayY.begin());
    }

    for(int i = 0; i < m_rotArrayX.size(); i++) {
        m_rotAverageX += m_rotArrayX[i];
    }
    for(int j = 0; j < m_rotArrayY.size(); j++) {
        m_rotAverageY += m_rotArrayY[j];
    }

    m_rotAverageX /= m_rotArrayX.size();
    m_rotAverageY /= m_rotArrayY.size();

    m_rotAverageX = clamp_angle(m_rotAverageX, m_minimumX, m_maximumX);
    m_rotAverageY = clamp_angle(m_rotAverageY, m_minimumY, m_maximumY);

    glm::quat xQuat = glm::angleAxis(glm::radians(m_rotAverageX), glm::vec3(0, 1, 0));
    glm::quat yQuat = glm::angleAxis(glm::radians(m_rotAverageY), glm::vec3(-1, 0, 0));

    m_transform.set_rotation(m_originalRotation * xQuat * yQuat);
    m_transform.set_rotation(glm::normalize(m_transform.rotation()));
    apply_transform_on_camera(m_transform, m_camera);
}

float CameraController::clamp_angle(float angle, float min, float max) {
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

void CameraController::apply_transform_on_camera(const Transform &transform, Camera &camera) {
    camera.set_view(transform.position(), transform.position() + transform.front(), transform.up());
}

EG_RAYTRACER_END

