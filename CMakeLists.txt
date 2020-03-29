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
        eagle/core/events/WindowEvents.h
        eagle/core/events/InputEvents.h
        eagle/core/events/KeyCodes.h
        eagle/core/InputLayer.h
        eagle/core/events/ImmediateEvent.h)

set(CORE_SOURCE
        eagle/core/source/CoreGlobalDefinitions.cpp
        eagle/core/source/Application.cpp
        eagle/core/source/Window.cpp
        eagle/core/source/WindowGLFW.cpp
        eagle/core/source/Log.cpp
        eagle/core/source/LayerStack.cpp
        eagle/core/source/Input.cpp
        eagle/core/source/InputLayer.cpp
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
        eagle/core/renderer/Texture2D.h
        eagle/core/renderer/Image.h
        eagle/core/renderer/RenderTarget.h
        eagle/core/renderer/DescriptorItem.h
        eagle/core/renderer/DescriptorSetLayout.h
        eagle/core/renderer/CommandBuffer.h
        eagle/core/renderer/ComputeShader.h
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
        eagle/core/renderer/vulkan/VulkanTexture2D.h
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
        )

set(RENDERER_SOURCE
        eagle/core/source/renderer/UniformBuffer.cpp
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
        eagle/core/source/renderer/vulkan/VulkanTexture2D.cpp
        eagle/core/source/renderer/vulkan/VulkanRenderTarget.cpp
        eagle/core/source/renderer/vulkan/spirv_reflect.cpp
        eagle/core/source/renderer/vulkan/VulkanConversor.cpp
        eagle/core/source/renderer/vulkan/VulkanCommandBuffer.cpp
        eagle/core/source/renderer/vulkan/VulkanCleaner.cpp
        eagle/core/source/renderer/vulkan/VulkanComputeShader.cpp
        eagle/core/source/renderer/vulkan/VulkanShaderUtils.cpp
        )

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

#raytracer-------------------------------------------------

add_subdirectory(${EG_EXTERNAL_PATH}/imgui ${CMAKE_BINARY_DIR}/imgui)
add_subdirectory(${EG_EXTERNAL_PATH}/glm ${CMAKE_BINARY_DIR}/glm)

set(RAYTRACER_INCLUDE
        eagle/raytracer/RaytracerGlobalDefinitions.h
        eagle/raytracer/Raytracer.h
        eagle/raytracer/renderer/RenderLayer.h
        eagle/raytracer/renderer/RenderMaster.h
        eagle/raytracer/editor/EditorMaster.h
        eagle/raytracer/editor/EditorLayer.h
        eagle/raytracer/editor/EditorWindow.h
        eagle/raytracer/editor/FooWindow.h
        eagle/raytracer/main/MainLayer.h)

set(RAYTRACER_SOURCE
        eagle/raytracer/source/renderer/RenderLayer.cpp
        eagle/raytracer/source/renderer/RenderMaster.cpp
        eagle/raytracer/source/editor/EditorLayer.cpp
        eagle/raytracer/source/editor/EditorMaster.cpp
        eagle/raytracer/source/editor/EditorWindow.cpp
        eagle/raytracer/source/editor/FooWindow.cpp
        eagle/raytracer/source/main/MainLayer.cpp)

set(RAYTRACER_ALL ${RAYTRACER_INCLUDE} ${RAYTRACER_SOURCE})

add_library(eagle_raytracer STATIC "${RAYTRACER_ALL}")

target_include_directories(
        eagle_raytracer
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(
        eagle_raytracer
        PROPERTIES
        LINKER_LANGUAGE CXX
)

define_file_basename_for_sources(eagle_raytracer)

target_link_libraries(eagle_raytracer eagle_core imgui glm)
#-----------------------------------------------------

add_executable(eagle eagle/EntryPoint.cpp eagle/Eagle.h)

define_file_basename_for_sources(eagle)


target_link_libraries(eagle eagle_raytracer)
