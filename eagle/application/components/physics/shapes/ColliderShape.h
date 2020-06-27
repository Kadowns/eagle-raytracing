//
// Created by Novak on 5/3/2020.
//

#ifndef EAGLE_COLLIDERSHAPE_H
#define EAGLE_COLLIDERSHAPE_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/components/physics/Rigidbody.h>

EG_RAYTRACER_BEGIN

class ColliderShape {
public:
    struct AABB {
        glm::vec3 min, max;
    };
public:
    virtual const std::type_index& type() const = 0;
    virtual void compute_aabb(const Rigidbody::Transform& transform) = 0;
    void compute_inertia(Rigidbody& rigidbody) const;
    inline AABB aabb() const { return m_aabb; }
protected:
    virtual glm::vec3 compute_axis_inertia(Rigidbody& rigidbody)const = 0;
protected:
    AABB m_aabb;
};

EG_RAYTRACER_END

#endif //EAGLE_COLLIDERSHAPE_H
