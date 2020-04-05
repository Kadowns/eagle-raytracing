//
// Created by Novak on 19/06/2019.
//

#ifndef EAGLE_TEXTURE_H
#define EAGLE_TEXTURE_H

#include <vector>

#include "eagle/core/CoreGlobalDefinitions.h"
#include "RenderingCore.h"
#include "Image.h"

EG_BEGIN

using Pixel = unsigned char;

struct TextureCreateInfo{
    int width, height, bpp;
    int mipLevels, layerCount;
    Format format;
    Filter filter = Filter::LINEAR;
    TextureUsage usage = TextureUsage::READ;
    std::vector<Pixel> pixels;
};

class Texture {

public:
    explicit Texture(TextureCreateInfo textureInfo):
        m_mipLevels(textureInfo.mipLevels),
        m_layerCount(textureInfo.layerCount),
        m_format(textureInfo.format),
        m_filter(textureInfo.filter),
        m_usage(textureInfo.usage),
        m_pixels(std::move(textureInfo.pixels)){}
    virtual ~Texture() = default;
    inline const int get_mip_levels()             const { return m_mipLevels;   }
    inline const int get_layer_count()            const { return m_layerCount;  }
    inline const std::vector<Pixel>& get_pixels() const { return m_pixels;      }


    virtual Handle<Image> get_image() = 0;
    virtual void apply() = 0;


protected:
    int m_mipLevels, m_layerCount;
    Format m_format;
    Filter m_filter;
    TextureUsage m_usage;
    std::vector<Pixel> m_pixels;

};

EG_END

#endif //EAGLE_TEXTURE_H
