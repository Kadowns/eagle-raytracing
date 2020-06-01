//
// Created by Novak on 5/3/2020.
//

#ifndef EAGLE_BOXCOLLIDER_H
#define EAGLE_BOXCOLLIDER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/components/physics/shapes/ColliderShape.h>

EG_RAYTRACER_BEGIN

class BoxCollider : public ColliderShape {
public:
    BoxCollider(const glm::vec3 extents);
    virtual const std::type_index &type() const override;
    virtual glm::vec3 compute_axis_inertia(Rigidbody& rigidbody)const override;
    inline glm::vec3 extents() const { return m_extents; }
    inline std::array<glm::vec3, 8> vertices() const { return m_vertices; }
private:
    glm::vec3 m_extents;
    std::array<glm::vec3, 8> m_vertices;
};

EG_RAYTRACER_END

#endif //EAGLE_BOXCOLLIDER_H
