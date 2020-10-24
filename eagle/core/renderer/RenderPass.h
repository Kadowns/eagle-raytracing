//
// Created by Novak on 07/09/2020.
//

#ifndef EAGLE_RENDERPASS_H
#define EAGLE_RENDERPASS_H

#include <eagle/core/renderer/RenderingCore.h>

EG_BEGIN

struct RenderAttachmentDescription {
    Format format;
    AttachmentOperator loadOp;
    AttachmentOperator storeOp;
    ImageLayout initialLayout;
    ImageLayout finalLayout;
};

class RenderPass {
public:

    RenderPass(const std::vector<RenderAttachmentDescription>& colorAttachments, const RenderAttachmentDescription& depthAttachment) :
        m_colorAttachments(colorAttachments),
        m_depthAttachment(depthAttachment) {}
    RenderPass(const RenderAttachmentDescription& colorAttachment, const RenderAttachmentDescription& depthAttachment) :
        RenderPass(std::vector<RenderAttachmentDescription>{colorAttachment}, depthAttachment) {}

    virtual ~RenderPass() = default;

    inline const std::vector<RenderAttachmentDescription>& color_attachments() const { return m_colorAttachments; }
    inline const RenderAttachmentDescription& depth_attachment() const { return m_depthAttachment; }

protected:
    const std::vector<RenderAttachmentDescription> m_colorAttachments;
    const RenderAttachmentDescription m_depthAttachment;
};

EG_END


#endif //EAGLE_RENDERPASS_H
