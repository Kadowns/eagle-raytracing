//
// Created by Novak on 08/05/2020.
//

#ifndef EAGLE_COLLISIONSOLVER_H
#define EAGLE_COLLISIONSOLVER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/systems/physics/collision/Collision.h>

EG_RAYTRACER_BEGIN

class CollisionSolver {
public:
    CollisionSolver(std::list<Collision> &collisions);
    void pre_solve(float dt);
    void solve();
    void finish();
private:
    std::list<Collision>& m_collisions;
};

EG_RAYTRACER_END

#endif //EAGLE_COLLISIONSOLVER_H
