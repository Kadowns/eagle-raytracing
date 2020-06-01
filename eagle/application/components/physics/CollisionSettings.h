//
// Created by Novak on 26/05/2020.
//

#ifndef EAGLE_COLLISIONSETTINGS_H
#define EAGLE_COLLISIONSETTINGS_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/systems/physics/collision/Collision.h>

EG_RAYTRACER_BEGIN

struct CollisionSettings {
    std::list<Collision> collisions;
};

EG_RAYTRACER_END

#endif //EAGLE_COLLISIONSETTINGS_H
