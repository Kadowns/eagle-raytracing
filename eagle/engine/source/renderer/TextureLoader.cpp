//
// Created by Novak on 04/04/2020.
//

#include <eagle/engine/renderer/TextureLoader.h>
#include <stb/stb_image.h>

EG_ENGINE_BEGIN

TextureCreateInfo TextureLoader::load_pixels(const std::string &path) {
    //assert(stbi_is_hdr(path.c_str()));
    //stbi_hdr_to_ldr_gamma(2.2f);
    TextureCreateInfo createInfo = {};
    if (stbi_is_hdr(path.c_str())){
        Pixel* pixels = (Pixel*)stbi_load(path.c_str(), &createInfo.width, &createInfo.height, &createInfo.bpp, STBI_rgb_alpha);
        if (!pixels){
            throw std::runtime_error("Failed to load image: " + std::string(stbi_failure_reason()));
        }

        int len = createInfo.width * createInfo.height * 4;
        createInfo.pixels.resize(len);
        memcpy(createInfo.pixels.data(), pixels, len);
        stbi_image_free(pixels);
    }

    if (createInfo.bpp == 4){
        createInfo.format = Format::R8G8B8A8_UNORM;
    }
    else if (createInfo.bpp == 3){
        createInfo.format = Format::R8G8B8A8_UNORM;
    }
    createInfo.mipLevels = 1;
    createInfo.layerCount = 1;
    return createInfo;
}


EG_ENGINE_END


