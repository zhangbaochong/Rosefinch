#pragma once
#include "Framework/Core/Base.h"

namespace Rosefinch
{
    enum class ResourceFlags : uint32_t
    {
        None                    = 0x0,          ///< No flags.
        AllowRenderTarget       = 0x1 << 0,     ///< Allow resource to be used as rasterization target.
        AllowDepthStencil       = 0x1 << 1,     ///< Allow resource to be used as depth/stencil target.
        AllowUnorderedAccess    = 0x1 << 3,     ///< Allow unordered access to resource.
        DenyShaderResource      = 0x1 << 4,     ///< Prevents the resource from having an SRV created for it. 
        AllowSimultaneousAccess = 0x1 << 6,     ///< Allow resource to be accessed from different queues simultaneously.
        AllowShadingRate        = 0x1 << 7,     ///< Allow resource to be a shading rate resource.
        AllowIndirect           = 0x1 << 8,     ///< Allow resource to be an indirect argument.
        AllowConstantBuffer     = 0x1 << 9,     ///< All resource to be used as a constant buffer
    };
    ENUM_FLAG_OPERATORS(ResourceFlags)

    enum class ResourceFormat
    {
        Unknown,            ///< Unknown resource format.

        // 8-bit
        R8_SINT,            ///< Single-component (R) 8-bit (signed int) type.
        R8_UINT,            ///< Single-component (R) 8-bit (unsigned int) type.
        R8_UNORM,           ///< Single-component (R) 8-bit (unsigned normalized) type.

        // 16-bit
        R16_SINT,           ///< Single-component (R) 16-bit (signed int) type.
        R16_UINT,           ///< Single-component (R) 16-bit (unsigned int) type.
        R16_FLOAT,          ///< Single-component (R) 16-bit (floating point) type.
        R16_UNORM,          ///< Single-component (R) 16-bit (unsigned normalized) type.
        R16_SNORM,          ///< Single-component (R) 16-bit (signed normalized) type.
        RG8_SINT,           ///< 2-component (RG) 16-bit (signed int) type.
        RG8_UINT,           ///< 2-component (RG) 16-bit (unsigned int) type.
        RG8_UNORM,          ///< 2-component (RG) 16-bit (unsigned normalized) type.

        // 32-bit
        R32_SINT,           ///< Single-Component (R) 32-bit (signed int) type.
        R32_UINT,           ///< Single-Component (R) 32-bit (unsigned int) type.
        RGBA8_SINT,         ///< 4-Component (RGBA) 32-bit (signed int) type.
        BGRA8_SINT,         ///< 4-Component (BGRA) 32-bit (signed int) type.
        RGBA8_UINT,         ///< 4-Component (RGBA) 32-bit (unsigned int) type.
        BGRA8_UINT,         ///< 4-Component (BGRA) 32-bit (unsigned int) type.
        RGBA8_UNORM,        ///< 4-Component (RGBA) 32-bit (unsigned normalized) type.
        BGRA8_UNORM,        ///< 4-Component (BGRA) 32-bit (unsigned normalized) type.
        RGBA8_SNORM,        ///< 4-Component (RGBA) 32-bit (signed normalized) type.
        RGBA8_SRGB,         ///< 4-Component (RGBA) 32-bit (SRGB) type.
        BGRA8_SRGB,         ///< 4-Component (BGRA) 32-bit (SRGB) type.
        RGBA8_TYPELESS,     ///< 4-Component (RGBA) 32-bit (typeless) type.
        BGRA8_TYPELESS,     ///< 4-Component (BGRA) 32-bit (typeless) type.
        RGB10A2_UNORM,      ///< 4-Component (RGBA) 32-bit (unsigned normalized) type.
        BGR10A2_UNORM,      ///< 4-Component (BGRA) 32-bit (unsigned normalized) type.
        RG11B10_FLOAT,      ///< 3-Component (RGB) 32-bit (floating point) type.
        RG16_SINT,          ///< 2-Component (RG) 32-bit (signed int) type.
        RG16_UINT,          ///< 2-Component (RG) 32-bit (unsigned int) type.
        RG16_FLOAT,         ///< 2-Component (R) 32-bit (floating point) type.
        R32_FLOAT,          ///< Single-Component (R) 32-bit (floating point) type.

        // 64-bit
        RGBA16_SINT,        ///< 4-Component (RGBA) 64-bit (signed int) type.
        RGBA16_UINT,        ///< 4-Component (RGBA) 64-bit (unsigned int) type.
        RGBA16_UNORM,       ///< 4-Component (RGBA) 64-bit (unsigned normalized) type.
        RGBA16_SNORM,       ///< 4-Component (RGBA) 64-bit (signed normalized) type.
        RGBA16_FLOAT,       ///< 4-Component (RGBA) 64-bit (floating point) type.
        RG32_SINT,          ///< 2-Component (RG) 64-bit (signed int) type.
        RG32_UINT,          ///< 2-Component (RG) 64-bit (unsigned int) type.
        RG32_FLOAT,         ///< 2-Component (RG) 64-bit (floating point) type.

        // 96-bit
        RGB32_SINT,         ///< 3-Component (RGB) 96-bit (signed int) type.
        RGB32_UINT,         ///< 3-Component (RGB) 96-bit (unsigned int) type.
        RGB32_FLOAT,        ///< 3-Component (RGB) 96-bit (floating point) type.

        // 128-bit
        RGBA32_SINT,        ///< 4-Component (RGBA) 128-bit (signed int) type.
        RGBA32_UINT,        ///< 4-Component (RGBA) 128-bit (unsigned int) type.
        RGBA32_FLOAT,       ///< 4-Component (RGBA) 128-bit (floating point) type.
        RGBA32_TYPELESS,    ///< 4-Component (RGBA) 128-bit (typeless) type.

        // Depth
        D16_UNORM,          ///< 16-bit depth (unsigned int) type.
        D32_FLOAT,          ///< 32-bit depth (floating point) type.

        // compressed
        BC1_UNORM,          ///< BC1 compressed (unsigned int) type.
        BC1_SRGB,           ///< BC1 compressed (SRGB) type.
        BC2_UNORM,          ///< BC2 compressed (unsigned normalized) type.
        BC2_SRGB,           ///< BC2 compressed (SRGB) type.
        BC3_UNORM,          ///< BC3 compressed (unsigned normalized) type.
        BC3_SRGB,           ///< BC3 compressed (SRGB) type.
        BC4_UNORM,          ///< BC4 compressed (unsigned normalized) type.
        BC4_SNORM,          ///< BC4 compressed (signed normalized) type.
        BC5_UNORM,          ///< BC5 compressed (unsigned normalized) type.
        BC5_SNORM,          ///< BC5 compressed (signed normalized) type.
        BC6_UNSIGNED,       ///< BC6 compressed (unsigned) type.
        BC6_SIGNED,         ///< BC6 compressed (signed) type.
        BC7_UNORM,          ///< BC7 compressed (unsigned normalized) type.
        BC7_SRGB,           ///< BC7 compressed (SRGB) type.
    };

    enum class ResourceState : uint32_t
    {
        CommonResource          = 0x0,          ///< Common resource state.
        VertexBufferResource    = 0x1 << 0,     ///< Vertex buffer resource state.
        ConstantBufferResource  = 0x1 << 1,     ///< Constant buffer resource state.
        IndexBufferResource     = 0x1 << 2,     ///< Index buffer resource state.
        RenderTargetResource    = 0x1 << 3,     ///< Render target resource state.
        UnorderedAccess         = 0x1 << 4,     ///< Unordered access resource state.
        DepthWrite              = 0x1 << 5,     ///< Depth write resource state.
        DepthRead               = 0x1 << 6,     ///< Depth read resource state.
        NonPixelShaderResource  = 0x1 << 7,     ///< Non-pixel shader resource state.
        PixelShaderResource     = 0x1 << 8,     ///< Pixel shader resource state.
        IndirectArgument        = 0x1 << 9,     ///< Indirect argument resource state.
        CopyDest                = 0x1 << 10,    ///< Copy destination resource state.
        CopySource              = 0x1 << 11,    ///< Copy source resource state.
        ResolveDest             = 0x1 << 12,    ///< Resolve destination resource state.
        ResolveSource           = 0x1 << 13,    ///< Resolve source resource state.
        RTAccelerationStruct    = 0x1 << 14,    ///< Ray tracing acceleration structure resource state.
        ShadingRateSource       = 0x1 << 15,    ///< Shading rate source resource state.
        GenericRead             = 0x1 << 16,    ///< Generic read resource state.
        Present                 = 0x1 << 17,    ///< Present resource state.

        // Special cases
        DepthShaderResource     = DepthRead | NonPixelShaderResource | PixelShaderResource, ///< Depth shader resource state.
        ShaderResource          = NonPixelShaderResource | PixelShaderResource,             ///< Shader resource (general) state
    };
    ENUM_FLAG_OPERATORS(ResourceState)
}