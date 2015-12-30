//============================================================================

#include "FusionField.h"
#include <assert.h>

//============================================================================

using namespace migme;

//============================================================================

std::string migme::EMPTY_STRING;

//============================================================================

unsigned char FusionField::AsByte() const
{
	assert(dataSize == 1);
	return *(const migme::Byte*) GetData();
}

short FusionField::AsShort() const
{
	assert(dataSize == 2);
	return *(const migme::Short*) GetData();
}

unsigned short FusionField::AsUShort() const
{
	assert(dataSize == 2);
	return *(const migme::UShort*) GetData();
}

int FusionField::AsInt() const
{
	assert(dataSize == 4);
	return *(const migme::Int*) GetData();
}

unsigned int FusionField::AsUInt() const
{
	assert(dataSize == 4);
	return *(const migme::UInt*) GetData();
}

long long FusionField::AsLong() const
{
	assert(dataSize == 8);
	return *(const migme::Long*) GetData();
}

unsigned long long FusionField::AsULong() const
{
	assert(dataSize == 8);
	return *(const migme::ULong*) GetData();
}

std::string FusionField::AsString() const
{
	return std::string((const char*) GetData(), dataSize);
}

std::vector<unsigned char> FusionField::AsByteArray() const
{
	const unsigned char* p = (const unsigned char*) GetData();
	return std::vector<unsigned char>(p, p+dataSize);
}

std::vector<std::string> FusionField::AsStringArray(char separator) const
{
	std::vector<std::string> values;

	const unsigned char* pStart = (const unsigned char*) GetData();
	const unsigned char* pEnd = pStart + dataSize;
	
	
	const unsigned char* p = pStart;
	while(p < pEnd)
	{
		if(*p == separator)
		{
			std::string entry(pStart, p);
			values.push_back(entry);
			pStart = p+1;
		}
		++p;
	}
	if(p != pStart)
	{
		std::string entry(pStart, p);
		values.push_back(entry);
	}
	
	return values;
}

//============================================================================

FusionField* FusionField::CreateFieldWithByte(int fieldId, unsigned char value)
{
	FusionField* field = new(1) FusionField(fieldId, 1);
	*(migme::Byte*) field->GetData() = value;
	return field;
}

FusionField* FusionField::CreateFieldWithUShort(int fieldId, unsigned short value)
{
	FusionField* field = new(2) FusionField(fieldId, 2);
	*(migme::UShort*) field->GetData() = value;
	return field;
}

FusionField* FusionField::CreateFieldWithInt(int fieldId, int value)
{
	FusionField* field = new(4) FusionField(fieldId, 4);
	*(migme::Int*) field->GetData() = value;
	return field;
}

FusionField* FusionField::CreateFieldWithUInt(int fieldId, unsigned int value)
{
	FusionField* field = new(4) FusionField(fieldId, 4);
	*(migme::UInt*) field->GetData() = value;
	return field;
}

FusionField* FusionField::CreateFieldWithLong(int fieldId, long long value)
{
	FusionField* field = new(8) FusionField(fieldId, 8);
	*(migme::Long*) field->GetData() = value;
	return field;
}

FusionField* FusionField::CreateFieldWithULong(int fieldId, unsigned long long value)
{
	FusionField* field = new(8) FusionField(fieldId, 8);
	*(migme::ULong*) field->GetData() = value;
	return field;
}

FusionField* FusionField::CreateFieldWithString(int fieldId, const std::string& value)
{
	FusionField* field = new(value.size()) FusionField(fieldId, (unsigned) value.size());
	memcpy(field->GetData(), value.c_str(), value.size());
	return field;
}

FusionField* FusionField::CreateFieldWithByteArray(int fieldId, const std::vector<unsigned char>& value)
{
	FusionField* field = new(value.size()) FusionField(fieldId, (unsigned) value.size());
	if(!value.empty())
	{
		memcpy(field->GetData(), &value.front(), value.size());
	}
	return field;
}

FusionField* FusionField::CreateFieldWithStringArray(int fieldId, const std::vector<std::string>& value, char separator)
{
	if(value.size() == 0) return new(0) FusionField(fieldId, 0);
	
	size_t numberOfBytes = value.size()-1;	// Number of '\0' separators
	for(const std::string& s : value) numberOfBytes += s.size();
	
	FusionField* field = new(numberOfBytes) FusionField(fieldId, (unsigned)numberOfBytes);
	char* p = (char*) field->GetData();
	
	for(size_t i = 0; i < value.size(); ++i)
	{
		if(i != 0) *p++ = separator;
		memcpy(p, value[i].c_str(), value[i].size());
		p += value[i].size();
	}
	
	return field;
}

//============================================================================
