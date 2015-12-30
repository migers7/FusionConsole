//============================================================================

#pragma once
#include <stdlib.h>

//============================================================================

namespace migme
{
    //============================================================================
    
    class DataBuffer
    {
    public:
        DataBuffer() { headElement = nullptr; tailElement = &headElement; }
        ~DataBuffer();
        
        void WriteBlock(const void* data, size_t size);
        
        bool HasData() const 	{ return headElement != nullptr; }
        
        size_t GetCount();
        bool HasCount(size_t count);
        void ReadBlock(void* data, size_t size);
        void PeekBlock(void* data, size_t size);
        
        void Reset();
        
    private:
        struct DataElement
        {
            DataElement* 	next;
            size_t			length;
            size_t			currentOffset;
            uint8_t			data[1];
            
            size_t GetRemainingSize() const { return length - currentOffset; }
            
            DataElement(const void* data, size_t size);
            
            static void* operator new(size_t size, size_t dataSize, bool)	{ return ::operator new(size + dataSize); }
            static void operator delete(void* p, size_t dataSize, bool)		{ ::operator delete(p); }
            static void operator delete(void* p) 							{ ::operator delete(p); }
        };
        
        DataElement*	headElement;
        DataElement**	tailElement;
    };
    
    //============================================================================
}
//============================================================================
