//
// Created by Novak on 09/04/2020.
//

#include <eagle/application/systems/LightSystem.h>
#include <eagle/application/components/Transform.h>
#include <eagle/application/components/DirectionalLight.h>

EG_RAYTRACER_BEGIN

void LightSystem::configure(entityx::EntityManager &entities, entityx::EventManager &events) {
    entities.each<DirectionalLight, Transform>([](entityx::Entity e, DirectionalLight& light, Transform& transform){
        light.direction = transform.front();
        transform.hasChanged = true;
    });
}

void LightSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    entities.each<DirectionalLight, Transform>([&events](entityx::Entity e, DirectionalLight& light, Transform& transform){
        if (transform.hasChanged){
            light.direction = transform.front();
            events.emit<OnLightUpdate>(light);
            transform.hasChanged = false;
        }
    });
}


EG_RAYTRACER_END


