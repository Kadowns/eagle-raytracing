//
// Created by Novak on 30/03/2020.
//

#ifndef EAGLE_TRANSFORM_H
#define EAGLE_TRANSFORM_H

#include <eagle/application/RaytracerApplicationGlobalDefinitions.h>

EG_RAYTRACER_BEGIN

struct Transform {
    Transform() : position(0), rotation(glm::vec3(0)), scale(0) {}
    Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale) :
        position(position), rotation(rotation), scale(scale) {}

    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    inline glm::vec3 front()   const { return rotation * glm::vec3(0.0f, 0.0f, -1.0f); }
    inline glm::vec3 up()      const { return rotation * glm::vec3(0.0f, 1.0f, 0.0f);  }
    inline glm::vec3 right()   const { return rotation * glm::vec3(1.0f, 0.0f, 0.0f);  }
    inline glm::mat4 matrix()  const { return glm::scale(glm::translate(glm::mat4(1), position) * glm::mat4_cast(rotation), scale);}
};


EG_RAYTRACER_END

#endif //EAGLE_TRANSFORM_H
