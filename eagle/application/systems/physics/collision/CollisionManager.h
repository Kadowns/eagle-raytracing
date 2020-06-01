//
// Created by Novak on 5/4/2020.
//

#ifndef EAGLE_COLLISIONMANAGER_H
#define EAGLE_COLLISIONMANAGER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/systems/physics/collision/Collision.h>

EG_RAYTRACER_BEGIN

class CollisionManager {
private:
    typedef std::unordered_map<std::type_index, std::unordered_map<std::type_index, std::function<bool(Collision&)>>> CollisionFunctionTable;
public:
    static void configure();
    static bool test_collision(Collision &collision);
private:
    static bool sphere_vs_sphere(Collision& collision);
    static bool sphere_vs_plane(Collision& collision);
    static bool sphere_vs_box(Collision& collision);
    static bool box_vs_plane(Collision& collision);
    static bool box_vs_sphere(Collision& collision);
    static bool box_vs_box(Collision& collision);
    static bool plane_vs_sphere(Collision& collision);
    static bool plane_vs_box(Collision& collision);
    static bool plane_vs_plane(Collision& collision);


    //helper functions
    static bool track_face_axis(int32_t& axis, int32_t axisNumber, float s, float& sMax, glm::vec3& axisNormal, const glm::vec3& normal);
    static bool track_face_edge(int32_t& axis, int32_t axisNumber, float s, float& sMax, glm::vec3& axisNormal, const glm::vec3& normal);
    static void compute_incident_face(const Rigidbody::Transform &trI, const glm::vec3 &e, glm::vec3 n, glm::vec3 *out);
    static void compute_reference_basis(const Rigidbody::Transform &trR, const glm::vec3 &eR,
                                        glm::vec3 n, int32_t axis, glm::mat3 &basis,
                                        glm::vec3 &e);
    static uint32_t clip(const glm::vec3 &posR, const glm::vec3 &e, const glm::mat3 &basis, glm::vec3 *incident,
                         glm::vec3 *outVerts, float *outDepths);
    static uint32_t ortographic(float sign, float e, float axis, glm::vec3 *in, uint32_t inCount, glm::vec3 *out);
    static void support_edge(const Rigidbody::Transform& tr, const glm::vec3& e, glm::vec3 n, glm::vec3* aOut, glm::vec3* bOut);
    static void edges_contact(glm::vec3 &ca, glm::vec3 &cb, const glm::vec3 &PA, const glm::vec3 &QA, const glm::vec3 &PB, const glm::vec3 &QB);

private:
    static CollisionFunctionTable m_collisionFunctionTable;
};

EG_RAYTRACER_END

#endif //EAGLE_COLLISIONMANAGER_H
