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

#ifndef _MD5_API_
#define _MD5_API_

typedef unsigned int uint4;
typedef unsigned short int uint2;
typedef unsigned char uchar;

char* print_md5(uchar digest[16], char* buffer, size_t size);
char* md5_string(const char* szString, char* buffer, size_t size);
char* md5_file(const char* szFilename, char* buffer, size_t size);

class md5
{
public:
	md5() 
	{ 
		init(); 
	}

	void init();
	void update(uchar* chInput, uint4 nInputLen);
	void finalize();
	
	uchar* digest() 
	{ 
		return m_Digest; 
	}

private:
	void transform(uchar* block);
	void encode(uchar* dest, uint4* src, uint4 nLength);
	void decode(uint4* dest, uchar* src, uint4 nLength);

	inline uint4 rotate_left(uint4 x, uint4 n)
	{ 
		return ((x << n) | (x >> (32-n))); 
	}

	inline uint4 f(uint4 x, uint4 y, uint4 z)
	{ 
		return ((x & y) | (~x & z)); 
	}

	inline uint4 g(uint4 x, uint4 y, uint4 z)
	{ 
		return ((x & z) | (y & ~z)); 
	}

	inline uint4 h(uint4 x, uint4 y, uint4 z)
	{ 
		return (x ^ y ^ z); 
	}

	inline uint4 i(uint4 x, uint4 y, uint4 z)
	{ 
		return (y ^ (x | ~z)); 
	}

	inline void ff(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
	{ 
		a += f(b, c, d) + x + ac; 
		a = rotate_left(a, s); 
		a += b; 
	}

	inline void gg(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
    { 
		a += g(b, c, d) + x + ac; 
		a = rotate_left(a, s); 
		a += b; 
	}

	inline void hh(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
    { 
		a += h(b, c, d) + x + ac; 
		a = rotate_left(a, s); 
		a += b; 
	}

	inline void ii(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
    { 
		a += i(b, c, d) + x + ac; 
		a = rotate_left(a, s); 
		a += b; 
	}

private:
	uint4 m_State[4];
	uint4 m_Count[2];
	uchar m_Buffer[64];
	uchar m_Digest[16];
	uchar m_Finalized;
};

#endif
