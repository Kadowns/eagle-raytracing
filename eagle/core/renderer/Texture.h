//
// Created by Novak on 19/06/2019.
//

#ifndef EAGLE_TEXTURE_H
#define EAGLE_TEXTURE_H

#include <utility>
#include <vector>

#include "eagle/core/CoreGlobalDefinitions.h"
#include "RenderingCore.h"
#include "Image.h"

EG_BEGIN

using Pixel = unsigned char;

struct TextureCreateInfo {
    Reference<Image> image;
    Filter filter = Filter::LINEAR;
};

class Texture {

public:
    explicit Texture(TextureCreateInfo createInfo):
            m_createInfo(std::move(createInfo)){}
    virtual ~Texture();


    inline const Reference<Image>& image() const { return m_createInfo.image; }

protected:
    TextureCreateInfo m_createInfo;
};

EG_END

#endif //EAGLE_TEXTURE_H
