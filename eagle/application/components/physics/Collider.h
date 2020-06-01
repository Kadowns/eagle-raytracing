//
// Created by Novak on 5/2/2020.
//

#ifndef EAGLE_COLLIDER_H
#define EAGLE_COLLIDER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/components/physics/shapes/ColliderShape.h>

EG_RAYTRACER_BEGIN

struct Collider {
    Collider(Reference<ColliderShape>&& shape, uint32_t layer = 1) : shape(std::move(shape)), layer(layer){}
    Reference<ColliderShape> shape;
    uint32_t layer;
};

EG_RAYTRACER_END

#endif //EAGLE_COLLIDER_H
