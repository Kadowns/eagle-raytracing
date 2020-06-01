//
// Created by Novak on 5/3/2020.
//

#include <eagle/application/components/physics/shapes/BoxCollider.h>

EG_RAYTRACER_BEGIN
BoxCollider::BoxCollider(const glm::vec3 extents) : m_extents(extents){
    m_vertices = {
            glm::vec3( -m_extents.x, -m_extents.y, -m_extents.z ),
            glm::vec3( -m_extents.x, -m_extents.y,  m_extents.z ),
            glm::vec3( -m_extents.x,  m_extents.y, -m_extents.z ),
            glm::vec3( -m_extents.x,  m_extents.y,  m_extents.z ),
            glm::vec3(  m_extents.x, -m_extents.y, -m_extents.z ),
            glm::vec3(  m_extents.x, -m_extents.y,  m_extents.z ),
            glm::vec3(  m_extents.x,  m_extents.y, -m_extents.z ),
            glm::vec3(  m_extents.x,  m_extents.y,  m_extents.z )
    };
}

const std::type_index &BoxCollider::type() const {
    static std::type_index index(typeid(BoxCollider));
    return index;
}

glm::vec3 BoxCollider::compute_axis_inertia(Rigidbody &rigidbody) const {
    float ex2 =  4.0 * m_extents.x * m_extents.x;
    float ey2 =  4.0 * m_extents.y * m_extents.y;
    float ez2 =  4.0 * m_extents.z * m_extents.z;
    float x =  1.0 / 12.0 * rigidbody.mass * (ex2 + ex2);
    float y =  1.0 / 12.0 * rigidbody.mass * (ey2 + ey2);
    float z =  1.0 / 12.0 * rigidbody.mass * (ez2 + ez2);
    return glm::vec3(x, y, z);
}

EG_RAYTRACER_END
