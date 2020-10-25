//
// Created by Novak on 25/06/2019.
//

#ifndef EAGLE_IMAGE_H
#define EAGLE_IMAGE_H

#include "DescriptorItem.h"
#include "RenderingCore.h"

EG_BEGIN

struct ImageCreateInfo {
    uint32_t width, height;
    uint32_t mipLevels, arrayLayers;
    Format format;
    ImageTiling tiling;
    ImageLayout layout;
    std::vector<unsigned char> bufferData;
    std::vector<ImageUsage> usages;
    std::vector<MemoryProperty> memoryProperties;
    std::vector<ImageAspect> aspects;
};

class Image : public DescriptorItem {
public:

    Image(const ImageCreateInfo& createInfo) :
        DescriptorItem(DescriptorType::SAMPLED_IMAGE),
        m_createInfo(createInfo) {}

    virtual ~Image() = default;

    inline uint32_t width() const { return m_createInfo.width; }
    inline uint32_t height() const { return m_createInfo.height; }
    inline void resize(uint32_t width, uint32_t height) {
        m_createInfo.width = width;
        m_createInfo.height = height;
        on_resize();
    }

protected:
    virtual void on_resize() = 0;

protected:
    ImageCreateInfo m_createInfo;
};

EG_END

#endif //EAGLE_IMAGE_H
