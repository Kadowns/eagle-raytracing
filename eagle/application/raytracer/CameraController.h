//
// Created by Novak on 29/03/2020.
//

#ifndef EAGLE_CAMERACONTROLLER_H
#define EAGLE_CAMERACONTROLLER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include "Camera.h"
#include "Transform.h"


EG_RAYTRACER_BEGIN

class CameraController {
public:

    void init();
    void update();
    inline Camera& camera() { return m_camera; }
    inline Transform& transform() { return m_transform; }

private:
    float clamp_angle(float angle, float min, float max);
    static void apply_transform_on_camera(const Transform &transform, Camera &camera);

private:
    Camera m_camera;
    Transform m_transform;

    float m_speed = 20.0f;
    float m_sensitivity = 0.05f;
    float m_minimumX = -360.0f;
    float m_maximumX = 360.0f;
    float m_minimumY = -80.0f;
    float m_maximumY = 90.0f;
    float m_frameCounterTime = 0.1f;
    float m_frameCounter;

    std::vector<float> m_rotArrayX;
    std::vector<float> m_rotArrayY;

    float m_rotationX;
    float m_rotationY;
    float m_rotAverageX;
    float m_rotAverageY;

    glm::quat m_originalRotation;
    bool m_dragging = false;
};

EG_RAYTRACER_END

#endif //EAGLE_CAMERACONTROLLER_H
