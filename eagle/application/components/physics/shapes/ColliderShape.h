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
    virtual const std::type_index& type() const = 0;
    void compute_inertia(Rigidbody& rigidbody) const;
protected:
    virtual glm::vec3 compute_axis_inertia(Rigidbody& rigidbody)const = 0;
};

EG_RAYTRACER_END

#endif //EAGLE_COLLIDERSHAPE_H
