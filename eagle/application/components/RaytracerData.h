//
// Created by Novak on 11/04/2020.
//

#ifndef EAGLE_RAYTRACERDATA_H
#define EAGLE_RAYTRACERDATA_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

struct RaytracerData {
    struct{
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 inverseProjection;
        alignas(16) glm::vec3 position;
        alignas(8) glm::vec2 pixelOffset;
        alignas(16) glm::vec4 light;
        float sampleCount;
        int sphereCount;
    } ubo;

    struct SphereData {
        alignas(16) glm::vec3 position;
        alignas(4) float radius;
        alignas(16) glm::vec3 albedo;
        alignas(16) glm::vec3 specular;
    };

    std::vector<SphereData> spheresData;
    Handle<UniformBuffer> uniformBuffer;
    Handle<ComputeShader> computeShader;
    Handle<StorageBuffer> spheresBuffer;
    Handle<Texture> computeTarget;
    Handle<Texture> skybox;
};

EG_RAYTRACER_END

#endif //EAGLE_RAYTRACERDATA_H
