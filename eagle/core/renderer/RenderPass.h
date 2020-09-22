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

};

EG_END


#endif //EAGLE_RENDERPASS_H
