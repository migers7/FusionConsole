//============================================================================

#pragma once
#include <stdlib.h>
#include <string.h>

//============================================================================

namespace migme
{
    //============================================================================
    
    class Sha1
    {
    public:
        Sha1()	{ }
        inline Sha1(const char* data)							{ Set(data); 			}
        inline Sha1(const void* data, size_t length)			{ Set(data, length);	}
        
        inline void Set(const char* data)					{ CalculateDigest(data, strlen(data)); 			}
        inline void Set(const void* data, size_t length)	{ CalculateDigest((const char*) data, length); }
        
        void Reset();
        void ProcessBlock(const unsigned* data);
        
        // Converts the result to the correct endian representation in Value
        void Rectify();
        
        static size_t GetCount()					{ return 20;				}
        unsigned char operator[](size_t n) const	{ return value[n];			}
        
        bool operator==(const Sha1& a) const		{ return memcmp(this, &a, sizeof(Sha1)) == 0; }
        bool operator!=(const Sha1& a) const		{ return memcmp(this, &a, sizeof(Sha1)) != 0; }
        bool operator<(const Sha1& a) const			{ return memcmp(this, &a, sizeof(Sha1)) <  0; }
        
    private:
        void CalculateDigest(const char *data, size_t length);
        
        union
        {
            unsigned char value[20];
            unsigned	  iValue[5];
        };
    };
    
    //============================================================================
} // namespace migme
//============================================================================
