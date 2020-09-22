//
// Created by Novak on 08/08/2020.
//

#ifndef EAGLE_VULKANFRAMEBUFFER_H
#define EAGLE_VULKANFRAMEBUFFER_H

#include <eagle/core/renderer/vulkan/VulkanCore.h>
#include <eagle/core/renderer/vulkan/VulkanImage.h>
#include <eagle/core/renderer/Framebuffer.h>

EG_BEGIN

struct VulkanFramebufferCreateInfo {
    VkDevice device;
    VkRenderPass renderPass;
};


class VulkanFramebuffer : public Framebuffer {
public:
    VulkanFramebuffer(const VulkanFramebufferCreateInfo& createInfo, uint32_t width, uint32_t height, const std::vector<Reference<VulkanImageAttachment>>& imageAttachments);
    inline std::vector<Reference<VulkanImageAttachment>>& get_image_attachments() { return m_imageAttachments; }
private:
    void create_framebuffer();
private:
    VulkanFramebufferCreateInfo m_createInfo;
    uint32_t m_width, m_height;
    std::vector<Reference<VulkanImageAttachment>> m_imageAttachments;
    VkFramebuffer m_framebuffer;
};

EG_END

#endif //EAGLE_VULKANFRAMEBUFFER_H
