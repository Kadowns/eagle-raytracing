//
// Created by Novak on 29/03/2020.
//

#ifndef EAGLE_EVENTMASTER_H
#define EAGLE_EVENTMASTER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/EventManager.h>

EG_RAYTRACER_BEGIN

struct OnRaytracerTargetCreated {
    OnRaytracerTargetCreated(const Reference<Texture2D> target) : target(target) {}
    Reference<Texture2D> target;
};

class EventMaster {
public:
    static EventManager& instance(){
        static EventManager s_instance;
        return s_instance;
    }
};

EG_RAYTRACER_END

#endif //EAGLE_EVENTMASTER_H
