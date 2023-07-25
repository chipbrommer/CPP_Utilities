///////////////////////////////////////////////////////////////////////////////
//!
//! @file		utilties.h
//! 
//! @brief		A cross platform header only files for utilties like byteswap,
//!				checksum calculations, and more
//! 
//! @author		Chip Brommer
//!
///////////////////////////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////////////////////////
//
//  Includes:
//          name                        reason included
//          --------------------        ---------------------------------------
#include	<cstdint>					// Standard Integers
#include	<iostream>					// cout
#include	<iomanip>					// Hex and Setw
// 
//	Defines:
//          name                        reason defined
//          --------------------        ---------------------------------------
#ifndef     CPP_UTILITIES_H				// Define the utilities header.
#define     CPP_UTILITIES_H
// 
///////////////////////////////////////////////////////////////////////////////

namespace Essentials
{
	namespace Utilities
	{
		/// @brief A 16 bit byteswap routine 
		/// @param value - value to be byteswapped
		/// @return - the byteswapped value
		uint16_t byteswap16(uint16_t value) 
		{
			return	(value << 8) | (value >> 8);
		}

		/// @brief A 32 bit byteswap routine 
		/// @param value - value to be byteswapped
		/// @return - the byteswapped value
		uint32_t byteswap32(uint32_t value) 
		{
			return	((value & 0xFF000000) >> 24)	|
					((value & 0x00FF0000) >> 8)		|
					((value & 0x0000FF00) << 8)		|
					((value & 0x000000FF) << 24);
		}

		/// @brief A 64 bit byteswap routine 
		/// @param value - value to be byteswapped
		/// @return - the byteswapped value
		uint64_t byteswap64(uint64_t value) 
		{
			return	((value & 0xFF00000000000000ull) >> 56) |
					((value & 0x00FF000000000000ull) >> 40) |
					((value & 0x0000FF0000000000ull) >> 24) |
					((value & 0x000000FF00000000ull) >> 8)	|
					((value & 0x00000000FF000000ull) << 8)	|
					((value & 0x0000000000FF0000ull) << 24) |
					((value & 0x000000000000FF00ull) << 40) |
					((value & 0x00000000000000FFull) << 56);
		}
	
		/// @brief A basic Fletcher 16 implementation with a 255 modulo
		/// @param data - [in] - The data to calculate the checksum for.
		/// @param length - [in] - The length of the data in bytes to validate
		/// @param startOffset - [in/opt] - Number of bytes to take off the front of the data for validation. Usually in case of a header. 
		/// @param backOffset  - [in/opt] - Number of bytes to take off the back of the data for validation. Usually in case of a footer.
		/// @return The checksum value
		uint16_t fletcher16(const uint8_t* data, uint32_t length, uint32_t startOffset = 0, uint32_t backOffset = 0)
		{
			uint16_t sum1 = 0;
			uint16_t sum2 = 0;
			const uint16_t mod = 255; 

			for (uint32_t i = startOffset; i < (length - backOffset); i++)
			{
				sum1 = (sum1 + data[i]) % mod;
				sum2 = (sum2 + sum1) % mod;
			}

			return (sum2 << 8) | sum1;
		}

		/// @brief A non-typical Fletcher 16 implementation with a 256 modulo
		/// @param data - [in] - The data to calculate the checksum for.
		/// @param length - [in] - The length of the data in bytes to validate
		/// @param startOffset - [in/opt] - Number of bytes to take off the front of the data for validation. Usually in case of a header. 
		/// @param backOffset  - [in/opt] - Number of bytes to take off the back of the data for validation. Usually in case of a footer.
		/// @return The checksum value
		uint16_t fletcher16_mod256(const uint8_t* data, uint32_t length, uint32_t startOffset = 0, uint32_t backOffset = 0)
		{
			uint16_t sum1 = 0;
			uint16_t sum2 = 0;
			const uint16_t mod = 256;

			for (uint32_t i = startOffset; i < (length - backOffset); i++)
			{
				sum1 = (sum1 + data[i]) % mod;
				sum2 = (sum2 + sum1) % mod;
			}

			return (sum2 << 8) | sum1;
		}

		/// @brief A basic Fletcher 32 implementation with a 65535 modulo
		/// @param data - [in] - The data to calculate the checksum for.
		/// @param length - [in] - The length of the data in bytes to validate
		/// @param startOffset - [in/opt] - Number of bytes to take off the front of the data for validation. Usually in case of a header. 
		/// @param backOffset  - [in/opt] - Number of bytes to take off the back of the data for validation. Usually in case of a footer.
		/// @return The checksum value
		uint32_t fletcher32(const uint8_t* data, uint32_t length, uint32_t startOffset = 0, uint32_t backOffset = 0) 
		{
			uint32_t sum1 = 0;
			uint32_t sum2 = 0;
			const uint32_t mod = 65535;

			for (uint32_t i = startOffset; i < (length - backOffset); i++)
			{
				sum1 = (sum1 + data[i]) % mod;
				sum2 = (sum2 + sum1) % mod;
			}

			return (sum2 << 16) | sum1;
		}

		/// @brief Print a buffer in 8 bit hex
		/// @param buffer - [in] - Buffer to be printed
		/// @param size - [in] -  Size of the buffer to be printed
		/// @param bytesPerLine - [in/opt] - number of bytes to be printed per line. 
		void printBufferInHex(const uint8_t* buffer, uint32_t size, uint32_t bytesPerLine = 0)
		{
			for (uint32_t i = 0; i < size; ++i) 
			{
				std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int32_t>(buffer[i]) << ' ';

				// If bytesPerLine isnt 0, print a new line after specified number of bytes. 
				if (bytesPerLine > 0 && ((i + 1) % bytesPerLine == 0)) 
				{
					std::cout << std::endl;
				}
			}

			std::cout << std::endl;
		}
	}
}

#endif // CPP_UTILITIES_H