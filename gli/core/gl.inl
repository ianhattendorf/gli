///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2015 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file gli/core/gl.inl
/// @date 2013-11-09 / 2013-11-09
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include <algorithm>

namespace gli
{
	inline gl::gl()
	{
		static format const Table[] =
		{
			// unorm formats
			{INTERNAL_R8_UNORM, EXTERNAL_RED, TYPE_U8, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},						//R8_UNORM,
			{INTERNAL_RG8_UNORM, EXTERNAL_RG, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},					//RG8_UNORM,
			{INTERNAL_RGB8_UNORM, EXTERNAL_RGB, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},					//RGB8_UNORM,
			{INTERNAL_RGBA8_UNORM, EXTERNAL_RGBA, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//RGBA8_UNORM,

			{INTERNAL_R16_UNORM, EXTERNAL_RED, TYPE_U16, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},					//R16_UNORM,
			{INTERNAL_RG16_UNORM, EXTERNAL_RG, TYPE_U16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},					//RG16_UNORM,
			{INTERNAL_RGB16_UNORM, EXTERNAL_RGB, TYPE_U16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},				//RGB16_UNORM,
			{INTERNAL_RGBA16_UNORM, EXTERNAL_RGBA, TYPE_U16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},			//RGBA16_UNORM,

			// snorm formats
			{INTERNAL_R8_SNORM, EXTERNAL_RED, TYPE_I8, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},						//R8_SNORM,
			{INTERNAL_RG8_SNORM, EXTERNAL_RG, TYPE_I8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},					//RG8_SNORM,
			{INTERNAL_RGB8_SNORM, EXTERNAL_RGB, TYPE_I8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},					//RGB8_SNORM,
			{INTERNAL_RGBA8_SNORM, EXTERNAL_RGBA, TYPE_I8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//RGBA8_SNORM,

			{INTERNAL_R16_SNORM, EXTERNAL_RED, TYPE_I16, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},					//R16_SNORM,
			{INTERNAL_RG16_SNORM, EXTERNAL_RG, TYPE_I16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},					//RG16_SNORM,
			{INTERNAL_RGB16_SNORM, EXTERNAL_RGB, TYPE_I16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},				//RGB16_SNORM,
			{INTERNAL_RGBA16_SNORM, EXTERNAL_RGBA, TYPE_I16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},			//RGBA16_SNORM,

			// Unsigned integer formats
			{INTERNAL_R8U, EXTERNAL_RED_INTEGER, TYPE_U8, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},					//R8U,
			{INTERNAL_RG8U, EXTERNAL_RG_INTEGER, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},					//RG8U,
			{INTERNAL_RGB8U, EXTERNAL_RGB_INTEGER, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},				//RGB8U,
			{INTERNAL_RGBA8U, EXTERNAL_RGBA_INTEGER, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},			//RGBA8U,

			{INTERNAL_R16U, EXTERNAL_RED_INTEGER, TYPE_U16, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},				//R16U,
			{INTERNAL_RG16U, EXTERNAL_RG_INTEGER, TYPE_U16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},				//RG16U,
			{INTERNAL_RGB16U, EXTERNAL_RGB_INTEGER, TYPE_U16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},				//RGB16U,
			{INTERNAL_RGBA16U, EXTERNAL_RGBA_INTEGER, TYPE_U16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},			//RGBA16U,

			{INTERNAL_R32U, EXTERNAL_RED_INTEGER, TYPE_U32, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},				//R32U,
			{INTERNAL_RG32U, EXTERNAL_RG_INTEGER, TYPE_U32, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},				//RG32U,
			{INTERNAL_RGB32U, EXTERNAL_RGB_INTEGER, TYPE_U32, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},				//RGB32U,
			{INTERNAL_RGBA32U, EXTERNAL_RGBA_INTEGER, TYPE_U32, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},			//RGBA32U,

			/// Signed integer formats
			{INTERNAL_R8I, EXTERNAL_RED_INTEGER, TYPE_I8, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},					//R8I,
			{INTERNAL_RG8I, EXTERNAL_RG_INTEGER, TYPE_I8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},					//RG8I,
			{INTERNAL_RGB8I, EXTERNAL_RGB_INTEGER, TYPE_I8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},				//RGB8I,
			{INTERNAL_RGBA8I, EXTERNAL_RGBA_INTEGER, TYPE_I8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},			//RGBA8I,

			{INTERNAL_R16I, EXTERNAL_RED_INTEGER, TYPE_I16, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},				//R16I,
			{INTERNAL_RG16I, EXTERNAL_RG_INTEGER, TYPE_I16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},				//RG16I,
			{INTERNAL_RGB16I, EXTERNAL_RGB_INTEGER, TYPE_I16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},				//RGB16I,
			{INTERNAL_RGBA16I, EXTERNAL_RGBA_INTEGER, TYPE_I16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},			//RGBA16I,

			{INTERNAL_R32I, EXTERNAL_RED_INTEGER, TYPE_I32, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},				//R32I,
			{INTERNAL_RG32I, EXTERNAL_RG_INTEGER, TYPE_I32, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},				//RG32I,
			{INTERNAL_RGB32I, EXTERNAL_RGB_INTEGER, TYPE_I32, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},				//RGB32I,
			{INTERNAL_RGBA32I, EXTERNAL_RGBA_INTEGER, TYPE_I32, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},			//RGBA32I,

			/// Floating formats
			{INTERNAL_R16F, EXTERNAL_RED, TYPE_F16, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},						//R16F,
			{INTERNAL_RG16F, EXTERNAL_RG, TYPE_F16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},						//RG16F,
			{INTERNAL_RGB16F, EXTERNAL_RGB, TYPE_F16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},						//RGB16F,
			{INTERNAL_RGBA16F, EXTERNAL_RGBA, TYPE_F16, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//RGBA16F,

			{INTERNAL_R32F, EXTERNAL_RED, TYPE_F32, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},						//R32F,
			{INTERNAL_RG32F, EXTERNAL_RG, TYPE_F32, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},						//RG32F,
			{INTERNAL_RGB32F, EXTERNAL_RGB, TYPE_F32, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},						//RGB32F,
			{INTERNAL_RGBA32F, EXTERNAL_RGBA, TYPE_F32, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//RGBA32F,

			/// sRGB formats
			{INTERNAL_SR8, EXTERNAL_RED, TYPE_U8, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},							//SR8_UNORM,
			{INTERNAL_SRG8, EXTERNAL_RG, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},							//SRG8_UNORM,
			{INTERNAL_SRGB8, EXTERNAL_RGB, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},						//SRGB8_UNORM,
			{INTERNAL_SRGB8_ALPHA8, EXTERNAL_RGBA, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//SRGB8_ALPHA8_UNORM,

			/// Packed formats
			{INTERNAL_RGB10A2_UNORM, EXTERNAL_RGBA, TYPE_UINT32_RGB10A2, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},		//RGB10A2_UNORM,
			{INTERNAL_RGB10A2U, EXTERNAL_RGBA_INTEGER, TYPE_UINT32_RGB10A2, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},		//RGB10A2U,
			{INTERNAL_RGB9E5, EXTERNAL_RGB, TYPE_UINT32_RGB9_E5, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},					//RGB9E5,
			{INTERNAL_RG11B10F, EXTERNAL_RGB, TYPE_UINT32_RG11B10F, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},				//RG11B10F,
			{INTERNAL_RG3B2, EXTERNAL_RGB, TYPE_UINT8_RG3B2, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},						//RG3B2,
			{INTERNAL_R5G6B5, EXTERNAL_RGB, TYPE_UINT16_R5G6B5, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},					//R5G6B5,
			{INTERNAL_RGB5A1, EXTERNAL_RGBA, TYPE_UINT16_RGB5A1, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//RGB5A1,
			{INTERNAL_RGBA4, EXTERNAL_RGBA, TYPE_UINT16_RGBA4, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//RGBA4,

			// Swizzle formats
			{INTERNAL_RGB8_UNORM, EXTERNAL_BGR, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},					//FORMAT_BGRX8_UNORM,
			{INTERNAL_RGBA8_UNORM, EXTERNAL_BGRA, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//FORMAT_BGRA8_UNORM,
			{INTERNAL_SRGB8, EXTERNAL_BGR, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},						//FORMAT_BGRX8_SRGB,
			{INTERNAL_SRGB8_ALPHA8, EXTERNAL_BGRA, TYPE_U8, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//FORMAT_BGRA8_SRGB,

			// Luminance Alpha formats
			{INTERNAL_RG8_UNORM, EXTERNAL_RED, TYPE_U8, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},					//L8_UNORM,
			{INTERNAL_RGB8_UNORM, EXTERNAL_RED, TYPE_U8, {SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_RED}},					//A8_UNORM,
			{INTERNAL_RG8_UNORM, EXTERNAL_RG, TYPE_U8, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_GREEN}},					//LA8_UNORM,
			{INTERNAL_R16_UNORM, EXTERNAL_RED, TYPE_U16, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},					//L16_UNORM,
			{INTERNAL_R16_UNORM, EXTERNAL_RED, TYPE_U16, {SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_RED}},					//A16_UNORM,
			{INTERNAL_RG16_UNORM, EXTERNAL_RG, TYPE_U16, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_GREEN}},					//LA16_UNORM,

			/// Depth formats
			{INTERNAL_D16, EXTERNAL_DEPTH, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//D16,
			{INTERNAL_D24, EXTERNAL_DEPTH, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//D24X8,
			{INTERNAL_D24S8, EXTERNAL_DEPTH_STENCIL, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},			//D24S8,
			{INTERNAL_D32F, EXTERNAL_DEPTH, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//D32F,
			{INTERNAL_D32FS8X24, EXTERNAL_DEPTH_STENCIL, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},		//D32FS8X24,

			/// Compressed formats
			{INTERNAL_RGB_DXT1, EXTERNAL_RGB_DXT1, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},												//RGB_DXT1_UNORM,
			{INTERNAL_RGBA_DXT1, EXTERNAL_RGBA_DXT1, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},											//RGBA_DXT1_UNORM,
			{INTERNAL_RGBA_DXT3, EXTERNAL_RGBA_DXT3, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},											//RGBA_DXT3_UNORM,
			{INTERNAL_RGBA_DXT5, EXTERNAL_RGBA_DXT5, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},											//RGBA_DXT5_UNORM,
			{INTERNAL_R_ATI1N_UNORM, EXTERNAL_R_ATI1N_UNORM, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},									//R_ATI1N_UNORM,
			{INTERNAL_R_ATI1N_SNORM, EXTERNAL_R_ATI1N_SNORM, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE}},									//R_ATI1N_SNORM,
			{INTERNAL_RG_ATI2N_UNORM, EXTERNAL_RG_ATI2N_UNORM, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},									//RG_ATI2N_UNORM,
			{INTERNAL_RG_ATI2N_SNORM, EXTERNAL_RG_ATI2N_SNORM, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE}},									//RG_ATI2N_SNORM,
			{INTERNAL_RGB_BP_UNSIGNED_FLOAT, EXTERNAL_RGB_BP_UNSIGNED_FLOAT, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},					//RGB_BP_UF16,
			{INTERNAL_RGB_BP_SIGNED_FLOAT, EXTERNAL_RGB_BP_SIGNED_FLOAT, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},						//RGB_BP_SF16,
			{INTERNAL_RGB_BP_UNORM, EXTERNAL_RGB_BP_UNORM, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},										//RGB_BP_UNORM,
			{INTERNAL_RGB_PVRTC_4BPPV1, EXTERNAL_RGB_PVRTC_4BPPV1, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},								//RGB_PVRTC_4BPP_UNORM,
			{INTERNAL_RGB_PVRTC_2BPPV1, EXTERNAL_RGB_PVRTC_2BPPV1, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},								//RGB_PVRTC_2BPP_UNORM,
			{INTERNAL_RGBA_PVRTC_4BPPV1, EXTERNAL_RGBA_PVRTC_4BPPV1, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},							//RGBA_PVRTC_4BPP_UNORM,
			{INTERNAL_RGBA_PVRTC_2BPPV1, EXTERNAL_RGBA_PVRTC_2BPPV1, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},							//RGBA_PVRTC_2BPP_UNORM,
			{INTERNAL_RGBA_PVRTC_4BPPV2, EXTERNAL_RGBA_PVRTC_4BPPV2, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},							//RGBA_PVRTC2_4BPP_UNORM,
			{INTERNAL_RGBA_PVRTC_2BPPV2, EXTERNAL_RGBA_PVRTC_2BPPV2, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},							//RGBA_PVRTC2_2BPP_UNORM,
			{INTERNAL_ATC_RGB, EXTERNAL_ATC_RGB, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},												//ATC_RGB_UNORM,
			{INTERNAL_ATC_RGBA_EXPLICIT_ALPHA, EXTERNAL_ATC_RGBA_EXPLICIT_ALPHA, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//ATC_RGBA_EXPLICIT_ALPHA_UNORM,
			{INTERNAL_ATC_RGBA_INTERPOLATED_ALPHA, EXTERNAL_ATC_RGBA_INTERPOLATED_ALPHA, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},		//ATC_RGBA_INTERPOLATED_ALPHA_UNORM,
			{INTERNAL_RGB_ETC2, EXTERNAL_RGB8_ETC2, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},											//FORMAT_RGB_ETC_UNORM,
			{INTERNAL_RGBA_PUNCHTHROUGH_ETC2, EXTERNAL_RGBA_PUNCHTHROUGH_ETC2_SRGB, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},			//FORMAT_RGBA_ETC2_PUNCHTHROUGH_UNORM,
			{INTERNAL_RGBA_ETC2_EAC, EXTERNAL_RGBA8_ETC2_EAC, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},								//FORMAT_RGBA_ETC2_UNORM,
			{INTERNAL_R11_EAC, EXTERNAL_R11_EAC, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},												//R11_EAC_UNORM,
			{INTERNAL_SIGNED_R11_EAC, EXTERNAL_SIGNED_R11_EAC, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},								//R11_EAC_SNORM,
			{INTERNAL_RG11_EAC, EXTERNAL_RG11_EAC, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},											//RG11_EAC_UNORM,
			{INTERNAL_SIGNED_RG11_EAC, EXTERNAL_SIGNED_RG11_EAC, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},								//RG11_EAC_SNORM,
			{INTERNAL_RGBA_ASTC_4x4, EXTERNAL_RGBA_ASTC_4x4, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},									//RGBA_ASTC_4x4_UNORM,
			{INTERNAL_RGBA_ASTC_5x4, EXTERNAL_RGBA_ASTC_5x4, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},									//RGBA_ASTC_5x4_UNORM,
			{INTERNAL_RGBA_ASTC_5x5, EXTERNAL_RGBA_ASTC_5x5, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},									//RGBA_ASTC_5x5_UNORM,
			{INTERNAL_RGBA_ASTC_6x5, EXTERNAL_RGBA_ASTC_6x5, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},									//RGBA_ASTC_6x5_UNORM,
			{INTERNAL_RGBA_ASTC_6x6, EXTERNAL_RGBA_ASTC_6x6, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},									//RGBA_ASTC_6x6_UNORM,
			{INTERNAL_RGBA_ASTC_8x5, EXTERNAL_RGBA_ASTC_8x5, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},									//RGBA_ASTC_8x5_UNORM,
			{INTERNAL_RGBA_ASTC_8x6, EXTERNAL_RGBA_ASTC_8x6, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},									//RGBA_ASTC_8x6_UNORM,
			{INTERNAL_RGBA_ASTC_8x8, EXTERNAL_RGBA_ASTC_8x8, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},									//RGBA_ASTC_8x8_UNORM,
			{INTERNAL_RGBA_ASTC_10x5, EXTERNAL_RGBA_ASTC_10x5, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},								//RGBA_ASTC_10x5_UNORM,
			{INTERNAL_RGBA_ASTC_10x6, EXTERNAL_RGBA_ASTC_10x6, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},								//RGBA_ASTC_10x6_UNORM,
			{INTERNAL_RGBA_ASTC_10x8, EXTERNAL_RGBA_ASTC_10x8, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},								//RGBA_ASTC_10x8_UNORM,
			{INTERNAL_RGBA_ASTC_10x10, EXTERNAL_RGBA_ASTC_10x10, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},								//RGBA_ASTC_10x10_UNORM,
			{INTERNAL_RGBA_ASTC_12x10, EXTERNAL_RGBA_ASTC_12x10, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},								//RGBA_ASTC_12x10_UNORM,
			{INTERNAL_RGBA_ASTC_12x12, EXTERNAL_RGBA_ASTC_12x12, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},								//RGBA_ASTC_12x12_UNORM,

			// sRGB compressed formats
			{INTERNAL_SRGB_DXT1, EXTERNAL_SRGB_DXT1, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},											//SRGB_DXT1_UNORM,
			{INTERNAL_SRGB_ALPHA_DXT1, EXTERNAL_SRGB_ALPHA_DXT1, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},								//SRGB_DXT1_UNORM,
			{INTERNAL_SRGB_ALPHA_DXT3, EXTERNAL_SRGB_ALPHA_DXT3, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},								//SRGB_DXT3_UNORM,
			{INTERNAL_SRGB_ALPHA_DXT5, EXTERNAL_SRGB_ALPHA_DXT5, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},								//SRGB_DXT5_UNORM,
			{INTERNAL_SRGB_BP_UNORM, EXTERNAL_SRGB_BP_UNORM, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},									//SRGB_BP_UNORM,
			{INTERNAL_SRGB_PVRTC_2BPPV1, EXTERNAL_SRGB_PVRTC_2BPPV1, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},							//SRGB_PVRTC_4BPP_UNORM,
			{INTERNAL_SRGB_PVRTC_4BPPV1, EXTERNAL_SRGB_PVRTC_4BPPV1, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE}},							//SRGB_PVRTC_2BPP_UNORM,
			{INTERNAL_SRGB_ALPHA_PVRTC_2BPPV1, EXTERNAL_SRGB_ALPHA_PVRTC_2BPPV1, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//SRGB_ALPHA_PVRTC_4BPP_UNORM,
			{INTERNAL_SRGB_ALPHA_PVRTC_4BPPV1, EXTERNAL_SRGB_ALPHA_PVRTC_4BPPV1, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//SRGB_ALPHA_PVRTC_2BPP_UNORM,
			{INTERNAL_SRGB_ALPHA_PVRTC_2BPPV2, EXTERNAL_SRGB_ALPHA_PVRTC_2BPPV2, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//SRGB_ALPHA_PVRTC2_4BPP_UNORM,
			{INTERNAL_SRGB_ALPHA_PVRTC_4BPPV2, EXTERNAL_SRGB_ALPHA_PVRTC_4BPPV2, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//SRGB_ALPHA_PVRTC2_2BPP_UNORM,
			{INTERNAL_SRGB8_ETC2, EXTERNAL_RGBA_ASTC_4x4, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},									//SRGB_ETC2_UNORM,
			{INTERNAL_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, EXTERNAL_RGBA_ASTC_4x4, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//SRGB_ETC2_PUNCHTHROUGH_ALPHA_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ETC2_EAC, EXTERNAL_RGBA_ASTC_4x4, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},							//SRGBA_ETC2_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_4x4, EXTERNAL_SRGB8_ALPHA8_ASTC_4x4, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//SRGB8_ALPHA8_ASTC_4x4_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_5x4, EXTERNAL_SRGB8_ALPHA8_ASTC_5x4, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//SRGB8_ALPHA8_ASTC_5x4_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_5x5, EXTERNAL_SRGB8_ALPHA8_ASTC_5x5, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//SRGB8_ALPHA8_ASTC_5x5_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_6x5, EXTERNAL_SRGB8_ALPHA8_ASTC_6x5, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//SRGB8_ALPHA8_ASTC_6x5_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_6x6, EXTERNAL_SRGB8_ALPHA8_ASTC_6x6, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//SRGB8_ALPHA8_ASTC_6x6_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_8x5, EXTERNAL_SRGB8_ALPHA8_ASTC_8x5, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//SRGB8_ALPHA8_ASTC_8x5_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_8x6, EXTERNAL_SRGB8_ALPHA8_ASTC_8x6, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//SRGB8_ALPHA8_ASTC_8x6_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_8x8, EXTERNAL_SRGB8_ALPHA8_ASTC_8x8, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},					//SRGB8_ALPHA8_ASTC_8x8_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_10x5, EXTERNAL_SRGB8_ALPHA8_ASTC_10x5, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//SRGB8_ALPHA8_ASTC_10x5_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_10x6, EXTERNAL_SRGB8_ALPHA8_ASTC_10x6, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//SRGB8_ALPHA8_ASTC_10x6_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_10x8, EXTERNAL_SRGB8_ALPHA8_ASTC_10x8, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//SRGB8_ALPHA8_ASTC_10x8_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_10x10, EXTERNAL_SRGB8_ALPHA8_ASTC_10x10, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//SRGB8_ALPHA8_ASTC_10x10_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_12x10, EXTERNAL_SRGB8_ALPHA8_ASTC_12x10, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//SRGB8_ALPHA8_ASTC_12x10_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_12x12, EXTERNAL_SRGB8_ALPHA8_ASTC_12x12, TYPE_NONE, {SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA}},				//SRGB8_ALPHA8_ASTC_12x12_UNORM,
		};

		static_assert(sizeof(Table) / sizeof(Table[0]) == FORMAT_COUNT, "GLI error: format descriptor list doesn't match number of supported formats");

		std::copy(&Table[0], &Table[0] + FORMAT_COUNT, this->Translation.begin());
	}

	inline gl::format const & gl::translate(gli::format const & Format) const
	{
		return this->Translation[Format];
	}
}//namespace gli
