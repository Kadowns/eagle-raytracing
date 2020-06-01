//
// Created by Novak on 5/4/2020.
//

#include <eagle/application/components/physics/shapes/PlaneCollider.h>

EG_RAYTRACER_BEGIN

PlaneCollider::PlaneCollider(const glm::vec3 &normal, float distance) : m_normal(normal), m_distance(distance) {

}

const std::type_index& PlaneCollider::type() const {
    static std::type_index index(typeid(PlaneCollider));
    return index;
}

glm::vec3 PlaneCollider::compute_axis_inertia(Rigidbody &rigidbody) const {
    return glm::vec3(0, 0, 0);
}

EG_RAYTRACER_END


