//
// Created by Novak on 5/3/2020.
//

#ifndef EAGLE_SPHERECOLLIDER_H
#define EAGLE_SPHERECOLLIDER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/components/physics/shapes/ColliderShape.h>

EG_RAYTRACER_BEGIN

class SphereCollider : public ColliderShape {
public:
    SphereCollider(float radius);
    virtual const std::type_index &type() const override;
    virtual glm::vec3 compute_axis_inertia(Rigidbody& rigidbody)const override;

    virtual void compute_aabb(const Rigidbody::Transform &transform) override;

    inline float radius() const { return m_radius; }
private:
    float m_radius;
};


EG_RAYTRACER_END

#endif //EAGLE_SPHERECOLLIDER_H
