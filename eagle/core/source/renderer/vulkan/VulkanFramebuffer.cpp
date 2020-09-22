//
// Created by Novak on 08/08/2020.
//

#include <eagle/core/renderer/vulkan/VulkanFramebuffer.h>

EG_BEGIN

VulkanFramebuffer::VulkanFramebuffer(const VulkanFramebufferCreateInfo &createInfo,
                                     uint32_t width, uint32_t height,
                                     const std::vector<Reference<VulkanImageAttachment>> &imageAttachments) :
                                     m_createInfo(createInfo),
                                     m_width(width), m_height(height),
                                     m_imageAttachments(imageAttachments) {
    create_framebuffer();
}

void VulkanFramebuffer::create_framebuffer() {

    std::vector<VkImageView> attachments;
    attachments.reserve(m_imageAttachments.size());
    for (auto& image : m_imageAttachments){
        attachments.emplace_back(image->view);
    }

    VkFramebufferCreateInfo framebufferCreateInfo = {};
    framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferCreateInfo.renderPass = m_createInfo.renderPass;
    framebufferCreateInfo.attachmentCount = attachments.size();
    framebufferCreateInfo.pAttachments = attachments.data();
    framebufferCreateInfo.width = m_width;
    framebufferCreateInfo.height = m_height;
    framebufferCreateInfo.layers = 1;

    VK_CALL vkCreateFramebuffer(m_createInfo.device, &framebufferCreateInfo, nullptr, &m_framebuffer);
}

EG_END
