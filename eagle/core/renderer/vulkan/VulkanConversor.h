//
// Created by Novak on 31/08/2019.
//

#ifndef EAGLE_VULKANCONVERSOR_H
#define EAGLE_VULKANCONVERSOR_H

#include <eagle/core/renderer/RenderPass.h>
#include "VulkanCore.h"

EG_BEGIN

class VulkanConversor {
public:
    static VkFormat           to_vk(Format format);
    static Format           to_eg(VkFormat format);
    static VkShaderStageFlags to_vk(ShaderStage stage);
    static ShaderStage      to_eg(VkShaderStageFlags stage);
    static VkDescriptorType   to_vk(DescriptorType type);
    static DescriptorType   to_eg(VkDescriptorType type);
    static VkFilter           to_vk(Filter filter);
    static Filter           to_eg(VkFilter filter);
    static VkPrimitiveTopology to_vk(PrimitiveTopology topology);
    static PrimitiveTopology to_eg(VkPrimitiveTopology topology);
    static AttachmentLoadOperator to_eg(VkAttachmentLoadOp op);
    static VkAttachmentLoadOp to_vk(AttachmentLoadOperator op);
    static AttachmentStoreOperator to_eg(VkAttachmentStoreOp op);
    static VkAttachmentStoreOp to_vk(AttachmentStoreOperator op);
    static VkImageLayout to_vk(ImageLayout op);
    static ImageLayout to_eg(VkImageLayout op);
    static VkAttachmentDescription to_vk(const RenderAttachmentDescription &egAttachment);
    static RenderAttachmentDescription to_eg(const VkAttachmentDescription &egAttachment);
};

EG_END

#endif //EAGLE_VULKANCONVERSOR_H
