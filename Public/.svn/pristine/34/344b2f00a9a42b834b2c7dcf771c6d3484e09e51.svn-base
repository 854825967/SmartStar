/////////////////////////////////////////////////////////////////////////
// MD5.cpp
// Implementation file for MD5 class
//
// This C++ Class implementation of the original RSA Data Security, Inc.
// MD5 Message-Digest Algorithm is copyright (c) 2002, Gary McNickle.
// All rights reserved.  This software is a derivative of the "RSA Data
//  Security, Inc. MD5 Message-Digest Algorithm"
//
// You may use this software free of any charge, but without any
// warranty or implied warranty, provided that you follow the terms
// of the original RSA copyright, listed below.
//
// Original RSA Data Security, Inc. Copyright notice
/////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
// rights reserved.
//
// License to copy and use this software is granted provided that it
// is identified as the "RSA Data Security, Inc. MD5 Message-Digest
// Algorithm" in all material mentioning or referencing this software
// or this function.
// License is also granted to make and use derivative works provided
// that such works are identified as "derived from the RSA Data
// Security, Inc. MD5 Message-Digest Algorithm" in all material
// mentioning or referencing the derived work.
// RSA Data Security, Inc. makes no representations concerning either
// the merchantability of this software or the suitability of this
// software for any particular purpose. It is provided "as is"
// without express or implied warranty of any kind.
// These notices must be retained in any copies of any part of this
// documentation and/or software.
/////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include "MultiSys.h"
#include "md5.h"

static unsigned char padding[64] =
{
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

// Converts a completed md5 digest into a char* string.
char* print_md5(uchar digest[16], char* buffer, size_t size)
{
	assert(size > 32);

	SafeSprintf(buffer, size, 
		"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
		digest[0], digest[1], digest[2], digest[3],
		digest[4], digest[5], digest[6], digest[7],
		digest[8], digest[9], digest[10], digest[11],
		digest[12], digest[13], digest[14], digest[15]);

	return buffer;
}

// Performs the MD5 algorithm on a char* string
// returning the results as a char*.
char* md5_string(const char* szString, char* buffer, size_t size)
{
	size_t nLen = strlen(szString);

	md5 alg;

	alg.update((unsigned char*)szString, (unsigned int)nLen);
	alg.finalize();

	return print_md5(alg.digest(), buffer, size);

}

// Performs the MD5 algorithm on a file (binar or text),
// returning the results as a char*.  Returns NULL if it fails.
char* md5_file(const char* szFilename, char* buffer, size_t size)
{
	FILE* file;
	md5 alg;
	size_t nLen;
	unsigned char chBuffer[1024];

// 	try
// 	{
		memset(chBuffer, 0, 1024);

		if ((file = fopen(szFilename, "rb")) != NULL)
		{
			while (nLen = fread(chBuffer, 1, 1024, file))
			{
				alg.update(chBuffer, (unsigned int)nLen);
			}

			alg.finalize();

			fclose(file);

			return print_md5(alg.digest(), buffer, size);
		}
// 	}
// 	catch (...)
// 	{
// 	}

	return NULL; // failed
}

// Initializes a new context.
void md5::init()
{
	memset(m_Count, 0, 2 * sizeof(uint4));

	m_State[0] = 0x67452301;
	m_State[1] = 0xefcdab89;
	m_State[2] = 0x98badcfe;
	m_State[3] = 0x10325476;
}

// MD5 block update operation. Continues an MD5 message-digest operation, 
// processing another message block, and updating the context.
void md5::update(uchar* chInput, uint4 nInputLen)
{
	uint4 i, index, partLen;

	// Compute number of bytes mod 64
	index = (unsigned int)((m_Count[0] >> 3) & 0x3F);

	// Update number of bits
	if ((m_Count[0] += (nInputLen << 3)) < (nInputLen << 3))
	{
		m_Count[1]++;
	}

	m_Count[1] += (nInputLen >> 29);

	partLen = 64 - index;

	// Transform as many times as possible.
	if (nInputLen >= partLen)
	{
		memcpy(&m_Buffer[index], chInput, partLen);

		transform(m_Buffer);

		for (i = partLen; i + 63 < nInputLen; i += 64)
		{
			transform(&chInput[i]);
		}

		index = 0;
	}
	else
	{
		i = 0;
	}

	// Buffer remaining input
	memcpy(&m_Buffer[index], &chInput[i], nInputLen - i);
}

// MD5 finalization. Ends an MD5 message-digest operation, writing
// the message digest and zeroizing the context.
void md5::finalize()
{
	uchar bits[8];
	uint4 index, padLen;

	// Save number of bits
	encode(bits, m_Count, 8);

	// Pad out to 56 mod 64
	index = (unsigned int)((m_Count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	
	update(padding, padLen);

	// Append length (before padding)
	update(bits, 8);

	// Store state in digest
	encode(m_Digest, m_State, 16);

	memset(m_Count, 0, 2 * sizeof(uint4));
	memset(m_State, 0, 4 * sizeof(uint4));
	memset(m_Buffer, 0, 64 * sizeof(uchar));
}

// MD5 basic transformation. Transforms state based on block.
void md5::transform (uchar* block)
{
	uint4 a = m_State[0], b = m_State[1], c = m_State[2], d = m_State[3], x[16];

	decode(x, block, 64);

	// Round 1
	ff(a, b, c, d, x[ 0], S11, 0xd76aa478);
	ff(d, a, b, c, x[ 1], S12, 0xe8c7b756);
	ff(c, d, a, b, x[ 2], S13, 0x242070db);
	ff(b, c, d, a, x[ 3], S14, 0xc1bdceee);
	ff(a, b, c, d, x[ 4], S11, 0xf57c0faf);
	ff(d, a, b, c, x[ 5], S12, 0x4787c62a);
	ff(c, d, a, b, x[ 6], S13, 0xa8304613);
	ff(b, c, d, a, x[ 7], S14, 0xfd469501);
	ff(a, b, c, d, x[ 8], S11, 0x698098d8);
	ff(d, a, b, c, x[ 9], S12, 0x8b44f7af);
	ff(c, d, a, b, x[10], S13, 0xffff5bb1);
	ff(b, c, d, a, x[11], S14, 0x895cd7be);
	ff(a, b, c, d, x[12], S11, 0x6b901122);
	ff(d, a, b, c, x[13], S12, 0xfd987193);
	ff(c, d, a, b, x[14], S13, 0xa679438e);
	ff(b, c, d, a, x[15], S14, 0x49b40821);

	// Round 2
	gg(a, b, c, d, x[ 1], S21, 0xf61e2562);
	gg(d, a, b, c, x[ 6], S22, 0xc040b340);
	gg(c, d, a, b, x[11], S23, 0x265e5a51);
	gg(b, c, d, a, x[ 0], S24, 0xe9b6c7aa);
	gg(a, b, c, d, x[ 5], S21, 0xd62f105d);
	gg(d, a, b, c, x[10], S22,  0x2441453);
	gg(c, d, a, b, x[15], S23, 0xd8a1e681);
	gg(b, c, d, a, x[ 4], S24, 0xe7d3fbc8);
	gg(a, b, c, d, x[ 9], S21, 0x21e1cde6);
	gg(d, a, b, c, x[14], S22, 0xc33707d6);
	gg(c, d, a, b, x[ 3], S23, 0xf4d50d87);
	gg(b, c, d, a, x[ 8], S24, 0x455a14ed);
	gg(a, b, c, d, x[13], S21, 0xa9e3e905);
	gg(d, a, b, c, x[ 2], S22, 0xfcefa3f8);
	gg(c, d, a, b, x[ 7], S23, 0x676f02d9);
	gg(b, c, d, a, x[12], S24, 0x8d2a4c8a);

	// Round 3
	hh(a, b, c, d, x[ 5], S31, 0xfffa3942);
	hh(d, a, b, c, x[ 8], S32, 0x8771f681);
	hh(c, d, a, b, x[11], S33, 0x6d9d6122);
	hh(b, c, d, a, x[14], S34, 0xfde5380c);
	hh(a, b, c, d, x[ 1], S31, 0xa4beea44);
	hh(d, a, b, c, x[ 4], S32, 0x4bdecfa9);
	hh(c, d, a, b, x[ 7], S33, 0xf6bb4b60);
	hh(b, c, d, a, x[10], S34, 0xbebfbc70);
	hh(a, b, c, d, x[13], S31, 0x289b7ec6);
	hh(d, a, b, c, x[ 0], S32, 0xeaa127fa);
	hh(c, d, a, b, x[ 3], S33, 0xd4ef3085);
	hh(b, c, d, a, x[ 6], S34,  0x4881d05);
	hh(a, b, c, d, x[ 9], S31, 0xd9d4d039);
	hh(d, a, b, c, x[12], S32, 0xe6db99e5);
	hh(c, d, a, b, x[15], S33, 0x1fa27cf8);
	hh(b, c, d, a, x[ 2], S34, 0xc4ac5665);

	// Round 4
	ii(a, b, c, d, x[ 0], S41, 0xf4292244);
	ii(d, a, b, c, x[ 7], S42, 0x432aff97);
	ii(c, d, a, b, x[14], S43, 0xab9423a7);
	ii(b, c, d, a, x[ 5], S44, 0xfc93a039);
	ii(a, b, c, d, x[12], S41, 0x655b59c3);
	ii(d, a, b, c, x[ 3], S42, 0x8f0ccc92);
	ii(c, d, a, b, x[10], S43, 0xffeff47d);
	ii(b, c, d, a, x[ 1], S44, 0x85845dd1);
	ii(a, b, c, d, x[ 8], S41, 0x6fa87e4f);
	ii(d, a, b, c, x[15], S42, 0xfe2ce6e0);
	ii(c, d, a, b, x[ 6], S43, 0xa3014314);
	ii(b, c, d, a, x[13], S44, 0x4e0811a1);
	ii(a, b, c, d, x[ 4], S41, 0xf7537e82);
	ii(d, a, b, c, x[11], S42, 0xbd3af235);
	ii(c, d, a, b, x[ 2], S43, 0x2ad7d2bb);
	ii(b, c, d, a, x[ 9], S44, 0xeb86d391);

	m_State[0] += a;
	m_State[1] += b;
	m_State[2] += c;
	m_State[3] += d;

	memset(x, 0, sizeof(x));
}

// Encodes input (uint4) into output (uchar). Assumes nLength is
// a multiple of 4.
void md5::encode(uchar* dest, uint4* src, uint4 nLength)
{
	uint4 i, j;

	assert(nLength % 4 == 0);

	for (i = 0, j = 0; j < nLength; i++, j += 4)
	{
		dest[j] = (uchar)(src[i] & 0xff);
		dest[j + 1] = (uchar)((src[i] >> 8) & 0xff);
		dest[j + 2] = (uchar)((src[i] >> 16) & 0xff);
		dest[j + 3] = (uchar)((src[i] >> 24) & 0xff);
	}
}

// Decodes input (uchar) into output (uint4). Assumes nLength is
// a multiple of 4.
void md5::decode(uint4* dest, uchar* src, uint4 nLength)
{
	uint4 i, j;

	assert(nLength % 4 == 0);

	for (i = 0, j = 0; j < nLength; i++, j += 4)
	{
		dest[i] = ((uint4)src[j]) | (((uint4)src[j + 1]) << 8) 
			| (((uint4)src[j + 2]) << 16) | (((uint4)src[j + 3]) << 24);
	}
}

