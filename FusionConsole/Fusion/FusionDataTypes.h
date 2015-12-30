//============================================================================

#pragma once
#include <stdlib.h>
#include <string>

//============================================================================

namespace migme
{
//============================================================================
	
	// Defined this way so that alignment is naturally packed, and handles endianness

	struct Byte
	{
	public:
		typedef unsigned char NativeType;
		
		void operator=(unsigned char c)		{ b0 = c; }
		operator unsigned char() const		{ return b0; }
		
	private:
		unsigned char	b0;
	};

	struct Short
	{
	public:
		void operator=(short s)				{ b0 = (unsigned char) (s >> 8); b1 = (unsigned char) s; }
		operator short() const 				{ return (short) ((b0 << 8) | b1); }

	private:
		unsigned char	b0;
		unsigned char	b1;
	};

	struct UShort
	{
	public:
		typedef unsigned short NativeType;
		
		UShort() { }
		UShort(unsigned short s)			{ *this = s; }
		
		void operator=(unsigned short s)	{ b0 = (unsigned char) (s >> 8); b1 = (unsigned char) s; }
		operator unsigned short() const 	{ return (b0 << 8) | b1; }
		
	private:
		unsigned char	b0;
		unsigned char	b1;
	};
	

	struct Int
	{
	public:
		void operator=(int i)				{ b0 = (unsigned char) (i >> 24); b1 = (unsigned char) (i >> 16); b2 = (unsigned char) (i >> 8); b3 = (unsigned char) i; }
		operator int() const 				{ return (int) ((b0 << 24) | (b1 << 16) | (b2 << 8) | b3); }
		
	private:
		unsigned char	b0;
		unsigned char	b1;
		unsigned char	b2;
		unsigned char	b3;
	};
	

	struct UInt
	{
	public:
		void operator=(unsigned int u)		{ b0 = (unsigned char) (u >> 24); b1 = (unsigned char) (u >> 16); b2 = (unsigned char) (u >> 8); b3 = (unsigned char) u; }
		operator unsigned int() const		{ return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3; }
		
	private:
		unsigned char	b0;
		unsigned char	b1;
		unsigned char	b2;
		unsigned char	b3;
	};

	struct Long
	{
	public:
		void operator=(long long u)		{
											b0 = (unsigned char) (u >> 56);
											b1 = (unsigned char) (u >> 48);
											b2 = (unsigned char) (u >> 40);
											b3 = (unsigned char) (u >> 32);
											b4 = (unsigned char) (u >> 24);
											b5 = (unsigned char) (u >> 16);
											b6 = (unsigned char) (u >> 8);
											b7 = (unsigned char) u;
										}
		operator long long() const		{
											return ((long long) b0 << 56) |
													((long long) b1 << 48) |
													((long long) b2 << 40) |
													((long long) b3 << 32) |
													((long long) b4 << 24) |
													((long long) b5 << 16) |
													((long long) b6 << 8) |
													((long long) b7);
										}
		
	private:
		unsigned char	b0;
		unsigned char	b1;
		unsigned char	b2;
		unsigned char	b3;
		unsigned char	b4;
		unsigned char	b5;
		unsigned char	b6;
		unsigned char	b7;
	};
	
	struct ULong
	{
	public:
		void operator=(unsigned long long u)	{
													b0 = (unsigned char) (u >> 56);
													b1 = (unsigned char) (u >> 48);
													b2 = (unsigned char) (u >> 40);
													b3 = (unsigned char) (u >> 32);
													b4 = (unsigned char) (u >> 24);
													b5 = (unsigned char) (u >> 16);
													b6 = (unsigned char) (u >> 8);
													b7 = (unsigned char) u;
												}
		operator unsigned long long() const		{
													return ((unsigned long long) b0 << 56) |
														 	((unsigned long long) b1 << 48) |
														 	((unsigned long long) b2 << 40) |
														 	((unsigned long long) b3 << 32) |
														 	((unsigned long long) b4 << 24) |
														 	((unsigned long long) b5 << 16) |
														 	((unsigned long long) b6 << 8) |
															((unsigned long long) b7);
												}
		
	private:
		unsigned char	b0;
		unsigned char	b1;
		unsigned char	b2;
		unsigned char	b3;
		unsigned char	b4;
		unsigned char	b5;
		unsigned char	b6;
		unsigned char	b7;
	};
	
//============================================================================
} // namespace migme
//============================================================================
