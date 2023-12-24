#pragma once
#include "Framework/Core/Base.h"

#define MAX_SHADING_RATES 9
#define SHADING_RATE_SHIFT 3

namespace Rosefinch
{
    /// An enumeration for device features to query
    enum class DeviceFeature
    {
        None        = 0,         ///< No device features. Used for initialization.
        FP16        = 1 << 0,    ///< Does the device support FP16 capabilities.
        VRSTier1    = 1 << 1,    ///< Does the device support VRS Tier 1 capabilities.
        VRSTier2    = 1 << 2,    ///< Does the device support VRS Tier 2 capabilities.
        RT_1_0      = 1 << 3,    ///< Does the device support RT 1.0 capabilities.
        RT_1_1      = 1 << 4,    ///< Does the device support RT 1.1 capabilities.
        WaveSize    = 1 << 5,    ///< Does the device support wave size control capabilities.
    };
    ENUM_FLAG_OPERATORS(DeviceFeature)

    /// An enumeration for shader stage
    enum class ShaderStage
    {
        Vertex = 0,     ///< Shader vertex stage.
        Pixel,          ///< Shader pixel stage.
        Hull,           ///< Shader hull stage.
        Domain,         ///< Shader domain stage.
        Geometry,       ///< Shader geometry stage.
        Compute,        ///< Shader compute stage.
    };

    /// An enumeration for shader stage
    /// Note, need to also update the JSON config enums in Framework.cpp when this changes
    /// Note2, need to also update defines strings in shaderbuild_win.cpp
    enum class ShaderModel
    {
        SM5_1 = 0,  ///< default basic hsls support.
        SM6_0,      ///< wave intrinsics & 64-integers for arithmetic.
        SM6_1,      ///< SV_ViewID, barycentric semantics, and GetAttributeAtVertex.
        SM6_2,      ///< float16 support (instead of minfloat16) and denorm mode selection.
        SM6_3,      ///< DXR support.
        SM6_4,      ///< low-precision packed dot product, library sub-object support for RT.
        SM6_5,      ///< DXR 1.1, Sampler Feedback, Mesh and Amplification shaders, and more wave intrinsics.
        SM6_6,      ///< New Atomic operations, Dynamic Resources, Helper Lane Detection, Compute derivatives,
                    ///< new Pack/Unpack intrinsics, WaveSize, RT payload access qualifiers.
        SM6_7,      ///< Expanded texture fetching, quad querying, and wave capabilities.
    };

    /// An enumeration for command queue types
    enum class CommandQueue : int32_t
    {
        // Single threaded (for now)
        Graphics = 0,                   ///< Graphics command queue (single threaded).
        Compute,                        ///< Compute command queue (single threaded).

        // Multi-threaded
        Copy,                           ///< Copy command queue (multi threaded).

        Count                           ///< CommandQueue type count.
    };

    /// An enumeration for primitive topology options
    enum class PrimitiveTopology
    {
        Undefined = 0,              ///< Undefined topology.
        PointList,                  ///< Point list primitive topology.
        LineList,                   ///< Line list primitive topology.
        TriangleList,               ///< Triangle list primitive topology.
        TriangleStrip               ///< Triangle strip primitive topology.
        // Add more as needed
    };

    /// An enumeration for primitive topology types
    enum class PrimitiveTopologyType
    {
        Undefined = 0,              ///< Undefined primitive topology.
        Point,                      ///< Point primitive topology.
        Line,                       ///< Line primitive topology.
        Triangle,                   ///< Triangle primitive topology.
        Patch,                      ///< Patch primitive topology.
    };

    /// A structure representing a viewport construct.
    struct Viewport
    {
        float X = 0.f;          ///< Viewport left coordinate.
        float Y = 0.f;          ///< Viewport top coordinate.
        float Width = 0.f;      ///< Viewport width.
        float Height = 0.f;     ///< Viewport height.
        float MinDepth = 0.f;   ///< Viewport min depth.
        float MaxDepth = 1.f;   ///< Viewport max depth.
    };

    /// A structure representing a rect (quad) construct.
    struct Rect
    {
        uint32_t Left;          ///< Rect left coordinate.
        uint32_t Top;           ///< Rect top coordinate.
        uint32_t Right;         ///< Rect right coordinate.
        uint32_t Bottom;        ///< Rect bottom coordinate.
    };

    /// An enumeration for various attribute formats
    enum class AttributeFormat
    {
        Unknown,        ///< Unknown attribute format.
        Scalar,         ///< Scalar (float) attribute format.
        Vec2,           ///< 2-Component vector attribute format.
        Vec3,           ///< 3-Component vector attribute format.
        Vec4            ///< 4-Component vector attribute format.
    };

    /// An enumeration for vertex attribute types
    enum class VertexAttributeType : uint32_t
    {
        Position = 0,   ///< Position vertex attribute.
        Normal,         ///< Normal vertex attribute.
        Tangent,        ///< Tangent vertex attribute.
        Texcoord0,      ///< Texcoord0 vertex attribute.
        Texcoord1,      ///< Texcoord1 vertex attribute.
        Color0,         ///< Color0 vertex attribute.
        Color1,         ///< Color1 vertex attribute.
        Weights0,       ///< Weights0 (blend weights) vertex attribute.
        Weights1,       ///< Weights1 (blend weights) vertex attribute.
        Joints0,        ///< Joint0 (blend indices) vertex attribute.
        Joints1,        ///< Joint1 (blend indices) vertex attribute.
        Count           ///< Vertex attribute count.
    };

    /// An enumeration for vertex attribute flags (convenience masks built from <c><i>VertexAttributeType</i></c>)
    enum VertexAttributeFlag : uint32_t
    {
        VertexAttributeFlag_Position = 0x1 << static_cast<uint32_t>(VertexAttributeType::Position),
        VertexAttributeFlag_Normal = 0x1 << static_cast<uint32_t>(VertexAttributeType::Normal),
        VertexAttributeFlag_Tangent = 0x1 << static_cast<uint32_t>(VertexAttributeType::Tangent),
        VertexAttributeFlag_Texcoord0 = 0x1 << static_cast<uint32_t>(VertexAttributeType::Texcoord0),
        VertexAttributeFlag_Texcoord1 = 0x1 << static_cast<uint32_t>(VertexAttributeType::Texcoord1),
        VertexAttributeFlag_Color0 = 0x1 << static_cast<uint32_t>(VertexAttributeType::Color0),
        VertexAttributeFlag_Color1 = 0x1 << static_cast<uint32_t>(VertexAttributeType::Color1),
        VertexAttributeFlag_Weights0 = 0x1 << static_cast<uint32_t>(VertexAttributeType::Weights0),
        VertexAttributeFlag_Weights1 = 0x1 << static_cast<uint32_t>(VertexAttributeType::Weights1),
        VertexAttributeFlag_Joints0 = 0x1 << static_cast<uint32_t>(VertexAttributeType::Joints0),
        VertexAttributeFlag_Joints1 = 0x1 << static_cast<uint32_t>(VertexAttributeType::Joints1),
    };

    /// An enumeration for Resource formats
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

    /// An enumeration for resource states
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

    /// An enumeration for resource flags
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

    /// An enumeration for blend factors
    enum class Blend
    {
        Zero = 0,       ///< Blend factor zero.
        One,            ///< Blend factor one.
                        
        SrcColor,       ///< Blend factor source color.
        DstColor,       ///< Blend factor destination color.
        InvSrcColor,    ///< Blend factor 1 - source color.
        InvDstColor,    ///< Blend factor 1 - destination color.
                        
        SrcAlpha,       ///< Blend factor source alpha.
        DstAlpha,       ///< Blend factor destination alpha.
        InvSrcAlpha,    ///< Blend factor 1 - source alpha.
        InvDstAlpha,    ///< Blend factor 1 - destination alpha.
                        
        SrcAlphaSat,    ///< Blend factor is (f, f, f, 1) where f = min(source alpha, 1 - destination alpha).
                        
        BlendFactor,    ///< Blend factor is a custom value.
        InvBlendFactor, ///< Blend factor is 1 - custom value.
    };

    /// An enumeration for blend operations
    enum class BlendOp
    {
        Add = 0,        ///< Source + destination blend operation.
        Subtract,       ///< Source - destination blend operation.
        RevSubtract,    ///< Destination - source blend operation.
        Min,            ///< Min(source, destination) blend operation.
        Max             ///< Max(source, destination) blend operation.
    };

    /// An enumeration for color write mask
    enum class ColorWriteMask : uint32_t
    {
        Red = 0x1,                          ///< Write red channel.
        Green = 0x2,                        ///< Write green channel.
        Blue = 0x4,                         ///< Write blue channel.
        Alpha = 0x8,                        ///< Write alpha channel.
        All = (Red | Green | Blue | Alpha)  ///< Write all channels.
    };

    /// An enumeration for culling mode
    enum class CullMode
    {
        None = 0,   ///< No culling.
        Front,      ///< Front face culling.
        Back,       ///< Backface culling.
    };

    /// An enumeration for comparison functions
    enum class ComparisonFunc
    {
        Never = 0,      ///< Always fail.
        Less,           ///< Accept new if less than current.
        Equal,          ///< Accept new if equal to current.
        LessEqual,      ///< Accept new if less or equal to current.
        Greater,        ///< Accept new if greater than current.
        NotEqual,       ///< Accept new if not equal to current.
        GreaterEqual,   ///< Accept new if greater or equal to current.
        Always,         ///< Always accept.
    };

    /// An enumeration for stencil operations
    enum class StencilOp
    {
        Zero = 0,       ///< Set stencil buffer entry to 0.
        Keep,           ///< Do not update the stencil buffer entry.
        Replace,        ///< Replace the stencil buffer entry with a specified value.
        IncrementSat,   ///< Increment the stencil buffer entry. Clamp to maximum value.
        DecrementSat,   ///< Decrement the stencil buffer entry. Clamp to minimum value.
        Invert,         ///< Invert the stencil buffer entry.
        Increment,      ///< Increment the stencil buffer entry. Wrap to zero.
        Decrement,      ///< Decrement the stencil buffer entry. Wrap to maximum value.
    };

    /// DefineList, holds pairs of key & value that will be used by the compiler as defines
    using DefineList = std::map<const std::string, std::string>;

    /// An enumeration for shader binding stages
    enum class ShaderBindStage
    {
        Unassigned  = 0,                    ///< Unassigned (default).
        Vertex      = 1 << 0,               ///< Vertex shader binding.
        Pixel       = 1 << 1,               ///< Pixel shader binding.
        Compute     = 1 << 2,               ///< Compute shader binding.
        VertexAndPixel = Vertex | Pixel,    ///< Vertex and Pixel shader binding.
    };
    ENUM_FLAG_OPERATORS(ShaderBindStage)

    /// An enumeration for pipeline types
    enum class PipelineType
    {
        Undefined = 0,      ///< Undefined (default)
        Graphics,           ///< Graphics pipeline.
        Compute,            ///< Compute pipeline.
    };

    /// An enumeration for resource view heap types
    enum class ResourceViewHeapType : uint32_t
    {
        GPUResourceView = 0,    ///< GPU resource view type.
        CPUResourceView,        ///< CPU resource view type.
        CPURenderView,          ///< CPU render view type (renter targets).
        CPUDepthView,           ///< CPU depth view type (depth targets).
        GPUSamplerView,         ///< GPU sampler view types (samplers).
        Count                   ///< Resource view heap type count.
    };

    /// An enumeration for resource view types
    enum class ResourceViewType : uint32_t
    {
        CBV = 0,                ///< Constant buffer view type.
        TextureSRV,             ///< Texture shader resource view type.
        BufferSRV,              ///< Buffer shader resource view type.
        TextureUAV,             ///< Texture unordered access view type.
        BufferUAV,              ///< Buffer unordered access view type.
        RTV,                    ///< Render target view type.
        DSV,                    ///< Depth stencil view type.
        Sampler,                ///< Sampler view type.
        Count,                  ///< Resource view type count.

        Invalid = 0xffffffff    ///< Invalid resource view type (used for initializations)
    };

    
    /// An enumeration for binding types.
    /// Used to bind parameters to root signatures and parameter sets.
    enum class BindingType
    {
        TextureSRV = 0,     ///< Binds as a texture srv.
        TextureUAV,         ///< Binds as a texture uav.
        BufferSRV,          ///< Binds as a buffer srv.
        BufferUAV,          ///< Binds as a buffer uav.
        AccelStructRT,      ///< Binds as an acceleration structure.
        CBV,                ///< Binds as a constant buffer.
        Sampler,            ///< Binds as a sampler.
        RootConstant,       ///< Binds as a root constant buffer.
        Root32BitConstant,  ///< Binds as a 32-bit push constant.
        Invalid,            ///< Invalid binding.
        Count = Invalid     ///< Binding type count.
    };

    /// An enumeration for resource view dimensions.
    enum class ViewDimension : uint32_t
    {
        Unknown = 0,                ///< View dimension for unknown resource.
        Buffer,                     ///< View dimension for buffer resource.
        Texture1D,                  ///< View dimension for 1D texture resource.
        Texture1DArray,             ///< View dimension for 1D texture array resource.
        Texture2D,                  ///< View dimension for 2D texture resource.
        Texture2DArray,             ///< View dimension for 2D texture array resource.
        Texture2DMS,                ///< View dimension for 2D multi-sampled texture resource.
        Texture2DMSArray,           ///< View dimension for 2D texture multi-sampled array resource.
        Texture3D,                  ///< View dimension for 3D texture resource.
        TextureCube,                ///< View dimension for cube map resource.
        TextureCubeArray,           ///< View dimension for cube map array resource.
        RTAccelerationStruct,       ///< View dimension for rt acceleration structure resource.
    };

    /// An enumeration for texture dimension.
    enum class TextureDimension : uint32_t
    {
        Unknown = 0,        ///< Unknown texture dimension.
        Texture1D,          ///< 1D texture dimension.
        Texture2D,          ///< 2D texture dimension.
        Texture3D,          ///< 3D texture dimension.
        CubeMap,            ///< Cubed texture dimension.
    };

    /// An enumeration for filter functions.
    enum class FilterFunc
    {
        MinMagMipPoint,                             
        MinMagPointMipLinear,                       
        MinPointMagLinearMipPoint,                  
        MinPointMagMipLinear,                       
        MintMagPointMipLinear,                      
        MinLinearMagMipPoint,                       
        MinLinearMagPointMipLinear,                 
        MinMagLinearMipPoint,                       
        MinMagMipLinear,                            
        Anisotropic,                                
        ComparisonMinMagMipPoint,                   
        ComparisonMinMagPointMipLinear,             
        ComparisonMinPointMagLinearMipPoint,        
        ComparisonMinPointMagMipLinear,             
        ComparisonMintMagPointMipLinear,            
        ComparisonMinLinearMagMipPoint,             
        ComparisonMinLinearMagPointMipLinear,       
        ComparisonMinMagLinearMipPoint,             
        ComparisonMinMagMipLinear,                  
        ComparisonAnisotropic                       
    };

    /// An enumeration for uv addressing mode.
    enum class AddressMode
    {
        Wrap,           ///< Tiles the texture.
        Mirror,         ///< Mirrors the texture when tiling.
        Clamp,          ///< Clamps accesses to 0.0 or 1.0.
        Border,         ///< Texture coordinates outside 0.0 or 1.0 return border color.
        MirrorOnce      ///< Takes the absolute value of the coordinate and clamps to the maximum value.
    };

    /// A structure holding HDR meta data.
    struct HDRMetadata
    {
        float RedPrimary[2];                ///< HDR red primaries.
        float GreenPrimary[2];              ///< HDR green primaries.
        float BluePrimary[2];               ///< HDR blue primaries.
        float WhitePoint[2];                ///< HDR white points.
        float MinLuminance;                 ///< HDR minimum luminance value.
        float MaxLuminance;                 ///< HDR maximum luminance value.
        float MaxContentLightLevel;         ///< HDR maximum content light level.
        float MaxFrameAverageLightLevel;    ///< HDR maximum average light level.
    };
    
    /// A structure holding resolution information.
    struct ResolutionInfo
    {
        // Core information
        uint32_t RenderWidth;       ///< The current render width.
        uint32_t RenderHeight;      ///< The current render height.
        uint32_t DisplayWidth;      ///< The current display width.
        uint32_t DisplayHeight;     ///< The current display height.

    public:

        /// Access render width as a floating point variable.
        ///
        inline float fRenderWidth()    const { return static_cast<float>(RenderWidth); }

        /// Access render height as a floating point variable.
        ///
        inline float fRenderHeight()   const { return static_cast<float>(RenderHeight); }

        /// Access display width as a floating point variable.
        ///
        inline float fDisplayWidth()   const { return static_cast<float>(DisplayWidth); }

        /// Access display height as a floating point variable.
        ///
        inline float fDisplayHeight()  const { return static_cast<float>(DisplayHeight); }

        /// Compute the render width scale ratio.
        ///
        inline float GetRenderWidthScaleRatio()   const { return fRenderWidth() / fDisplayWidth(); }

        /// Compute the render height scale ratio.
        ///
        inline float GetRenderHeightScaleRatio()  const { return fRenderHeight() / fDisplayHeight(); }

        /// Compute the render aspect ratio.
        ///
        inline float GetRenderAspectRatio()       const { return fRenderWidth() / fDisplayHeight(); }

        /// Compute the display width scale ratio.
        ///
        inline float GetDisplayWidthScaleRatio()  const { return fDisplayWidth() / fRenderWidth(); }

        /// Compute the display height scale ratio.
        ///
        inline float GetDisplayHeightScaleRatio() const { return fDisplayHeight() / fRenderHeight(); }

        /// Compute the display aspect ratio.
        ///
        inline float GetDisplayAspectRatio()      const { return fDisplayWidth() / fDisplayHeight(); }
    };

    /// An enumeration for upscaler state.
    enum class UpscalerState : uint32_t
    {
        None        = 0,        ///< No upscaling.
        PreUpscale,             ///< Currently in pre-upscale state.
        PostUpscale,            ///< Currently in post-upscale state.
    };

    /// An enumeration for 1 dimensional shading rates.
    enum class ShadingRate1D : uint32_t
    {
        ShadingRate1D_1X = 1 << 0,  ///< 1x1 shading rate.
        ShadingRate1D_2X = 1 << 1,  ///< 1x2 shading rate.
        ShadingRate1D_4X = 1 << 2   ///< 1x4 shading rate.
    };

    inline ShadingRate1D operator|(ShadingRate1D left, ShadingRate1D right)
    {
        return (ShadingRate1D)(((uint32_t)left) | ((uint32_t)right));
    }

    /// An enumeration for variable shading mode.
    enum class VariableShadingMode: uint32_t
    {
        VariableShadingMode_None = 0,   ///< No variable rate shading.
        VariableShadingMode_Per_Draw,   ///< Per-draw variable rate shading.
        VariableShadingMode_Image       ///< Image-based variable rate shading.
    };

    /// An enumeration for shading rate modes.
    enum class ShadingRate : uint32_t
    {
        ShadingRate_1X1 = ((uint32_t)ShadingRate1D::ShadingRate1D_1X << SHADING_RATE_SHIFT) | (uint32_t)ShadingRate1D::ShadingRate1D_1X,  ///< 1x1 shading rate.
        ShadingRate_1X2 = ((uint32_t)ShadingRate1D::ShadingRate1D_1X << SHADING_RATE_SHIFT) | (uint32_t)ShadingRate1D::ShadingRate1D_2X,  ///< 1x2 shading rate.
        ShadingRate_1X4 = ((uint32_t)ShadingRate1D::ShadingRate1D_1X << SHADING_RATE_SHIFT) | (uint32_t)ShadingRate1D::ShadingRate1D_4X,  ///< 1x4 shading rate.
        ShadingRate_2X1 = ((uint32_t)ShadingRate1D::ShadingRate1D_2X << SHADING_RATE_SHIFT) | (uint32_t)ShadingRate1D::ShadingRate1D_1X,  ///< 2x1 shading rate.
        ShadingRate_2X2 = ((uint32_t)ShadingRate1D::ShadingRate1D_2X << SHADING_RATE_SHIFT) | (uint32_t)ShadingRate1D::ShadingRate1D_2X,  ///< 2x2 shading rate.
        ShadingRate_2X4 = ((uint32_t)ShadingRate1D::ShadingRate1D_2X << SHADING_RATE_SHIFT) | (uint32_t)ShadingRate1D::ShadingRate1D_4X,  ///< 2x4 shading rate.
        ShadingRate_4X1 = ((uint32_t)ShadingRate1D::ShadingRate1D_4X << SHADING_RATE_SHIFT) | (uint32_t)ShadingRate1D::ShadingRate1D_1X,  ///< 4x1 shading rate.
        ShadingRate_4X2 = ((uint32_t)ShadingRate1D::ShadingRate1D_4X << SHADING_RATE_SHIFT) | (uint32_t)ShadingRate1D::ShadingRate1D_2X,  ///< 4x2 shading rate.
        ShadingRate_4X4 = ((uint32_t)ShadingRate1D::ShadingRate1D_4X << SHADING_RATE_SHIFT) | (uint32_t)ShadingRate1D::ShadingRate1D_4X   ///< 4x4 shading rate.
    };

    /// An enumeration for shading rate combiners.
    enum class ShadingRateCombiner : uint32_t
    {
        ShadingRateCombiner_Passthrough = 1 << 0,   ///< Pass through.
        ShadingRateCombiner_Override    = 1 << 1,   ///< Override.
        ShadingRateCombiner_Min         = 1 << 2,   ///< Minimum.
        ShadingRateCombiner_Max         = 1 << 3,   ///< Maximum.
        ShadingRateCombiner_Sum         = 1 << 4,   ///< Sum.
        ShadingRateCombiner_Mul         = 1 << 5    ///< Multiply.
    };
    ENUM_FLAG_OPERATORS(ShadingRateCombiner)

    /// A structure holding Variable Shading Rate feature information.
    struct FeatureInfo_VRS
    {
        bool                AdditionalShadingRatesSupported = false;    ///< True if shading rates over 2xX are supported.
        ShadingRate         ShadingRates[MAX_SHADING_RATES];            ///< Array of shading rates to use.
        uint32_t            NumShadingRates = 0;                        ///< Number of shading rates in shading rates array.
        ShadingRateCombiner Combiners;                                  ///< Number of combiners.
        uint32_t            MinTileSize[2];                             ///< Minimum tile size (x, y).
        uint32_t            MaxTileSize[2];                             ///< Maximum tile size (x, y).
    };

} // namespace Rosefinch