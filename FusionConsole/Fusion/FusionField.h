//============================================================================

#pragma once
#include "FusionDataTypes.h"
#include <string>
#include <vector>

//============================================================================

namespace migme
{
//============================================================================
	
	extern std::string EMPTY_STRING;

	struct FusionField
	{
		UShort	fieldId;
		UInt	dataSize;
		
		size_t GetFieldSize()			{ return sizeof(FusionField) + dataSize; }
		void* GetData() 				{ return this+1; }
		const void* GetData() const		{ return this+1; }
		
		unsigned char		AsByte() const;
		short				AsShort() const;
		unsigned short		AsUShort() const;
		int					AsInt() const;
		unsigned int		AsUInt() const;
		long long			AsLong() const;
		unsigned long long	AsULong() const;
		std::string			AsString() const;
		std::vector<unsigned char> AsByteArray() const;
		std::vector<std::string> AsStringArray(char separator) const;
		
		FusionField* GetNextField()		{ return (FusionField*) ((char*) (this+1) + dataSize); }
		
		static FusionField* CreateFieldWithByte(int fieldId, unsigned char value);
		static FusionField* CreateFieldWithUShort(int fieldId, unsigned short value);
		static FusionField* CreateFieldWithUInt(int fieldId, unsigned int value);
		static FusionField* CreateFieldWithInt(int fieldId, int value);
		static FusionField* CreateFieldWithLong(int fieldId, long long value);
		static FusionField* CreateFieldWithULong(int fieldId, unsigned long long value);
		static FusionField* CreateFieldWithString(int fieldId, const std::string& value);
		static FusionField* CreateFieldWithByteArray(int fieldId, const std::vector<unsigned char>& value);
		static FusionField* CreateFieldWithStringArray(int fieldId, const std::vector<std::string>& value, char separator);
		
		void* operator new(size_t size, size_t dataSize) { return ::operator new(size+dataSize); }
		
	private:
		FusionField(unsigned short aFieldId, unsigned aDataSize) { fieldId = aFieldId; dataSize = aDataSize; }
	};
	
//============================================================================
} // namespace migme
//============================================================================
