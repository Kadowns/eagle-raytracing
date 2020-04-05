//
// Created by Novak on 19/06/2019.
//

#ifndef EAGLE_VULKANTEXTURE_H
#define EAGLE_VULKANTEXTURE_H

#include "eagle/core/renderer/Texture.h"
#include "VulkanCore.h"
#include "VulkanBuffer.h"
#include "VulkanImage.h"

EG_BEGIN

struct VulkanTextureCreateInfo {
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkCommandPool commandPool;
    VkQueue graphicsQueue;
};

class VulkanTexture : public Texture {
public:
    VulkanTexture(const TextureCreateInfo &textureCreateInfo,
                    const VulkanTextureCreateInfo &vulkanInfo);
    ~VulkanTexture();

    virtual void apply() override;

    virtual Handle<Image> get_image() override;


private:

    Reference<VulkanBuffer> create_staging_buffer();

    void copy_buffer_to_image(const Reference<VulkanBuffer>& buffer, VkImage image, uint32_t width, uint32_t height);

private:
    VulkanTextureCreateInfo m_vulkanInfo;
    Reference<VulkanImage> m_image;
};

EG_END

#endif //EAGLE_VULKANTEXTURE_H
