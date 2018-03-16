#include "../dx.hpp"
#include "file.hpp"
#include "byteswap.hpp"
#include <cstdio>
#include <cassert>

namespace gli{
namespace detail
{
	// Magic number
	static uint32_t const FOURCC_DDS = GLI_MAKEFOURCC('D', 'D', 'S', ' ');
	// Byte-swapped magic number
	static uint32_t const FOURCC_SDD = byteswap(FOURCC_DDS);

	enum dds_cubemap_flag
	{
		DDSCAPS2_CUBEMAP				= 0x00000200,
		DDSCAPS2_CUBEMAP_POSITIVEX		= 0x00000400,
		DDSCAPS2_CUBEMAP_NEGATIVEX		= 0x00000800,
		DDSCAPS2_CUBEMAP_POSITIVEY		= 0x00001000,
		DDSCAPS2_CUBEMAP_NEGATIVEY		= 0x00002000,
		DDSCAPS2_CUBEMAP_POSITIVEZ		= 0x00004000,
		DDSCAPS2_CUBEMAP_NEGATIVEZ		= 0x00008000,
		DDSCAPS2_VOLUME					= 0x00200000
	};

	enum
	{
		DDSCAPS2_CUBEMAP_ALLFACES = DDSCAPS2_CUBEMAP_POSITIVEX | DDSCAPS2_CUBEMAP_NEGATIVEX | DDSCAPS2_CUBEMAP_POSITIVEY | DDSCAPS2_CUBEMAP_NEGATIVEY | DDSCAPS2_CUBEMAP_POSITIVEZ | DDSCAPS2_CUBEMAP_NEGATIVEZ
	};

	enum dds_flag
	{
		DDSD_CAPS			= 0x00000001,
		DDSD_HEIGHT			= 0x00000002,
		DDSD_WIDTH			= 0x00000004,
		DDSD_PITCH			= 0x00000008,
		DDSD_PIXELFORMAT	= 0x00001000,
		DDSD_MIPMAPCOUNT	= 0x00020000,
		DDSD_LINEARSIZE		= 0x00080000,
		DDSD_DEPTH			= 0x00800000
	};

	enum dds_surface_flag
	{
		DDSCAPS_COMPLEX				= 0x00000008,
		DDSCAPS_MIPMAP				= 0x00400000,
		DDSCAPS_TEXTURE				= 0x00001000
	};

	struct dds_pixel_format
	{
		std::uint32_t size; // 32
		dx::ddpf flags;
		dx::d3dfmt fourCC;
		std::uint32_t bpp;
		glm::u32vec4 Mask;
	};

	struct dds_header
	{
		std::uint32_t Size;
		std::uint32_t Flags;
		std::uint32_t Height;
		std::uint32_t Width;
		std::uint32_t Pitch;
		std::uint32_t Depth;
		std::uint32_t MipMapLevels;
		std::uint32_t Reserved1[11];
		dds_pixel_format Format;
		std::uint32_t SurfaceFlags;
		std::uint32_t CubemapFlags;
		std::uint32_t Reserved2[3];
	};

	/**
	 * Swap endianness of the provided dds_header struct if needed
	 * @param Header The struct to swap endianness
	 * @param HeaderNeedsEndianSwap Whether to swap endianness or not
	 * @return The original struct if no swap is needed, otherwise the swapped struct
	 */
	inline dds_header endian_swap(dds_header const& Header, bool const HeaderNeedsEndianSwap)
	{
		if (!HeaderNeedsEndianSwap)
		{
			return Header;
		}

		return {
				byteswap(Header.Size),
				byteswap(Header.Flags),
				byteswap(Header.Height),
				byteswap(Header.Width),
				byteswap(Header.Pitch),
				byteswap(Header.Depth),
				byteswap(Header.MipMapLevels),
				{0},
				{
						byteswap(Header.Format.size),
						byteswap(Header.Format.flags),
						byteswap(Header.Format.fourCC),
						byteswap(Header.Format.bpp),
						{
								byteswap(Header.Format.Mask.x),
								byteswap(Header.Format.Mask.y),
								byteswap(Header.Format.Mask.z),
								byteswap(Header.Format.Mask.w),
						}
				},
				byteswap(Header.SurfaceFlags),
				byteswap(Header.CubemapFlags),
				{0}
		};
	}

	static_assert(sizeof(dds_header) == 124, "DDS Header size mismatch");

	enum d3d10_resource_dimension
	{
		D3D10_RESOURCE_DIMENSION_UNKNOWN     = 0,
		D3D10_RESOURCE_DIMENSION_BUFFER      = 1,
		D3D10_RESOURCE_DIMENSION_TEXTURE1D   = 2,
		D3D10_RESOURCE_DIMENSION_TEXTURE2D   = 3,
		D3D10_RESOURCE_DIMENSION_TEXTURE3D   = 4 
	};

	enum d3d10_resource_misc_flag
	{
		D3D10_RESOURCE_MISC_GENERATE_MIPS		= 0x01,
		D3D10_RESOURCE_MISC_SHARED				= 0x02,
		D3D10_RESOURCE_MISC_TEXTURECUBE			= 0x04,
		D3D10_RESOURCE_MISC_SHARED_KEYEDMUTEX	= 0x10,
		D3D10_RESOURCE_MISC_GDI_COMPATIBLE		= 0x20,
	};

	enum dds_alpha_mode
	{
		DDS_ALPHA_MODE_UNKNOWN					= 0x0,
		DDS_ALPHA_MODE_STRAIGHT					= 0x1,
		DDS_ALPHA_MODE_PREMULTIPLIED			= 0x2,
		DDS_ALPHA_MODE_OPAQUE					= 0x3,
		DDS_ALPHA_MODE_CUSTOM					= 0x4
	};

	struct dds_header10
	{
		dds_header10() :
			Format(dx::DXGI_FORMAT_UNKNOWN),
			ResourceDimension(D3D10_RESOURCE_DIMENSION_UNKNOWN),
			MiscFlag(0),
			ArraySize(0),
			AlphaFlags(DDS_ALPHA_MODE_UNKNOWN)
		{}

		dx::dxgiFormat				Format;
		d3d10_resource_dimension	ResourceDimension;
		std::uint32_t				MiscFlag; // D3D10_RESOURCE_MISC_GENERATE_MIPS
		std::uint32_t				ArraySize;
		dds_alpha_mode				AlphaFlags; // Should be 0 whenever possible to avoid D3D utility library to fail
	};

	/**
	 * Swap endianness of the provided dds_header10 struct if needed
	 * @param Header10 The struct to swap endianness
	 * @param HeaderNeedsEndianSwap Whether to swap endianness or not
	 * @return The original struct if no swap is needed, otherwise the swapped struct
	 */
	inline dds_header10 endian_swap(dds_header10 const& Header10, bool const HeaderNeedsEndianSwap)
	{
		if (!HeaderNeedsEndianSwap)
		{
			return Header10;
		}

		dds_header10 swapped_header10{};
		swapped_header10.Format.DDS = byteswap(Header10.Format.DDS);
		swapped_header10.ResourceDimension = byteswap(Header10.ResourceDimension);
		swapped_header10.MiscFlag = byteswap(Header10.MiscFlag);
		swapped_header10.ArraySize = byteswap(Header10.ArraySize);
		swapped_header10.AlphaFlags = byteswap(Header10.AlphaFlags);

		return swapped_header10;
	}

	static_assert(sizeof(dds_header10) == 20, "DDS DX10 Extended Header size mismatch");

	inline target get_target(dds_header const& Header, dds_header10 const& Header10)
	{
		if(Header.CubemapFlags & detail::DDSCAPS2_CUBEMAP)
		{
			if(Header10.ArraySize > 1)
				return TARGET_CUBE_ARRAY;
			else
				return TARGET_CUBE;
		}
		else if(Header10.ArraySize > 1)
		{
			if(Header.Flags & detail::DDSD_HEIGHT)
				return TARGET_2D_ARRAY;
			else
				return TARGET_1D_ARRAY;
		}
		else if(Header10.ResourceDimension == D3D10_RESOURCE_DIMENSION_TEXTURE1D)
			return TARGET_1D;
		else if(Header10.ResourceDimension == D3D10_RESOURCE_DIMENSION_TEXTURE3D || Header.Flags & detail::DDSD_DEPTH || Header.CubemapFlags & detail::DDSCAPS2_VOLUME)
			return TARGET_3D;
		else
			return TARGET_2D;
	}

	// Some formats have multiple fourcc values. This function allows remapping to the default fourcc value of a format
	inline dx::d3dfmt remap_four_cc(dx::d3dfmt FourCC)
	{
		switch(FourCC)
		{
		default:
			return FourCC;
		case dx::D3DFMT_BC4U:
			return dx::D3DFMT_ATI1;
		case dx::D3DFMT_BC4S:
			return dx::D3DFMT_AT1N;
		case dx::D3DFMT_BC5U:
			return dx::D3DFMT_ATI2;
		case dx::D3DFMT_BC5S:
			return dx::D3DFMT_AT2N;
		}
	}
}//namespace detail

	inline texture load_dds(char const * Data, std::size_t Size)
	{
		GLI_ASSERT(Data && (Size >= sizeof(detail::FOURCC_DDS)));

		// Check DDS magic word, "DDS ", as fourCC.
		// If we're on a big endian platform, it should be " SDD" (read as fourCC)
		// and we'll need to swap header endianness for both dds_header and dds_header10.
		// (Are textures ever accessed as anything greater than 1 byte? If so we might need to
		// byte swap texture data in those cases...)
		uint32_t const * const MagicWord = reinterpret_cast<uint32_t const *>(Data);
		bool HeaderNeedsEndianSwap;
		if(*MagicWord == detail::FOURCC_DDS)
		{
			HeaderNeedsEndianSwap = false;
		}
		else if(*MagicWord == detail::FOURCC_SDD)
		{
			HeaderNeedsEndianSwap = true;
		}
		else
		{
			return texture();
		}
		std::size_t Offset = sizeof(detail::FOURCC_DDS);

		GLI_ASSERT(Size >= sizeof(detail::dds_header));

		detail::dds_header const Header = endian_swap(*reinterpret_cast<detail::dds_header const *>(Data + Offset), HeaderNeedsEndianSwap);
		Offset += sizeof(detail::dds_header);

		detail::dds_header10 Header10;
		if((Header.Format.flags & dx::DDPF_FOURCC) && (Header.Format.fourCC == dx::D3DFMT_DX10 || Header.Format.fourCC == dx::D3DFMT_GLI1))
		{
			std::memcpy(&Header10, Data + Offset, sizeof(Header10));
			Header10 = endian_swap(Header10, HeaderNeedsEndianSwap);
			Offset += sizeof(detail::dds_header10);
		}

		dx DX;

		gli::format Format(static_cast<gli::format>(gli::FORMAT_INVALID));
		if((Header.Format.flags & (dx::DDPF_RGB | dx::DDPF_ALPHAPIXELS | dx::DDPF_ALPHA | dx::DDPF_YUV | dx::DDPF_LUMINANCE)) && Format == static_cast<format>(gli::FORMAT_INVALID) && Header.Format.bpp != 0)
		{
			switch(Header.Format.bpp)
			{
				default:
					GLI_ASSERT(0);
					break;
				case 8:
				{
					if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_RG4_UNORM_PACK8).Mask)))
						Format = FORMAT_RG4_UNORM_PACK8;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_L8_UNORM_PACK8).Mask)))
						Format = FORMAT_L8_UNORM_PACK8;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_A8_UNORM_PACK8).Mask)))
						Format = FORMAT_A8_UNORM_PACK8;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_R8_UNORM_PACK8).Mask)))
						Format = FORMAT_R8_UNORM_PACK8;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_RG3B2_UNORM_PACK8).Mask)))
						Format = FORMAT_RG3B2_UNORM_PACK8;
					else
						GLI_ASSERT(0);
					break;
				}
				case 16:
				{
					if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_RGBA4_UNORM_PACK16).Mask)))
						Format = FORMAT_RGBA4_UNORM_PACK16;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_BGRA4_UNORM_PACK16).Mask)))
						Format = FORMAT_BGRA4_UNORM_PACK16;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_R5G6B5_UNORM_PACK16).Mask)))
						Format = FORMAT_R5G6B5_UNORM_PACK16;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_B5G6R5_UNORM_PACK16).Mask)))
						Format = FORMAT_B5G6R5_UNORM_PACK16;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_RGB5A1_UNORM_PACK16).Mask)))
						Format = FORMAT_RGB5A1_UNORM_PACK16;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_BGR5A1_UNORM_PACK16).Mask)))
						Format = FORMAT_BGR5A1_UNORM_PACK16;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_LA8_UNORM_PACK8).Mask)))
						Format = FORMAT_LA8_UNORM_PACK8;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_RG8_UNORM_PACK8).Mask)))
						Format = FORMAT_RG8_UNORM_PACK8;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_L16_UNORM_PACK16).Mask)))
						Format = FORMAT_L16_UNORM_PACK16;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_A16_UNORM_PACK16).Mask)))
						Format = FORMAT_A16_UNORM_PACK16;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_R16_UNORM_PACK16).Mask)))
						Format = FORMAT_R16_UNORM_PACK16;
					else
						GLI_ASSERT(0);
					break;
				}
				case 24:
				{
					if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_RGB8_UNORM_PACK8).Mask)))
						Format = FORMAT_RGB8_UNORM_PACK8;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_BGR8_UNORM_PACK8).Mask)))
						Format = FORMAT_BGR8_UNORM_PACK8;
					else
						GLI_ASSERT(0);
					break;
				}
				case 32:
				{
					if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_BGR8_UNORM_PACK32).Mask)))
						Format = FORMAT_BGR8_UNORM_PACK32;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_BGRA8_UNORM_PACK8).Mask)))
						Format = FORMAT_BGRA8_UNORM_PACK8;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_RGBA8_UNORM_PACK8).Mask)))
						Format = FORMAT_RGBA8_UNORM_PACK8;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_RGB10A2_UNORM_PACK32).Mask)))
						Format = FORMAT_RGB10A2_UNORM_PACK32;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_LA16_UNORM_PACK16).Mask)))
						Format = FORMAT_LA16_UNORM_PACK16;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_RG16_UNORM_PACK16).Mask)))
						Format = FORMAT_RG16_UNORM_PACK16;
					else if(glm::all(glm::equal(Header.Format.Mask, DX.translate(FORMAT_R32_SFLOAT_PACK32).Mask)))
						Format = FORMAT_R32_SFLOAT_PACK32;
					else
						GLI_ASSERT(0);
					break;
				}
			}
		}
		else if((Header.Format.flags & dx::DDPF_FOURCC) && (Header.Format.fourCC != dx::D3DFMT_DX10) && (Header.Format.fourCC != dx::D3DFMT_GLI1) && (Format == static_cast<format>(gli::FORMAT_INVALID)))
		{
			dx::d3dfmt const FourCC = detail::remap_four_cc(Header.Format.fourCC);
			Format = DX.find(FourCC);
		}
		else if(Header.Format.fourCC == dx::D3DFMT_DX10 || Header.Format.fourCC == dx::D3DFMT_GLI1)
			Format = DX.find(Header.Format.fourCC, Header10.Format);

		GLI_ASSERT(Format != static_cast<format>(gli::FORMAT_INVALID));

		if (HeaderNeedsEndianSwap)
		{
			detail::formatInfo const& FormatInfo = detail::get_format_info(Format);
			// If BlockSize > 1, we need to change byte order of texture data. Not implemented.
			GLI_ASSERT(FormatInfo.BlockSize == 1);
		}

		size_t const MipMapCount = (Header.Flags & detail::DDSD_MIPMAPCOUNT) ? Header.MipMapLevels : 1;
		size_t FaceCount = 1;
		if(Header.CubemapFlags & detail::DDSCAPS2_CUBEMAP)
			FaceCount = int(glm::bitCount(Header.CubemapFlags & detail::DDSCAPS2_CUBEMAP_ALLFACES));

		size_t DepthCount = 1;
		if(Header.CubemapFlags & detail::DDSCAPS2_VOLUME)
			DepthCount = Header.Depth;

		texture Texture(
			get_target(Header, Header10), Format,
			texture::extent_type(Header.Width, Header.Height, DepthCount),
			std::max<texture::size_type>(Header10.ArraySize, 1), FaceCount, MipMapCount);

		std::size_t const SourceSize = Offset + Texture.size();
		GLI_ASSERT(SourceSize == Size);

		std::memcpy(Texture.data(), Data + Offset, Texture.size());

		return Texture;
	}

	inline texture load_dds(char const * Filename)
	{
		FILE* File = detail::open_file(Filename, "rb");
		if(!File)
			return texture();

		long Beg = std::ftell(File);
		std::fseek(File, 0, SEEK_END);
		long End = std::ftell(File);
		std::fseek(File, 0, SEEK_SET);

		std::vector<char> Data(static_cast<std::size_t>(End - Beg));

		std::fread(&Data[0], 1, Data.size(), File);
		std::fclose(File);

		return load_dds(&Data[0], Data.size());
	}

	inline texture load_dds(std::string const & Filename)
	{
		return load_dds(Filename.c_str());
	}
}//namespace gli
