//
// Created by Novak on 12/04/2020.
//

#ifndef EAGLE_SCENE_H
#define EAGLE_SCENE_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

class Scene : public entityx::EntityX {
public:
    void update();
};

EG_RAYTRACER_END

#endif //EAGLE_SCENE_H
