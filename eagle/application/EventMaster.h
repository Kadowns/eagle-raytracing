//
// Created by Novak on 29/03/2020.
//

#ifndef EAGLE_EVENTMASTER_H
#define EAGLE_EVENTMASTER_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>
#include <eagle/application/editor/EditorWindow.h>
#include <eagle/core/events/EventDispatcher.h>

EG_RAYTRACER_BEGIN

struct OnRaytracerTargetCreated {
    OnRaytracerTargetCreated(const Reference<Image> target) : target(target) {}
    Reference<Image> target;
};

class EventMaster {
public:
    static EventDispatcher& instance(){
        static EventDispatcher s_instance;
        return s_instance;
    }
};

EG_RAYTRACER_END

#endif //EAGLE_EVENTMASTER_H
