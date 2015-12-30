//============================================================================

#include "Sha1.h"

//============================================================================

using namespace migme;

//============================================================================

static inline unsigned RotateLeft(unsigned a, int s)  { return (a << s) | (a >> (32-s));  }
static inline unsigned ByteSwap(unsigned a)
{
    unsigned char b0 = a & 0xff;
    unsigned char b1 = (a >> 8) & 0xff;
    unsigned char b2 = (a >> 16) & 0xff;
    unsigned char b3 = (a >> 24) & 0xff;
    
    return b3 | (b2 << 8) | (b1 << 16) | (b0 << 24);
}

//============================================================================

void Sha1::Reset()
{
    iValue[0] = 0x67452301;
    iValue[1] = 0xEFCDAB89;
    iValue[2] = 0x98BADCFE;
    iValue[3] = 0x10325476;
    iValue[4] = 0xC3D2E1F0;
}

void Sha1::Rectify()
{
    iValue[0] = ByteSwap(iValue[0]);
    iValue[1] = ByteSwap(iValue[1]);
    iValue[2] = ByteSwap(iValue[2]);
    iValue[3] = ByteSwap(iValue[3]);
    iValue[4] = ByteSwap(iValue[4]);
}

//============================================================================

void Sha1::ProcessBlock(const unsigned *data)
{
    int t;
    unsigned w[80];
    for(t = 0; t < 16; t++) w[t] = ByteSwap(data[t]);
    for(; t < 80; t++) w[t] = RotateLeft(w[t-3] ^ w[t-8] ^ w[t-14] ^ w[t-16], 1);
    
    unsigned a = iValue[0];
    unsigned b = iValue[1];
    unsigned c = iValue[2];
    unsigned d = iValue[3];
    unsigned e = iValue[4];
    
    for(t = 0; t < 20; t++)
    {
        unsigned temp = RotateLeft(a, 5) + ((b & c) | (~b & d)) + e + w[t] + 0x5A827999;
        e = d;
        d = c;
        c = RotateLeft(b, 30);
        b = a;
        a = temp;
    }
    
    for(;t < 40; t++)
    {
        unsigned temp = RotateLeft(a, 5) + (b ^ c ^ d) + e + w[t] + 0x6ED9EBA1;
        e = d;
        d = c;
        c = RotateLeft(b, 30);
        b = a;
        a = temp;
    }
    
    for(;t < 60; t++)
    {
        unsigned temp = RotateLeft(a, 5) + ((b & c) | (b & d) | (c & d)) + e + w[t] + 0x8F1BBCDC;
        e = d;
        d = c;
        c = RotateLeft(b, 30);
        b = a;
        a = temp;
    }
    
    for(;t < 80; t++)
    {
        unsigned temp = RotateLeft(a, 5) + (b ^ c ^ d) + e + w[t] + 0xCA62C1D6;
        e = d;
        d = c;
        c = RotateLeft(b, 30);
        b = a;
        a = temp;
    }
    
    iValue[0] += a;
    iValue[1] += b;
    iValue[2] += c;
    iValue[3] += d;
    iValue[4] += e;
}

//============================================================================

void Sha1::CalculateDigest(const char *data, size_t length)
{
    union
    {
        char		cBuffer[64];
        unsigned	iBuffer[16];
    };
    
    size_t hashSize	= (length+64+8+1) & ~63;
    size_t blockLength	= length & ~63;
    
    Reset();
    
    for(size_t i = 0; i < hashSize; i += 64)
    {
        if(i < blockLength)
        {
            ProcessBlock(reinterpret_cast<const unsigned*>(data+i));
        }
        else
        {
            unsigned *const x = iBuffer;
            if(i > length)
            {
                memset(cBuffer, 0, 56);
            }
            else
            {
                size_t remainder = length-i;
                
                memcpy(cBuffer, data+i, remainder);
                cBuffer[remainder] = '\x80';
                memset(cBuffer+remainder+1, 0, 63-remainder);
                
                if(remainder >= 56) goto DoBlock;
            }
            
            x[14] = ByteSwap((unsigned) (length >> 29));
            x[15] = ByteSwap(unsigned (length << 3));
            
        DoBlock:
            ProcessBlock(x);
        }
    }
    
    Rectify();
}

//============================================================================
