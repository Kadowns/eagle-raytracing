cmake_minimum_required(VERSION 3.14)

project(eagle)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(EG_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(EG_EXTERNAL_PATH ${EG_ROOT_PATH}/external)


option(BUILD_EG_ENGINE "Build eagle engine library" ON)
option(BUILD_EG_EDITOR "Build eagle editor executable (requires engine)" ON)

add_definitions(-DPROJECT_ROOT="${EG_ROOT_PATH}/data")
if(MSVC)
add_definitions(-D_ENABLE_EXTENDED_ALIGNED_STORAGE)
endif(MSVC)

find_package(GLFW REQUIRED)
find_package(SPDLOG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(GLSLANG REQUIRED)

set(CORE_INCLUDE
        eagle/Eagle.h
        eagle/core/Core.h
        eagle/core/CoreGlobalDefinitions.h
        eagle/core/Application.h
        eagle/core/Window.h
        eagle/core/Input.h
        eagle/core/WindowGLFW.h
        eagle/core/Log.h
        eagle/core/Layer.h
        eagle/core/LayerStack.h
        eagle/core/events/Event.h
        eagle/core/events/EventDispatcher.h
        eagle/core/events/WindowEvents.h
        eagle/core/events/InputEvents.h
        eagle/core/events/KeyCodes.h
        eagle/core/InputLayer.h
        eagle/core/events/ImmediateEvent.h
        eagle/core/Random.h
        eagle/core/Time.h
        )

set(CORE_SOURCE
        eagle/core/source/CoreGlobalDefinitions.cpp
        eagle/core/source/Application.cpp
        eagle/core/source/Window.cpp
        eagle/core/source/WindowGLFW.cpp
        eagle/core/source/Log.cpp
        eagle/core/source/LayerStack.cpp
        eagle/core/source/Input.cpp
        eagle/core/source/InputLayer.cpp
        eagle/core/source/Random.cpp
        eagle/core/source/Time.cpp
        )


set(CORE_ALL ${CORE_INCLUDE} ${CORE_SOURCE})


set(RENDERER_INCLUDE
        eagle/core/renderer/RenderingCore.h
        eagle/core/renderer/RenderingContext.h
        eagle/core/renderer/Shader.h
        eagle/core/renderer/VertexLayout.h
        eagle/core/renderer/VertexBuffer.h
        eagle/core/renderer/IndexBuffer.h
        eagle/core/renderer/UniformBuffer.h
        eagle/core/renderer/DescriptorSet.h
        eagle/core/renderer/Texture.h
        eagle/core/renderer/Image.h
        eagle/core/renderer/RenderTarget.h
        eagle/core/renderer/DescriptorItem.h
        eagle/core/renderer/DescriptorSetLayout.h
        eagle/core/renderer/CommandBuffer.h
        eagle/core/renderer/ComputeShader.h
        eagle/core/renderer/StorageBuffer.h
        eagle/core/renderer/vulkan/VulkanContext.h
        eagle/core/renderer/vulkan/VulkanCore.h
        eagle/core/renderer/vulkan/VulkanHelper.h
        eagle/core/renderer/vulkan/VulkanShader.h
        eagle/core/renderer/vulkan/VulkanShaderCompiler.h
        eagle/core/renderer/vulkan/VulkanBuffer.h
        eagle/core/renderer/vulkan/VulkanVertexBuffer.h
        eagle/core/renderer/vulkan/VulkanIndexBuffer.h
        eagle/core/renderer/vulkan/VulkanUniformBuffer.h
        eagle/core/renderer/vulkan/VulkanDescriptorSet.h
        eagle/core/renderer/vulkan/VulkanTexture.h
        eagle/core/renderer/vulkan/VulkanImage.h
        eagle/core/renderer/vulkan/VulkanRenderTarget.h
        eagle/core/renderer/vulkan/VulkanCommand.h
        eagle/core/renderer/vulkan/VulkanCommandList.h
        eagle/core/renderer/vulkan/spirv_reflect.h
        eagle/core/renderer/vulkan/VulkanDescriptorSetLayout.h
        eagle/core/renderer/vulkan/VulkanCommandBuffer.h
        eagle/core/renderer/vulkan/VulkanConversor.h
        eagle/core/renderer/vulkan/VulkanCleaner.h
        eagle/core/renderer/vulkan/VulkanComputeShader.h
        eagle/core/renderer/vulkan/VulkanShaderUtils.h
        eagle/core/renderer/vulkan/VulkanStorageBuffer.h
        eagle/core/renderer/Framebuffer.h eagle/core/renderer/vulkan/VulkanFramebuffer.h eagle/core/renderer/RenderPass.h)

set(RENDERER_SOURCE
        eagle/core/source/renderer/DescriptorSet.cpp
        eagle/core/source/renderer/VertexLayout.cpp
        eagle/core/source/renderer/vulkan/VulkanContext.cpp
        eagle/core/source/renderer/vulkan/VulkanHelper.cpp
        eagle/core/source/renderer/vulkan/VulkanCore.cpp
        eagle/core/source/renderer/vulkan/VulkanShader.cpp
        eagle/core/source/renderer/vulkan/VulkanShaderCompiler.cpp
        eagle/core/source/renderer/vulkan/VulkanBuffer.cpp
        eagle/core/source/renderer/vulkan/VulkanVertexBuffer.cpp
        eagle/core/source/renderer/vulkan/VulkanIndexBuffer.cpp
        eagle/core/source/renderer/vulkan/VulkanUniformBuffer.cpp
        eagle/core/source/renderer/vulkan/VulkanDescriptorSet.cpp
        eagle/core/source/renderer/vulkan/VulkanDescriptorSetLayout.cpp
        eagle/core/source/renderer/vulkan/VulkanTexture.cpp
        eagle/core/source/renderer/vulkan/VulkanRenderTarget.cpp
        eagle/core/source/renderer/vulkan/spirv_reflect.cpp
        eagle/core/source/renderer/vulkan/VulkanConversor.cpp
        eagle/core/source/renderer/vulkan/VulkanCommandBuffer.cpp
        eagle/core/source/renderer/vulkan/VulkanCleaner.cpp
        eagle/core/source/renderer/vulkan/VulkanComputeShader.cpp
        eagle/core/source/renderer/vulkan/VulkanShaderUtils.cpp
        eagle/core/source/renderer/vulkan/VulkanStorageBuffer.cpp
        eagle/core/source/renderer/vulkan/VulkanFramebuffer.cpp)

set(RENDERER_ALL ${RENDERER_INCLUDE} ${RENDERER_SOURCE})

set(EAGLE_ALL ${CORE_ALL} ${RENDERER_ALL})

add_library(eagle_core STATIC "${EAGLE_ALL}")

target_include_directories(
        eagle_core
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(
        eagle_core
        PROPERTIES
        LINKER_LANGUAGE CXX
)

include(cmake/Eagle.cmake)

define_file_basename_for_sources(eagle_core)

target_link_libraries(eagle_core GLFW spdlog Vulkan::Vulkan glslang OSDependent OGLCompiler HLSL SPIRV)

#engine-------------------------------------------------
add_subdirectory(${EG_EXTERNAL_PATH}/glm ${CMAKE_BINARY_DIR}/glm)
add_subdirectory(${EG_EXTERNAL_PATH}/stb ${CMAKE_BINARY_DIR}/stb)
add_subdirectory(${EG_EXTERNAL_PATH}/entityx ${CMAKE_BINARY_DIR}/entityx)

set(ENGINE_INCLUDE
        eagle/engine/EventMaster.h
        eagle/engine/EngineGlobalDefinitions.h
        eagle/engine/Engine.h
        eagle/engine/renderer/RenderLayer.h
        eagle/engine/renderer/RenderMaster.h
        eagle/engine/renderer/TextureLoader.h
        eagle/engine/components/Camera.h
        eagle/engine/components/CameraController.h
        eagle/engine/components/Transform.h
        eagle/engine/components/SceneData.h
        eagle/engine/components/RaytracerData.h
        eagle/engine/components/DirectionalLight.h
        eagle/engine/systems/RaytracerSystem.h
        eagle/engine/systems/CameraSystem.h
        eagle/engine/systems/LightSystem.h
        eagle/engine/components/SingletonComponent.h
        eagle/engine/components/Sphere.h
        eagle/engine/SceneLayer.h
        eagle/engine/systems/physics/PhysicsSystem.h
        eagle/engine/components/physics/Rigidbody.h
        eagle/engine/components/Box.h
        eagle/engine/systems/physics/CollisionSystem.h
        eagle/engine/components/physics/PhysicsSettings.h
        eagle/engine/components/physics/Collider.h
        eagle/engine/components/physics/shapes/BoxCollider.h
        eagle/engine/components/physics/shapes/ColliderShape.h
        eagle/engine/components/physics/shapes/SphereCollider.h
        eagle/engine/systems/physics/collision/CollisionManager.h
        eagle/engine/systems/physics/collision/Collision.h
        eagle/engine/components/physics/shapes/PlaneCollider.h
        eagle/engine/components/physics/CollisionSettings.h
        eagle/engine/systems/SpawnerSystem.h
        eagle/engine/components/Spawner.h
        eagle/engine/SceneManager.h
        eagle/engine/systems/PaintOnCollisionSystem.h
        )

set(ENGINE_SOURCE
        eagle/engine/source/renderer/RenderLayer.cpp
        eagle/engine/source/renderer/RenderMaster.cpp
        eagle/engine/source/renderer/TextureLoader.cpp
        eagle/engine/source/systems/RaytracerSystem.cpp
        eagle/engine/source/systems/CameraSystem.cpp
        eagle/engine/source/systems/LightSystem.cpp
        eagle/engine/source/SceneLayer.cpp
        eagle/engine/source/systems/physics/PhysicsSystem.cpp
        eagle/engine/source/systems/physics/collision/shapes/SphereCollider.cpp
        eagle/engine/source/systems/physics/collision/shapes/ColliderShape.cpp
        eagle/engine/source/systems/physics/collision/shapes/BoxCollider.cpp
        eagle/engine/source/systems/physics/collision/CollisionManager.cpp
        eagle/engine/source/systems/physics/collision/shapes/PlaneCollider.cpp
        eagle/engine/source/systems/physics/CollisionSystem.cpp
        eagle/engine/source/systems/SpawnerSystem.cpp
        )

set(ENGINE_ALL ${ENGINE_INCLUDE} ${ENGINE_SOURCE})

add_library(eagle_engine STATIC "${ENGINE_ALL}")

target_include_directories(
        eagle_engine
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(
        eagle_engine
        PROPERTIES
        LINKER_LANGUAGE CXX
)

define_file_basename_for_sources(eagle_engine)

target_link_libraries(eagle_engine eagle_core imgui glm stb entityx)
#-----------------------------------------------------


#editor-----------------------------------------------
add_subdirectory(${EG_EXTERNAL_PATH}/imgui ${CMAKE_BINARY_DIR}/imgui)
set(EDITOR_INCLUDE
        eagle/editor/EditorMaster.h
        eagle/editor/EditorLayer.h
        eagle/editor/window/EditorWindow.h
        eagle/editor/window/ComputeDataEditor.h
        eagle/editor/window/EditorDockingWindow.h
        eagle/editor/window/SceneWindow.h
        eagle/editor/window/DebugSettingsWindow.h
        eagle/editor/EditorGlobalDefinitions.h eagle/editor/Editor.h)

set(EDITOR_SOURCE
        eagle/editor/source/EditorLayer.cpp
        eagle/editor/source/EditorMaster.cpp
        eagle/editor/source/window/EditorWindow.cpp
        eagle/editor/source/window/ComputeDataEditor.cpp
        eagle/editor/source/window/EditorDockingWindow.cpp
        eagle/editor/source/window/SceneWindow.cpp
        eagle/editor/source/window/DebugSettingsWindow.cpp
        )

set(EDITOR_ALL ${EDITOR_INCLUDE} ${EDITOR_SOURCE})

add_library(eagle_editor STATIC "${EDITOR_ALL}")

target_include_directories(
        eagle_editor
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(
        eagle_editor
        PROPERTIES
        LINKER_LANGUAGE CXX
)

define_file_basename_for_sources(eagle_editor)


target_link_libraries(eagle_editor eagle_engine imgui)
#-----------------------------------------------------

add_executable(eagle eagle/EntryPoint.cpp eagle/Eagle.h)

define_file_basename_for_sources(eagle)

target_link_libraries(eagle eagle_editor)
