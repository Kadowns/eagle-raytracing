//
// Created by Novak on 31/08/2019.
//

#include <eagle/core/renderer/vulkan/VulkanConversor.h>

EG_BEGIN

VkFormat VulkanConversor::to_vk(Format format) {

    VkFormat result = VK_FORMAT_UNDEFINED;
    switch(format){
        case Format::UNDEFINED: result = VK_FORMAT_UNDEFINED; break;
        case Format::R4G4_UNORM_PACK8: result = VK_FORMAT_R4G4_UNORM_PACK8; break;
        case Format::R4G4B4A4_UNORM_PACK16: result = VK_FORMAT_R4G4B4A4_UNORM_PACK16; break;
        case Format::B4G4R4A4_UNORM_PACK16: result = VK_FORMAT_B4G4R4A4_UNORM_PACK16; break;
        case Format::R5G6B5_UNORM_PACK16: result = VK_FORMAT_R5G6B5_UNORM_PACK16; break;
        case Format::B5G6R5_UNORM_PACK16: result = VK_FORMAT_B5G6R5_UNORM_PACK16; break;
        case Format::R5G5B5A1_UNORM_PACK16: result = VK_FORMAT_R5G5B5A1_UNORM_PACK16; break;
        case Format::B5G5R5A1_UNORM_PACK16: result = VK_FORMAT_B5G5R5A1_UNORM_PACK16; break;
        case Format::A1R5G5B5_UNORM_PACK16: result = VK_FORMAT_A1R5G5B5_UNORM_PACK16; break;
        case Format::R8_UNORM: result = VK_FORMAT_R8_UNORM; break;
        case Format::R8_SNORM: result = VK_FORMAT_R8_SNORM; break;
        case Format::R8_USCALED: result = VK_FORMAT_R8_USCALED; break;
        case Format::R8_SSCALED: result = VK_FORMAT_R8_SSCALED; break;
        case Format::R8_UINT: result = VK_FORMAT_R8_UINT; break;
        case Format::R8_SINT: result = VK_FORMAT_R8_SINT; break;
        case Format::R8_SRGB: result = VK_FORMAT_R8_SRGB; break;
        case Format::R8G8_UNORM: result = VK_FORMAT_R8G8_UNORM; break;
        case Format::R8G8_SNORM: result = VK_FORMAT_R8G8_SNORM; break;
        case Format::R8G8_USCALED: result = VK_FORMAT_R8G8_USCALED; break;
        case Format::R8G8_SSCALED: result = VK_FORMAT_R8G8_SSCALED; break;
        case Format::R8G8_UINT: result = VK_FORMAT_R8G8_UINT; break;
        case Format::R8G8_SINT: result = VK_FORMAT_R8G8_SINT; break;
        case Format::R8G8_SRGB: result = VK_FORMAT_R8G8_SRGB; break;
        case Format::R8G8B8_UNORM: result = VK_FORMAT_R8G8B8_UNORM; break;
        case Format::R8G8B8_SNORM: result = VK_FORMAT_R8G8B8_SNORM; break;
        case Format::R8G8B8_USCALED: result = VK_FORMAT_R8G8B8_USCALED; break;
        case Format::R8G8B8_SSCALED: result = VK_FORMAT_R8G8B8_SSCALED; break;
        case Format::R8G8B8_UINT: result = VK_FORMAT_R8G8B8_UINT; break;
        case Format::R8G8B8_SINT: result = VK_FORMAT_R8G8B8_SINT; break;
        case Format::R8G8B8_SRGB: result = VK_FORMAT_R8G8B8_SRGB; break;
        case Format::B8G8R8_UNORM: result = VK_FORMAT_B8G8R8_UNORM; break;
        case Format::B8G8R8_SNORM: result = VK_FORMAT_B8G8R8_SNORM; break;
        case Format::B8G8R8_USCALED: result = VK_FORMAT_B8G8R8_USCALED; break;
        case Format::B8G8R8_SSCALED: result = VK_FORMAT_B8G8R8_SSCALED; break;
        case Format::B8G8R8_UINT: result = VK_FORMAT_B8G8R8_UINT; break;
        case Format::B8G8R8_SINT: result = VK_FORMAT_B8G8R8_SINT; break;
        case Format::B8G8R8_SRGB: result = VK_FORMAT_B8G8R8_SRGB; break;
        case Format::R8G8B8A8_UNORM: result = VK_FORMAT_R8G8B8A8_UNORM; break;
        case Format::R8G8B8A8_SNORM: result = VK_FORMAT_R8G8B8A8_SNORM; break;
        case Format::R8G8B8A8_USCALED: result = VK_FORMAT_R8G8B8A8_USCALED; break;
        case Format::R8G8B8A8_SSCALED: result = VK_FORMAT_R8G8B8A8_SSCALED; break;
        case Format::R8G8B8A8_UINT: result = VK_FORMAT_R8G8B8A8_UINT; break;
        case Format::R8G8B8A8_SINT: result = VK_FORMAT_R8G8B8A8_SINT; break;
        case Format::R8G8B8A8_SRGB: result = VK_FORMAT_R8G8B8A8_SRGB; break;
        case Format::B8G8R8A8_UNORM: result = VK_FORMAT_B8G8R8A8_UNORM; break;
        case Format::B8G8R8A8_SNORM: result = VK_FORMAT_B8G8R8A8_SNORM; break;
        case Format::B8G8R8A8_USCALED: result = VK_FORMAT_B8G8R8A8_USCALED; break;
        case Format::B8G8R8A8_SSCALED: result = VK_FORMAT_B8G8R8A8_SSCALED; break;
        case Format::B8G8R8A8_UINT: result = VK_FORMAT_B8G8R8A8_UINT; break;
        case Format::B8G8R8A8_SINT: result = VK_FORMAT_B8G8R8A8_SINT; break;
        case Format::B8G8R8A8_SRGB: result = VK_FORMAT_B8G8R8A8_SRGB; break;
        case Format::A8B8G8R8_UNORM_PACK32: result = VK_FORMAT_A8B8G8R8_UNORM_PACK32; break;
        case Format::A8B8G8R8_SNORM_PACK32: result = VK_FORMAT_A8B8G8R8_SNORM_PACK32; break;
        case Format::A8B8G8R8_USCALED_PACK32: result = VK_FORMAT_A8B8G8R8_USCALED_PACK32; break;
        case Format::A8B8G8R8_SSCALED_PACK32: result = VK_FORMAT_A8B8G8R8_SSCALED_PACK32; break;
        case Format::A8B8G8R8_UINT_PACK32: result = VK_FORMAT_A8B8G8R8_UINT_PACK32; break;
        case Format::A8B8G8R8_SINT_PACK32: result = VK_FORMAT_A8B8G8R8_SINT_PACK32; break;
        case Format::A8B8G8R8_SRGB_PACK32: result = VK_FORMAT_A8B8G8R8_SRGB_PACK32; break;
        case Format::A2R10G10B10_UNORM_PACK32: result = VK_FORMAT_A2R10G10B10_UNORM_PACK32; break;
        case Format::A2R10G10B10_SNORM_PACK32: result = VK_FORMAT_A2R10G10B10_SNORM_PACK32; break;
        case Format::A2R10G10B10_USCALED_PACK32: result = VK_FORMAT_A2R10G10B10_USCALED_PACK32; break;
        case Format::A2R10G10B10_SSCALED_PACK32: result = VK_FORMAT_A2R10G10B10_SSCALED_PACK32; break;
        case Format::A2R10G10B10_UINT_PACK32: result = VK_FORMAT_A2R10G10B10_UINT_PACK32; break;
        case Format::A2R10G10B10_SINT_PACK32: result = VK_FORMAT_A2R10G10B10_SINT_PACK32; break;
        case Format::A2B10G10R10_UNORM_PACK32: result = VK_FORMAT_A2B10G10R10_UNORM_PACK32; break;
        case Format::A2B10G10R10_SNORM_PACK32: result = VK_FORMAT_A2B10G10R10_SNORM_PACK32; break;
        case Format::A2B10G10R10_USCALED_PACK32: result = VK_FORMAT_A2B10G10R10_USCALED_PACK32; break;
        case Format::A2B10G10R10_SSCALED_PACK32: result = VK_FORMAT_A2B10G10R10_SSCALED_PACK32; break;
        case Format::A2B10G10R10_UINT_PACK32: result = VK_FORMAT_A2B10G10R10_UINT_PACK32; break;
        case Format::A2B10G10R10_SINT_PACK32: result = VK_FORMAT_A2B10G10R10_SINT_PACK32; break;
        case Format::R16_UNORM: result = VK_FORMAT_R16_UNORM; break;
        case Format::R16_SNORM: result = VK_FORMAT_R16_SNORM; break;
        case Format::R16_USCALED: result = VK_FORMAT_R16_USCALED; break;
        case Format::R16_SSCALED: result = VK_FORMAT_R16_SSCALED; break;
        case Format::R16_UINT: result = VK_FORMAT_R16_UINT; break;
        case Format::R16_SINT: result = VK_FORMAT_R16_SINT; break;
        case Format::R16_SFLOAT: result = VK_FORMAT_R16_SFLOAT; break;
        case Format::R16G16_UNORM: result = VK_FORMAT_R16G16_UNORM; break;
        case Format::R16G16_SNORM: result = VK_FORMAT_R16G16_SNORM; break;
        case Format::R16G16_USCALED: result = VK_FORMAT_R16G16_USCALED; break;
        case Format::R16G16_SSCALED: result = VK_FORMAT_R16G16_SSCALED; break;
        case Format::R16G16_UINT: result = VK_FORMAT_R16G16_UINT; break;
        case Format::R16G16_SINT: result = VK_FORMAT_R16G16_SINT; break;
        case Format::R16G16_SFLOAT: result = VK_FORMAT_R16G16_SFLOAT; break;
        case Format::R16G16B16_UNORM: result = VK_FORMAT_R16G16B16_UNORM; break;
        case Format::R16G16B16_SNORM: result = VK_FORMAT_R16G16B16_SNORM; break;
        case Format::R16G16B16_USCALED: result = VK_FORMAT_R16G16B16_USCALED; break;
        case Format::R16G16B16_SSCALED: result = VK_FORMAT_R16G16B16_SSCALED; break;
        case Format::R16G16B16_UINT: result = VK_FORMAT_R16G16B16_UINT; break;
        case Format::R16G16B16_SINT: result = VK_FORMAT_R16G16B16_SINT; break;
        case Format::R16G16B16_SFLOAT: result = VK_FORMAT_R16G16B16_SFLOAT; break;
        case Format::R16G16B16A16_UNORM: result = VK_FORMAT_R16G16B16A16_UNORM; break;
        case Format::R16G16B16A16_SNORM: result = VK_FORMAT_R16G16B16A16_SNORM; break;
        case Format::R16G16B16A16_USCALED: result = VK_FORMAT_R16G16B16A16_USCALED; break;
        case Format::R16G16B16A16_SSCALED: result = VK_FORMAT_R16G16B16A16_SSCALED; break;
        case Format::R16G16B16A16_UINT: result = VK_FORMAT_R16G16B16A16_UINT; break;
        case Format::R16G16B16A16_SINT: result = VK_FORMAT_R16G16B16A16_SINT; break;
        case Format::R16G16B16A16_SFLOAT: result = VK_FORMAT_R16G16B16A16_SFLOAT; break;
        case Format::R32_UINT: result = VK_FORMAT_R32_UINT; break;
        case Format::R32_SINT: result = VK_FORMAT_R32_SINT; break;
        case Format::R32_SFLOAT: result = VK_FORMAT_R32_SFLOAT; break;
        case Format::R32G32_UINT: result = VK_FORMAT_R32G32_UINT; break;
        case Format::R32G32_SINT: result = VK_FORMAT_R32G32_SINT; break;
        case Format::R32G32_SFLOAT: result = VK_FORMAT_R32G32_SFLOAT; break;
        case Format::R32G32B32_UINT: result = VK_FORMAT_R32G32B32_UINT; break;
        case Format::R32G32B32_SINT: result = VK_FORMAT_R32G32B32_SINT; break;
        case Format::R32G32B32_SFLOAT: result = VK_FORMAT_R32G32B32_SFLOAT; break;
        case Format::R32G32B32A32_UINT: result = VK_FORMAT_R32G32B32A32_UINT; break;
        case Format::R32G32B32A32_SINT: result = VK_FORMAT_R32G32B32A32_SINT; break;
        case Format::R32G32B32A32_SFLOAT: result = VK_FORMAT_R32G32B32A32_SFLOAT; break;
        case Format::R64_UINT: result = VK_FORMAT_R64_UINT; break;
        case Format::R64_SINT: result = VK_FORMAT_R64_SINT; break;
        case Format::R64_SFLOAT: result = VK_FORMAT_R64_SFLOAT; break;
        case Format::R64G64_UINT: result = VK_FORMAT_R64G64_UINT; break;
        case Format::R64G64_SINT: result = VK_FORMAT_R64G64_SINT; break;
        case Format::R64G64_SFLOAT: result = VK_FORMAT_R64G64_SFLOAT; break;
        case Format::R64G64B64_UINT: result = VK_FORMAT_R64G64B64_UINT; break;
        case Format::R64G64B64_SINT: result = VK_FORMAT_R64G64B64_SINT; break;
        case Format::R64G64B64_SFLOAT: result = VK_FORMAT_R64G64B64_SFLOAT; break;
        case Format::R64G64B64A64_UINT: result = VK_FORMAT_R64G64B64A64_UINT; break;
        case Format::R64G64B64A64_SINT: result = VK_FORMAT_R64G64B64A64_SINT; break;
        case Format::R64G64B64A64_SFLOAT: result = VK_FORMAT_R64G64B64A64_SFLOAT; break;
        case Format::B10G11R11_UFLOAT_PACK32: result = VK_FORMAT_B10G11R11_UFLOAT_PACK32; break;
        case Format::E5B9G9R9_UFLOAT_PACK32: result = VK_FORMAT_E5B9G9R9_UFLOAT_PACK32; break;
        case Format::D16_UNORM: result = VK_FORMAT_D16_UNORM; break;
        case Format::X8_D24_UNORM_PACK32: result = VK_FORMAT_X8_D24_UNORM_PACK32; break;
        case Format::D32_SFLOAT: result = VK_FORMAT_D32_SFLOAT; break;
        case Format::S8_UINT: result = VK_FORMAT_S8_UINT; break;
        case Format::D16_UNORM_S8_UINT: result = VK_FORMAT_D16_UNORM_S8_UINT; break;
        case Format::D24_UNORM_S8_UINT: result = VK_FORMAT_D24_UNORM_S8_UINT; break;
        case Format::D32_SFLOAT_S8_UINT: result = VK_FORMAT_D32_SFLOAT_S8_UINT; break;
        case Format::BC1_RGB_UNORM_BLOCK: result = VK_FORMAT_BC1_RGB_UNORM_BLOCK; break;
        case Format::BC1_RGB_SRGB_BLOCK: result = VK_FORMAT_BC1_RGB_SRGB_BLOCK; break;
        case Format::BC1_RGBA_UNORM_BLOCK: result = VK_FORMAT_BC1_RGBA_UNORM_BLOCK; break;
        case Format::BC1_RGBA_SRGB_BLOCK: result = VK_FORMAT_BC1_RGBA_SRGB_BLOCK; break;
        case Format::BC2_UNORM_BLOCK: result = VK_FORMAT_BC2_UNORM_BLOCK; break;
        case Format::BC2_SRGB_BLOCK: result = VK_FORMAT_BC2_SRGB_BLOCK; break;
        case Format::BC3_UNORM_BLOCK: result = VK_FORMAT_BC3_UNORM_BLOCK; break;
        case Format::BC3_SRGB_BLOCK: result = VK_FORMAT_BC3_SRGB_BLOCK; break;
        case Format::BC4_UNORM_BLOCK: result = VK_FORMAT_BC4_UNORM_BLOCK; break;
        case Format::BC4_SNORM_BLOCK: result = VK_FORMAT_BC4_SNORM_BLOCK; break;
        case Format::BC5_UNORM_BLOCK: result = VK_FORMAT_BC5_UNORM_BLOCK; break;
        case Format::BC5_SNORM_BLOCK: result = VK_FORMAT_BC5_SNORM_BLOCK; break;
        case Format::BC6H_UFLOAT_BLOCK: result = VK_FORMAT_BC6H_UFLOAT_BLOCK; break;
        case Format::BC6H_SFLOAT_BLOCK: result = VK_FORMAT_BC6H_SFLOAT_BLOCK; break;
        case Format::BC7_UNORM_BLOCK: result = VK_FORMAT_BC7_UNORM_BLOCK; break;
        case Format::BC7_SRGB_BLOCK: result = VK_FORMAT_BC7_SRGB_BLOCK; break;
        case Format::ETC2_R8G8B8_UNORM_BLOCK: result = VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK; break;
        case Format::ETC2_R8G8B8_SRGB_BLOCK: result = VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK; break;
        case Format::ETC2_R8G8B8A1_UNORM_BLOCK: result = VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK; break;
        case Format::ETC2_R8G8B8A1_SRGB_BLOCK: result = VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK; break;
        case Format::ETC2_R8G8B8A8_UNORM_BLOCK: result = VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK; break;
        case Format::ETC2_R8G8B8A8_SRGB_BLOCK: result = VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK; break;
        case Format::EAC_R11_UNORM_BLOCK: result = VK_FORMAT_EAC_R11_UNORM_BLOCK; break;
        case Format::EAC_R11_SNORM_BLOCK: result = VK_FORMAT_EAC_R11_SNORM_BLOCK; break;
        case Format::EAC_R11G11_UNORM_BLOCK: result = VK_FORMAT_EAC_R11G11_UNORM_BLOCK; break;
        case Format::EAC_R11G11_SNORM_BLOCK: result = VK_FORMAT_EAC_R11G11_SNORM_BLOCK; break;
        case Format::ASTC_4x4_UNORM_BLOCK: result = VK_FORMAT_ASTC_4x4_UNORM_BLOCK; break;
        case Format::ASTC_4x4_SRGB_BLOCK: result = VK_FORMAT_ASTC_4x4_SRGB_BLOCK; break;
        case Format::ASTC_5x4_UNORM_BLOCK: result = VK_FORMAT_ASTC_5x4_UNORM_BLOCK; break;
        case Format::ASTC_5x4_SRGB_BLOCK: result = VK_FORMAT_ASTC_5x4_SRGB_BLOCK; break;
        case Format::ASTC_5x5_UNORM_BLOCK: result = VK_FORMAT_ASTC_5x5_UNORM_BLOCK; break;
        case Format::ASTC_5x5_SRGB_BLOCK: result = VK_FORMAT_ASTC_5x5_SRGB_BLOCK; break;
        case Format::ASTC_6x5_UNORM_BLOCK: result = VK_FORMAT_ASTC_6x5_UNORM_BLOCK; break;
        case Format::ASTC_6x5_SRGB_BLOCK: result = VK_FORMAT_ASTC_6x5_SRGB_BLOCK; break;
        case Format::ASTC_6x6_UNORM_BLOCK: result = VK_FORMAT_ASTC_6x6_UNORM_BLOCK; break;
        case Format::ASTC_6x6_SRGB_BLOCK: result = VK_FORMAT_ASTC_6x6_SRGB_BLOCK; break;
        case Format::ASTC_8x5_UNORM_BLOCK: result = VK_FORMAT_ASTC_8x5_UNORM_BLOCK; break;
        case Format::ASTC_8x5_SRGB_BLOCK: result = VK_FORMAT_ASTC_8x5_SRGB_BLOCK; break;
        case Format::ASTC_8x6_UNORM_BLOCK: result = VK_FORMAT_ASTC_8x6_UNORM_BLOCK; break;
        case Format::ASTC_8x6_SRGB_BLOCK: result = VK_FORMAT_ASTC_8x6_SRGB_BLOCK; break;
        case Format::ASTC_8x8_UNORM_BLOCK: result = VK_FORMAT_ASTC_8x8_UNORM_BLOCK; break;
        case Format::ASTC_8x8_SRGB_BLOCK: result = VK_FORMAT_ASTC_8x8_SRGB_BLOCK; break;
        case Format::ASTC_10x5_UNORM_BLOCK: result = VK_FORMAT_ASTC_10x5_UNORM_BLOCK; break;
        case Format::ASTC_10x5_SRGB_BLOCK: result = VK_FORMAT_ASTC_10x5_SRGB_BLOCK; break;
        case Format::ASTC_10x6_UNORM_BLOCK: result = VK_FORMAT_ASTC_10x6_UNORM_BLOCK; break;
        case Format::ASTC_10x6_SRGB_BLOCK: result = VK_FORMAT_ASTC_10x6_SRGB_BLOCK; break;
        case Format::ASTC_10x8_UNORM_BLOCK: result = VK_FORMAT_ASTC_10x8_UNORM_BLOCK; break;
        case Format::ASTC_10x8_SRGB_BLOCK: result = VK_FORMAT_ASTC_10x8_SRGB_BLOCK; break;
        case Format::ASTC_10x10_UNORM_BLOCK: result = VK_FORMAT_ASTC_10x10_UNORM_BLOCK; break;
        case Format::ASTC_10x10_SRGB_BLOCK: result = VK_FORMAT_ASTC_10x10_SRGB_BLOCK; break;
        case Format::ASTC_12x10_UNORM_BLOCK: result = VK_FORMAT_ASTC_12x10_UNORM_BLOCK; break;
        case Format::ASTC_12x10_SRGB_BLOCK: result = VK_FORMAT_ASTC_12x10_SRGB_BLOCK; break;
        case Format::ASTC_12x12_UNORM_BLOCK: result = VK_FORMAT_ASTC_12x12_UNORM_BLOCK; break;
        case Format::ASTC_12x12_SRGB_BLOCK: result = VK_FORMAT_ASTC_12x12_SRGB_BLOCK; break;
        case Format::G8B8G8R8_422_UNORM: result = VK_FORMAT_G8B8G8R8_422_UNORM; break;
        case Format::B8G8R8G8_422_UNORM: result = VK_FORMAT_B8G8R8G8_422_UNORM; break;
        case Format::G8_B8_R8_3PLANE_420_UNORM: result = VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM; break;
        case Format::G8_B8R8_2PLANE_420_UNORM: result = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM; break;
        case Format::G8_B8_R8_3PLANE_422_UNORM: result = VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM; break;
        case Format::G8_B8R8_2PLANE_422_UNORM: result = VK_FORMAT_G8_B8R8_2PLANE_422_UNORM; break;
        case Format::G8_B8_R8_3PLANE_444_UNORM: result = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM; break;
        case Format::R10X6_UNORM_PACK16: result = VK_FORMAT_R10X6_UNORM_PACK16; break;
        case Format::R10X6G10X6_UNORM_2PACK16: result = VK_FORMAT_R10X6G10X6_UNORM_2PACK16; break;
        case Format::R10X6G10X6B10X6A10X6_UNORM_4PACK16: result = VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16; break;
        case Format::G10X6B10X6G10X6R10X6_422_UNORM_4PACK16: result = VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16; break;
        case Format::B10X6G10X6R10X6G10X6_422_UNORM_4PACK16: result = VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16; break;
        case Format::G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16: result = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16; break;
        case Format::G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16: result = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16; break;
        case Format::G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16: result = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16; break;
        case Format::G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16: result = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16; break;
        case Format::G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16: result = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16; break;
        case Format::R12X4_UNORM_PACK16: result = VK_FORMAT_R12X4_UNORM_PACK16; break;
        case Format::R12X4G12X4_UNORM_2PACK16: result = VK_FORMAT_R12X4G12X4_UNORM_2PACK16; break;
        case Format::R12X4G12X4B12X4A12X4_UNORM_4PACK16: result = VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16; break;
        case Format::G12X4B12X4G12X4R12X4_422_UNORM_4PACK16: result = VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16; break;
        case Format::B12X4G12X4R12X4G12X4_422_UNORM_4PACK16: result = VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16; break;
        case Format::G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16: result = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16; break;
        case Format::G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16: result = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16; break;
        case Format::G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16: result = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16; break;
        case Format::G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16: result = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16; break;
        case Format::G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16: result = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16; break;
        case Format::G16B16G16R16_422_UNORM: result = VK_FORMAT_G16B16G16R16_422_UNORM; break;
        case Format::B16G16R16G16_422_UNORM: result = VK_FORMAT_B16G16R16G16_422_UNORM; break;
        case Format::G16_B16_R16_3PLANE_420_UNORM: result = VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM; break;
        case Format::G16_B16R16_2PLANE_420_UNORM: result = VK_FORMAT_G16_B16R16_2PLANE_420_UNORM; break;
        case Format::G16_B16_R16_3PLANE_422_UNORM: result = VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM; break;
        case Format::G16_B16R16_2PLANE_422_UNORM: result = VK_FORMAT_G16_B16R16_2PLANE_422_UNORM; break;
        case Format::G16_B16_R16_3PLANE_444_UNORM: result = VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM; break;
        case Format::PVRTC1_2BPP_UNORM_BLOCK_IMG: result = VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG; break;
        case Format::PVRTC1_4BPP_UNORM_BLOCK_IMG: result = VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG; break;
        case Format::PVRTC2_2BPP_UNORM_BLOCK_IMG: result = VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG; break;
        case Format::PVRTC2_4BPP_UNORM_BLOCK_IMG: result = VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG; break;
        case Format::PVRTC1_2BPP_SRGB_BLOCK_IMG: result = VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG; break;
        case Format::PVRTC1_4BPP_SRGB_BLOCK_IMG: result = VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG; break;
        case Format::PVRTC2_2BPP_SRGB_BLOCK_IMG: result = VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG; break;
        case Format::PVRTC2_4BPP_SRGB_BLOCK_IMG: result = VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG; break;
    }
    return result;
}

Format VulkanConversor::to_eg(VkFormat format) {

    Format result = Format::UNDEFINED;

    switch(format){
        case VK_FORMAT_UNDEFINED: result = Format::UNDEFINED; break;
        case VK_FORMAT_R4G4_UNORM_PACK8: result = Format::R4G4_UNORM_PACK8; break;
        case VK_FORMAT_R4G4B4A4_UNORM_PACK16: result = Format::R4G4B4A4_UNORM_PACK16; break;
        case VK_FORMAT_B4G4R4A4_UNORM_PACK16: result = Format::B4G4R4A4_UNORM_PACK16; break;
        case VK_FORMAT_R5G6B5_UNORM_PACK16: result = Format::R5G6B5_UNORM_PACK16; break;
        case VK_FORMAT_B5G6R5_UNORM_PACK16: result = Format::B5G6R5_UNORM_PACK16; break;
        case VK_FORMAT_R5G5B5A1_UNORM_PACK16: result = Format::R5G5B5A1_UNORM_PACK16; break;
        case VK_FORMAT_B5G5R5A1_UNORM_PACK16: result = Format::B5G5R5A1_UNORM_PACK16; break;
        case VK_FORMAT_A1R5G5B5_UNORM_PACK16: result = Format::A1R5G5B5_UNORM_PACK16; break;
        case VK_FORMAT_R8_UNORM: result = Format::R8_UNORM; break;
        case VK_FORMAT_R8_SNORM: result = Format::R8_SNORM; break;
        case VK_FORMAT_R8_USCALED: result = Format::R8_USCALED; break;
        case VK_FORMAT_R8_SSCALED: result = Format::R8_SSCALED; break;
        case VK_FORMAT_R8_UINT: result = Format::R8_UINT; break;
        case VK_FORMAT_R8_SINT: result = Format::R8_SINT; break;
        case VK_FORMAT_R8_SRGB: result = Format::R8_SRGB; break;
        case VK_FORMAT_R8G8_UNORM: result = Format::R8G8_UNORM; break;
        case VK_FORMAT_R8G8_SNORM: result = Format::R8G8_SNORM; break;
        case VK_FORMAT_R8G8_USCALED: result = Format::R8G8_USCALED; break;
        case VK_FORMAT_R8G8_SSCALED: result = Format::R8G8_SSCALED; break;
        case VK_FORMAT_R8G8_UINT: result = Format::R8G8_UINT; break;
        case VK_FORMAT_R8G8_SINT: result = Format::R8G8_SINT; break;
        case VK_FORMAT_R8G8_SRGB: result = Format::R8G8_SRGB; break;
        case VK_FORMAT_R8G8B8_UNORM: result = Format::R8G8B8_UNORM; break;
        case VK_FORMAT_R8G8B8_SNORM: result = Format::R8G8B8_SNORM; break;
        case VK_FORMAT_R8G8B8_USCALED: result = Format::R8G8B8_USCALED; break;
        case VK_FORMAT_R8G8B8_SSCALED: result = Format::R8G8B8_SSCALED; break;
        case VK_FORMAT_R8G8B8_UINT: result = Format::R8G8B8_UINT; break;
        case VK_FORMAT_R8G8B8_SINT: result = Format::R8G8B8_SINT; break;
        case VK_FORMAT_R8G8B8_SRGB: result = Format::R8G8B8_SRGB; break;
        case VK_FORMAT_B8G8R8_UNORM: result = Format::B8G8R8_UNORM; break;
        case VK_FORMAT_B8G8R8_SNORM: result = Format::B8G8R8_SNORM; break;
        case VK_FORMAT_B8G8R8_USCALED: result = Format::B8G8R8_USCALED; break;
        case VK_FORMAT_B8G8R8_SSCALED: result = Format::B8G8R8_SSCALED; break;
        case VK_FORMAT_B8G8R8_UINT: result = Format::B8G8R8_UINT; break;
        case VK_FORMAT_B8G8R8_SINT: result = Format::B8G8R8_SINT; break;
        case VK_FORMAT_B8G8R8_SRGB: result = Format::B8G8R8_SRGB; break;
        case VK_FORMAT_R8G8B8A8_UNORM: result = Format::R8G8B8A8_UNORM; break;
        case VK_FORMAT_R8G8B8A8_SNORM: result = Format::R8G8B8A8_SNORM; break;
        case VK_FORMAT_R8G8B8A8_USCALED: result = Format::R8G8B8A8_USCALED; break;
        case VK_FORMAT_R8G8B8A8_SSCALED: result = Format::R8G8B8A8_SSCALED; break;
        case VK_FORMAT_R8G8B8A8_UINT: result = Format::R8G8B8A8_UINT; break;
        case VK_FORMAT_R8G8B8A8_SINT: result = Format::R8G8B8A8_SINT; break;
        case VK_FORMAT_R8G8B8A8_SRGB: result = Format::R8G8B8A8_SRGB; break;
        case VK_FORMAT_B8G8R8A8_UNORM: result = Format::B8G8R8A8_UNORM; break;
        case VK_FORMAT_B8G8R8A8_SNORM: result = Format::B8G8R8A8_SNORM; break;
        case VK_FORMAT_B8G8R8A8_USCALED: result = Format::B8G8R8A8_USCALED; break;
        case VK_FORMAT_B8G8R8A8_SSCALED: result = Format::B8G8R8A8_SSCALED; break;
        case VK_FORMAT_B8G8R8A8_UINT: result = Format::B8G8R8A8_UINT; break;
        case VK_FORMAT_B8G8R8A8_SINT: result = Format::B8G8R8A8_SINT; break;
        case VK_FORMAT_B8G8R8A8_SRGB: result = Format::B8G8R8A8_SRGB; break;
        case VK_FORMAT_A8B8G8R8_UNORM_PACK32: result = Format::A8B8G8R8_UNORM_PACK32; break;
        case VK_FORMAT_A8B8G8R8_SNORM_PACK32: result = Format::A8B8G8R8_SNORM_PACK32; break;
        case VK_FORMAT_A8B8G8R8_USCALED_PACK32: result = Format::A8B8G8R8_USCALED_PACK32; break;
        case VK_FORMAT_A8B8G8R8_SSCALED_PACK32: result = Format::A8B8G8R8_SSCALED_PACK32; break;
        case VK_FORMAT_A8B8G8R8_UINT_PACK32: result = Format::A8B8G8R8_UINT_PACK32; break;
        case VK_FORMAT_A8B8G8R8_SINT_PACK32: result = Format::A8B8G8R8_SINT_PACK32; break;
        case VK_FORMAT_A8B8G8R8_SRGB_PACK32: result = Format::A8B8G8R8_SRGB_PACK32; break;
        case VK_FORMAT_A2R10G10B10_UNORM_PACK32: result = Format::A2R10G10B10_UNORM_PACK32; break;
        case VK_FORMAT_A2R10G10B10_SNORM_PACK32: result = Format::A2R10G10B10_SNORM_PACK32; break;
        case VK_FORMAT_A2R10G10B10_USCALED_PACK32: result = Format::A2R10G10B10_USCALED_PACK32; break;
        case VK_FORMAT_A2R10G10B10_SSCALED_PACK32: result = Format::A2R10G10B10_SSCALED_PACK32; break;
        case VK_FORMAT_A2R10G10B10_UINT_PACK32: result = Format::A2R10G10B10_UINT_PACK32; break;
        case VK_FORMAT_A2R10G10B10_SINT_PACK32: result = Format::A2R10G10B10_SINT_PACK32; break;
        case VK_FORMAT_A2B10G10R10_UNORM_PACK32: result = Format::A2B10G10R10_UNORM_PACK32; break;
        case VK_FORMAT_A2B10G10R10_SNORM_PACK32: result = Format::A2B10G10R10_SNORM_PACK32; break;
        case VK_FORMAT_A2B10G10R10_USCALED_PACK32: result = Format::A2B10G10R10_USCALED_PACK32; break;
        case VK_FORMAT_A2B10G10R10_SSCALED_PACK32: result = Format::A2B10G10R10_SSCALED_PACK32; break;
        case VK_FORMAT_A2B10G10R10_UINT_PACK32: result = Format::A2B10G10R10_UINT_PACK32; break;
        case VK_FORMAT_A2B10G10R10_SINT_PACK32: result = Format::A2B10G10R10_SINT_PACK32; break;
        case VK_FORMAT_R16_UNORM: result = Format::R16_UNORM; break;
        case VK_FORMAT_R16_SNORM: result = Format::R16_SNORM; break;
        case VK_FORMAT_R16_USCALED: result = Format::R16_USCALED; break;
        case VK_FORMAT_R16_SSCALED: result = Format::R16_SSCALED; break;
        case VK_FORMAT_R16_UINT: result = Format::R16_UINT; break;
        case VK_FORMAT_R16_SINT: result = Format::R16_SINT; break;
        case VK_FORMAT_R16_SFLOAT: result = Format::R16_SFLOAT; break;
        case VK_FORMAT_R16G16_UNORM: result = Format::R16G16_UNORM; break;
        case VK_FORMAT_R16G16_SNORM: result = Format::R16G16_SNORM; break;
        case VK_FORMAT_R16G16_USCALED: result = Format::R16G16_USCALED; break;
        case VK_FORMAT_R16G16_SSCALED: result = Format::R16G16_SSCALED; break;
        case VK_FORMAT_R16G16_UINT: result = Format::R16G16_UINT; break;
        case VK_FORMAT_R16G16_SINT: result = Format::R16G16_SINT; break;
        case VK_FORMAT_R16G16_SFLOAT: result = Format::R16G16_SFLOAT; break;
        case VK_FORMAT_R16G16B16_UNORM: result = Format::R16G16B16_UNORM; break;
        case VK_FORMAT_R16G16B16_SNORM: result = Format::R16G16B16_SNORM; break;
        case VK_FORMAT_R16G16B16_USCALED: result = Format::R16G16B16_USCALED; break;
        case VK_FORMAT_R16G16B16_SSCALED: result = Format::R16G16B16_SSCALED; break;
        case VK_FORMAT_R16G16B16_UINT: result = Format::R16G16B16_UINT; break;
        case VK_FORMAT_R16G16B16_SINT: result = Format::R16G16B16_SINT; break;
        case VK_FORMAT_R16G16B16_SFLOAT: result = Format::R16G16B16_SFLOAT; break;
        case VK_FORMAT_R16G16B16A16_UNORM: result = Format::R16G16B16A16_UNORM; break;
        case VK_FORMAT_R16G16B16A16_SNORM: result = Format::R16G16B16A16_SNORM; break;
        case VK_FORMAT_R16G16B16A16_USCALED: result = Format::R16G16B16A16_USCALED; break;
        case VK_FORMAT_R16G16B16A16_SSCALED: result = Format::R16G16B16A16_SSCALED; break;
        case VK_FORMAT_R16G16B16A16_UINT: result = Format::R16G16B16A16_UINT; break;
        case VK_FORMAT_R16G16B16A16_SINT: result = Format::R16G16B16A16_SINT; break;
        case VK_FORMAT_R16G16B16A16_SFLOAT: result = Format::R16G16B16A16_SFLOAT; break;
        case VK_FORMAT_R32_UINT: result = Format::R32_UINT; break;
        case VK_FORMAT_R32_SINT: result = Format::R32_SINT; break;
        case VK_FORMAT_R32_SFLOAT: result = Format::R32_SFLOAT; break;
        case VK_FORMAT_R32G32_UINT: result = Format::R32G32_UINT; break;
        case VK_FORMAT_R32G32_SINT: result = Format::R32G32_SINT; break;
        case VK_FORMAT_R32G32_SFLOAT: result = Format::R32G32_SFLOAT; break;
        case VK_FORMAT_R32G32B32_UINT: result = Format::R32G32B32_UINT; break;
        case VK_FORMAT_R32G32B32_SINT: result = Format::R32G32B32_SINT; break;
        case VK_FORMAT_R32G32B32_SFLOAT: result = Format::R32G32B32_SFLOAT; break;
        case VK_FORMAT_R32G32B32A32_UINT: result = Format::R32G32B32A32_UINT; break;
        case VK_FORMAT_R32G32B32A32_SINT: result = Format::R32G32B32A32_SINT; break;
        case VK_FORMAT_R32G32B32A32_SFLOAT: result = Format::R32G32B32A32_SFLOAT; break;
        case VK_FORMAT_R64_UINT: result = Format::R64_UINT; break;
        case VK_FORMAT_R64_SINT: result = Format::R64_SINT; break;
        case VK_FORMAT_R64_SFLOAT: result = Format::R64_SFLOAT; break;
        case VK_FORMAT_R64G64_UINT: result = Format::R64G64_UINT; break;
        case VK_FORMAT_R64G64_SINT: result = Format::R64G64_SINT; break;
        case VK_FORMAT_R64G64_SFLOAT: result = Format::R64G64_SFLOAT; break;
        case VK_FORMAT_R64G64B64_UINT: result = Format::R64G64B64_UINT; break;
        case VK_FORMAT_R64G64B64_SINT: result = Format::R64G64B64_SINT; break;
        case VK_FORMAT_R64G64B64_SFLOAT: result = Format::R64G64B64_SFLOAT; break;
        case VK_FORMAT_R64G64B64A64_UINT: result = Format::R64G64B64A64_UINT; break;
        case VK_FORMAT_R64G64B64A64_SINT: result = Format::R64G64B64A64_SINT; break;
        case VK_FORMAT_R64G64B64A64_SFLOAT: result = Format::R64G64B64A64_SFLOAT; break;
        case VK_FORMAT_B10G11R11_UFLOAT_PACK32: result = Format::B10G11R11_UFLOAT_PACK32; break;
        case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32: result = Format::E5B9G9R9_UFLOAT_PACK32; break;
        case VK_FORMAT_D16_UNORM: result = Format::D16_UNORM; break;
        case VK_FORMAT_X8_D24_UNORM_PACK32: result = Format::X8_D24_UNORM_PACK32; break;
        case VK_FORMAT_D32_SFLOAT: result = Format::D32_SFLOAT; break;
        case VK_FORMAT_S8_UINT: result = Format::S8_UINT; break;
        case VK_FORMAT_D16_UNORM_S8_UINT: result = Format::D16_UNORM_S8_UINT; break;
        case VK_FORMAT_D24_UNORM_S8_UINT: result = Format::D24_UNORM_S8_UINT; break;
        case VK_FORMAT_D32_SFLOAT_S8_UINT: result = Format::D32_SFLOAT_S8_UINT; break;
        case VK_FORMAT_BC1_RGB_UNORM_BLOCK: result = Format::BC1_RGB_UNORM_BLOCK; break;
        case VK_FORMAT_BC1_RGB_SRGB_BLOCK: result = Format::BC1_RGB_SRGB_BLOCK; break;
        case VK_FORMAT_BC1_RGBA_UNORM_BLOCK: result = Format::BC1_RGBA_UNORM_BLOCK; break;
        case VK_FORMAT_BC1_RGBA_SRGB_BLOCK: result = Format::BC1_RGBA_SRGB_BLOCK; break;
        case VK_FORMAT_BC2_UNORM_BLOCK: result = Format::BC2_UNORM_BLOCK; break;
        case VK_FORMAT_BC2_SRGB_BLOCK: result = Format::BC2_SRGB_BLOCK; break;
        case VK_FORMAT_BC3_UNORM_BLOCK: result = Format::BC3_UNORM_BLOCK; break;
        case VK_FORMAT_BC3_SRGB_BLOCK: result = Format::BC3_SRGB_BLOCK; break;
        case VK_FORMAT_BC4_UNORM_BLOCK: result = Format::BC4_UNORM_BLOCK; break;
        case VK_FORMAT_BC4_SNORM_BLOCK: result = Format::BC4_SNORM_BLOCK; break;
        case VK_FORMAT_BC5_UNORM_BLOCK: result = Format::BC5_UNORM_BLOCK; break;
        case VK_FORMAT_BC5_SNORM_BLOCK: result = Format::BC5_SNORM_BLOCK; break;
        case VK_FORMAT_BC6H_UFLOAT_BLOCK: result = Format::BC6H_UFLOAT_BLOCK; break;
        case VK_FORMAT_BC6H_SFLOAT_BLOCK: result = Format::BC6H_SFLOAT_BLOCK; break;
        case VK_FORMAT_BC7_UNORM_BLOCK: result = Format::BC7_UNORM_BLOCK; break;
        case VK_FORMAT_BC7_SRGB_BLOCK: result = Format::BC7_SRGB_BLOCK; break;
        case VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK: result = Format::ETC2_R8G8B8_UNORM_BLOCK; break;
        case VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK: result = Format::ETC2_R8G8B8_SRGB_BLOCK; break;
        case VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK: result = Format::ETC2_R8G8B8A1_UNORM_BLOCK; break;
        case VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK: result = Format::ETC2_R8G8B8A1_SRGB_BLOCK; break;
        case VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK: result = Format::ETC2_R8G8B8A8_UNORM_BLOCK; break;
        case VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK: result = Format::ETC2_R8G8B8A8_SRGB_BLOCK; break;
        case VK_FORMAT_EAC_R11_UNORM_BLOCK: result = Format::EAC_R11_UNORM_BLOCK; break;
        case VK_FORMAT_EAC_R11_SNORM_BLOCK: result = Format::EAC_R11_SNORM_BLOCK; break;
        case VK_FORMAT_EAC_R11G11_UNORM_BLOCK: result = Format::EAC_R11G11_UNORM_BLOCK; break;
        case VK_FORMAT_EAC_R11G11_SNORM_BLOCK: result = Format::EAC_R11G11_SNORM_BLOCK; break;
        case VK_FORMAT_ASTC_4x4_UNORM_BLOCK: result = Format::ASTC_4x4_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_4x4_SRGB_BLOCK: result = Format::ASTC_4x4_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_5x4_UNORM_BLOCK: result = Format::ASTC_5x4_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_5x4_SRGB_BLOCK: result = Format::ASTC_5x4_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_5x5_UNORM_BLOCK: result = Format::ASTC_5x5_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_5x5_SRGB_BLOCK: result = Format::ASTC_5x5_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_6x5_UNORM_BLOCK: result = Format::ASTC_6x5_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_6x5_SRGB_BLOCK: result = Format::ASTC_6x5_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_6x6_UNORM_BLOCK: result = Format::ASTC_6x6_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_6x6_SRGB_BLOCK: result = Format::ASTC_6x6_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_8x5_UNORM_BLOCK: result = Format::ASTC_8x5_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_8x5_SRGB_BLOCK: result = Format::ASTC_8x5_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_8x6_UNORM_BLOCK: result = Format::ASTC_8x6_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_8x6_SRGB_BLOCK: result = Format::ASTC_8x6_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_8x8_UNORM_BLOCK: result = Format::ASTC_8x8_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_8x8_SRGB_BLOCK: result = Format::ASTC_8x8_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_10x5_UNORM_BLOCK: result = Format::ASTC_10x5_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_10x5_SRGB_BLOCK: result = Format::ASTC_10x5_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_10x6_UNORM_BLOCK: result = Format::ASTC_10x6_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_10x6_SRGB_BLOCK: result = Format::ASTC_10x6_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_10x8_UNORM_BLOCK: result = Format::ASTC_10x8_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_10x8_SRGB_BLOCK: result = Format::ASTC_10x8_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_10x10_UNORM_BLOCK: result = Format::ASTC_10x10_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_10x10_SRGB_BLOCK: result = Format::ASTC_10x10_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_12x10_UNORM_BLOCK: result = Format::ASTC_12x10_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_12x10_SRGB_BLOCK: result = Format::ASTC_12x10_SRGB_BLOCK; break;
        case VK_FORMAT_ASTC_12x12_UNORM_BLOCK: result = Format::ASTC_12x12_UNORM_BLOCK; break;
        case VK_FORMAT_ASTC_12x12_SRGB_BLOCK: result = Format::ASTC_12x12_SRGB_BLOCK; break;
        case VK_FORMAT_G8B8G8R8_422_UNORM: result = Format::G8B8G8R8_422_UNORM; break;
        case VK_FORMAT_B8G8R8G8_422_UNORM: result = Format::B8G8R8G8_422_UNORM; break;
        case VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM: result = Format::G8_B8_R8_3PLANE_420_UNORM; break;
        case VK_FORMAT_G8_B8R8_2PLANE_420_UNORM: result = Format::G8_B8R8_2PLANE_420_UNORM; break;
        case VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM: result = Format::G8_B8_R8_3PLANE_422_UNORM; break;
        case VK_FORMAT_G8_B8R8_2PLANE_422_UNORM: result = Format::G8_B8R8_2PLANE_422_UNORM; break;
        case VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM: result = Format::G8_B8_R8_3PLANE_444_UNORM; break;
        case VK_FORMAT_R10X6_UNORM_PACK16: result = Format::R10X6_UNORM_PACK16; break;
        case VK_FORMAT_R10X6G10X6_UNORM_2PACK16: result = Format::R10X6G10X6_UNORM_2PACK16; break;
        case VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16: result = Format::R10X6G10X6B10X6A10X6_UNORM_4PACK16; break;
        case VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16: result = Format::G10X6B10X6G10X6R10X6_422_UNORM_4PACK16; break;
        case VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16: result = Format::B10X6G10X6R10X6G10X6_422_UNORM_4PACK16; break;
        case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16: result = Format::G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16; break;
        case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16: result = Format::G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16; break;
        case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16: result = Format::G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16; break;
        case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16: result = Format::G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16; break;
        case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16: result = Format::G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16; break;
        case VK_FORMAT_R12X4_UNORM_PACK16: result = Format::R12X4_UNORM_PACK16; break;
        case VK_FORMAT_R12X4G12X4_UNORM_2PACK16: result = Format::R12X4G12X4_UNORM_2PACK16; break;
        case VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16: result = Format::R12X4G12X4B12X4A12X4_UNORM_4PACK16; break;
        case VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16: result = Format::G12X4B12X4G12X4R12X4_422_UNORM_4PACK16; break;
        case VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16: result = Format::B12X4G12X4R12X4G12X4_422_UNORM_4PACK16; break;
        case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16: result = Format::G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16; break;
        case VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16: result = Format::G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16; break;
        case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16: result = Format::G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16; break;
        case VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16: result = Format::G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16; break;
        case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16: result = Format::G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16; break;
        case VK_FORMAT_G16B16G16R16_422_UNORM: result = Format::G16B16G16R16_422_UNORM; break;
        case VK_FORMAT_B16G16R16G16_422_UNORM: result = Format::B16G16R16G16_422_UNORM; break;
        case VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM: result = Format::G16_B16_R16_3PLANE_420_UNORM; break;
        case VK_FORMAT_G16_B16R16_2PLANE_420_UNORM: result = Format::G16_B16R16_2PLANE_420_UNORM; break;
        case VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM: result = Format::G16_B16_R16_3PLANE_422_UNORM; break;
        case VK_FORMAT_G16_B16R16_2PLANE_422_UNORM: result = Format::G16_B16R16_2PLANE_422_UNORM; break;
        case VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM: result = Format::G16_B16_R16_3PLANE_444_UNORM; break;
        case VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG: result = Format::PVRTC1_2BPP_UNORM_BLOCK_IMG; break;
        case VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG: result = Format::PVRTC1_4BPP_UNORM_BLOCK_IMG; break;
        case VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG: result = Format::PVRTC2_2BPP_UNORM_BLOCK_IMG; break;
        case VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG: result = Format::PVRTC2_4BPP_UNORM_BLOCK_IMG; break;
        case VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG: result = Format::PVRTC1_2BPP_SRGB_BLOCK_IMG; break;
        case VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG: result = Format::PVRTC1_4BPP_SRGB_BLOCK_IMG; break;
        case VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG: result = Format::PVRTC2_2BPP_SRGB_BLOCK_IMG; break;
        case VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG: result = Format::PVRTC2_4BPP_SRGB_BLOCK_IMG; break;
    }
    return result;
}

VkShaderStageFlags VulkanConversor::to_vk(ShaderStage stage) {
    VkShaderStageFlags result;
    switch(stage){
        case ShaderStage::VERTEX: result = VK_SHADER_STAGE_VERTEX_BIT; break;
        case ShaderStage::FRAGMENT:result = VK_SHADER_STAGE_FRAGMENT_BIT; break;
        case ShaderStage::COMPUTE: result = VK_SHADER_STAGE_COMPUTE_BIT; break;
        case ShaderStage::GEOMETRY: result = VK_SHADER_STAGE_GEOMETRY_BIT; break;
        case ShaderStage::TESSALATION_CONTROL: result = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT; break;
        case ShaderStage::TESSALATION_EVALUATE: result = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT; break;
    }
    return result;
}

ShaderStage VulkanConversor::to_eg(VkShaderStageFlags stage) {
    ShaderStage result;
    switch(stage){
        case VK_SHADER_STAGE_VERTEX_BIT: result = ShaderStage::VERTEX; break;
        case VK_SHADER_STAGE_FRAGMENT_BIT:result = ShaderStage::FRAGMENT; break;
        case VK_SHADER_STAGE_COMPUTE_BIT: result = ShaderStage::COMPUTE; break;
        case VK_SHADER_STAGE_GEOMETRY_BIT: result = ShaderStage::GEOMETRY; break;
        case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT: result = ShaderStage::TESSALATION_CONTROL; break;
        case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT: result = ShaderStage::TESSALATION_EVALUATE; break;
        default: throw std::runtime_error("Invalid VkShaderStageFlags conversion attempt!");
    }
    return result;
}

VkDescriptorType VulkanConversor::to_vk(DescriptorType type) {
    VkDescriptorType result;
    switch(type){
        case DescriptorType::UNIFORM_BUFFER: result = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; break;
        case DescriptorType::SAMPLED_IMAGE: result = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER; break;
        case DescriptorType::STORAGE_IMAGE: result = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE; break;
        case DescriptorType::STORAGE_BUFFER: result = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER; break;
    }
    return result;
}

DescriptorType VulkanConversor::to_eg(VkDescriptorType type) {
    DescriptorType result;
    switch(type){
        case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER: result = DescriptorType::SAMPLED_IMAGE; break;
        case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER: result = DescriptorType::UNIFORM_BUFFER; break;
        case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE: result = DescriptorType::STORAGE_IMAGE; break;
        case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER: result = DescriptorType::STORAGE_BUFFER; break;
        default: throw std::runtime_error("Invalid VkDescriptorType (not yet supported!)");
    }
    return result;
}

VkFilter VulkanConversor::to_vk(Filter filter) {
    VkFilter result;
    switch(filter){
        case Filter::LINEAR: result = VK_FILTER_LINEAR; break;
        case Filter::NEAREST: result = VK_FILTER_NEAREST; break;
    }
    return result;
}

Filter VulkanConversor::to_eg(VkFilter filter) {
    Filter result;
    switch(filter){
        case VK_FILTER_LINEAR: result = Filter::LINEAR; break;
        case VK_FILTER_NEAREST: result = Filter::NEAREST; break;
        default: throw std::runtime_error("Invalid VkFilter (not yet supported!)");
    }
    return result;
}

VkPrimitiveTopology VulkanConversor::to_vk(PrimitiveTopology topology) {
    VkPrimitiveTopology result;
    switch(topology){
        case PrimitiveTopology::POINT_LIST:result = VK_PRIMITIVE_TOPOLOGY_POINT_LIST; break;
        case PrimitiveTopology::LINE_LIST:result = VK_PRIMITIVE_TOPOLOGY_LINE_LIST; break;
        case PrimitiveTopology::LINE_STRIP:result = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP; break;
        case PrimitiveTopology::TRIANGLE_LIST:result = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; break;
        case PrimitiveTopology::TRIANGLE_STRIP:result = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP; break;
        case PrimitiveTopology::TRIANGLE_FAN:result = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN; break;
        case PrimitiveTopology::LINE_LIST_WITH_ADJACENCY:result = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY; break;
        case PrimitiveTopology::LINE_STRIP_WITH_ADJACENCY:result = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY; break;
        case PrimitiveTopology::TRIANGLE_LIST_WITH_ADJACENCY:result = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY; break;
        case PrimitiveTopology::TRIANGLE_STRIP_WITH_ADJACENCY:result = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY; break;
        case PrimitiveTopology::PATCH_LIST:result = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST; break;
    }
    return result;
}

PrimitiveTopology VulkanConversor::to_eg(VkPrimitiveTopology topology) {
    PrimitiveTopology result;
    switch(topology){
        case VK_PRIMITIVE_TOPOLOGY_POINT_LIST: result = PrimitiveTopology::POINT_LIST; break;
        case VK_PRIMITIVE_TOPOLOGY_LINE_LIST: result = PrimitiveTopology::LINE_LIST; break;
        case VK_PRIMITIVE_TOPOLOGY_LINE_STRIP: result = PrimitiveTopology::LINE_STRIP; break;
        case VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST: result = PrimitiveTopology::TRIANGLE_LIST; break;
        case VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP: result = PrimitiveTopology::TRIANGLE_STRIP; break;
        case VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN: result = PrimitiveTopology::TRIANGLE_FAN; break;
        case VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY: result = PrimitiveTopology::LINE_LIST_WITH_ADJACENCY; break;
        case VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY: result = PrimitiveTopology::LINE_STRIP_WITH_ADJACENCY; break;
        case VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY: result = PrimitiveTopology::TRIANGLE_LIST_WITH_ADJACENCY; break;
        case VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY: result = PrimitiveTopology::TRIANGLE_STRIP_WITH_ADJACENCY; break;
        case VK_PRIMITIVE_TOPOLOGY_PATCH_LIST: result = PrimitiveTopology::PATCH_LIST; break;
        default: throw std::runtime_error("Invalid VkPrimitiveTopology on conversion");
    }
    return result;
}


EG_END