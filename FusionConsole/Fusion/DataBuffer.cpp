//============================================================================

#include "DataBuffer.h"
#include <algorithm>
#include <string.h>
#include <stdlib.h>

//============================================================================

using namespace migme;

//============================================================================

DataBuffer::DataElement::DataElement(const void* aData, size_t size)
{
    next = nullptr;
    length = size;
    currentOffset = 0;
    memcpy(data, aData, size);
}

//============================================================================

DataBuffer::~DataBuffer()
{
    Reset();
}

void DataBuffer::Reset()
{
    DataElement* p = headElement;
    while(p)
    {
        DataElement* pNext = p->next;
        delete p;
        p = pNext;
    }
    headElement = nullptr;
    tailElement = &headElement;
}

void DataBuffer::WriteBlock(const void* data, size_t size)
{
    DataElement* p = new(size, true) DataElement(data, size);
    *tailElement = p;
    tailElement = &p->next;
}

size_t DataBuffer::GetCount()
{
    size_t count = 0;
    DataElement* p = headElement;
    while(p)
    {
        count += p->GetRemainingSize();
        p = p->next;
    }
    return count;
}

bool DataBuffer::HasCount(size_t count)
{
    DataElement* p = headElement;
    while(p)
    {
        size_t remainingCount = p->GetRemainingSize();
        if(remainingCount >= count) return true;
        count -= remainingCount;
        p = p->next;
    }
    return false;
}

void DataBuffer::ReadBlock(void* data, size_t size)
{
    uint8_t* d = (uint8_t*) data;
    while(size > 0)
    {
        size_t sizeToCopy = std::min(size, headElement->GetRemainingSize());
        memcpy(d, headElement->data + headElement->currentOffset, sizeToCopy);
        
        d += sizeToCopy;
        size -= sizeToCopy;
        headElement->currentOffset += sizeToCopy;
        if(headElement->GetRemainingSize() == 0)
        {
            DataElement* toDelete = headElement;
            headElement = headElement->next;
            if(headElement == nullptr) tailElement = &headElement;
            delete toDelete;
        }
    }
}

void DataBuffer::PeekBlock(void* data, size_t size)
{
    uint8_t* d = (uint8_t*) data;
    const DataElement* p = headElement;
    while(size > 0)
    {
        size_t sizeToCopy = std::min(size, p->GetRemainingSize());
        memcpy(d, p->data + p->currentOffset, sizeToCopy);
        d += sizeToCopy;
        size -= sizeToCopy;
        p = p->next;
    }
}

//============================================================================
