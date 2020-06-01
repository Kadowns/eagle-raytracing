//
// Created by Novak on 17/03/2020.
//

#ifndef EAGLE_RAYTRACERAPPLICATIONGLOBALDEFINITIONS_H
#define EAGLE_RAYTRACERAPPLICATIONGLOBALDEFINITIONS_H

#include <eagle/core/Core.h>

#include <entityx/entityx.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/norm.hpp>

#define EG_RAYTRACER_BEGIN namespace Eagle::Raytracer {
#define EG_RAYTRACER_END   }

inline const std::string ProjectRoot = PROJECT_ROOT;

#endif //EAGLE_COREGLOBALDEFINITIONS_H