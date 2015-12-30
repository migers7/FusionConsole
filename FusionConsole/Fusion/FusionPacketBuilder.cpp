//============================================================================

#include "FusionPacketBuilder.h"
#include "FusionField.h"
#include <assert.h>

//============================================================================

using namespace migme;

//============================================================================

FusionPacketBuilder::FusionPacketBuilder(FusionEnum::PacketType aType)
: type(aType)
{
}

FusionPacketBuilder::~FusionPacketBuilder()
{
	for(FusionField* field : fields) delete field;
}

//============================================================================

FusionPacket* FusionPacketBuilder::CreatePacket() const
{
	FusionPacket* packet = new(GetContentSize()) FusionPacket;
	WriteToFusionPacket(packet);
	return packet;
}

std::vector<unsigned char> FusionPacketBuilder::CreateData() const
{
	std::vector<unsigned char> data;
	data.resize(GetContentSize());

	FusionField* p = (FusionField*) data.data();

	for(const FusionField* field : fields)
	{
		p->fieldId = field->fieldId;
		p->dataSize = field->dataSize;
		memcpy(p->GetData(), field->GetData(), field->dataSize);
		
		p = p->GetNextField();
	}

	return data;
}

//============================================================================

size_t FusionPacketBuilder::GetContentSize() const
{
	size_t size = 0;
	for(FusionField* field : fields)
	{
		size += field->GetFieldSize();
	}
	return size;
}

//============================================================================

void FusionPacketBuilder::WriteToFusionPacket(FusionPacket* buffer) const
{
	buffer->startOfPacket = 2;
	buffer->type = (unsigned short) type;
	buffer->transactionId = 0;
	assert(buffer->contentSize == GetContentSize());
	
	FusionField* p = (FusionField*) (buffer + 1);
	for(const FusionField* field : fields)
	{
		p->fieldId = field->fieldId;
		p->dataSize = field->dataSize;
		memcpy(p->GetData(), field->GetData(), field->dataSize);
		
		p = p->GetNextField();
	}
}

//============================================================================

unsigned char FusionPacketBuilder::GetByte(int fieldId) const
{
	return GetFieldById(fieldId)->AsByte();
}

void FusionPacketBuilder::SetByte(int fieldId, unsigned char value)
{
	RemoveFieldById(fieldId);
	fields.push_back(FusionField::CreateFieldWithByte(fieldId, value));
}


unsigned short FusionPacketBuilder::GetUShort(int fieldId) const
{
	return GetFieldById(fieldId)->AsUShort();
}

void FusionPacketBuilder::SetUShort(int fieldId, unsigned short value)
{
	RemoveFieldById(fieldId);
	fields.push_back(FusionField::CreateFieldWithUShort(fieldId, value));
}

unsigned int FusionPacketBuilder::GetUInt(int fieldId) const
{
	return GetFieldById(fieldId)->AsUInt();
}

void FusionPacketBuilder::SetUInt(int fieldId, unsigned int value)
{
	RemoveFieldById(fieldId);
	fields.push_back(FusionField::CreateFieldWithUInt(fieldId, value));
}

long long FusionPacketBuilder::GetLong(int fieldId) const
{
	return GetFieldById(fieldId)->AsLong();
}

void FusionPacketBuilder::SetLong(int fieldId, long long value)
{
	RemoveFieldById(fieldId);
	fields.push_back(FusionField::CreateFieldWithLong(fieldId, value));
}

unsigned long long FusionPacketBuilder::GetULong(int fieldId) const
{
	return GetFieldById(fieldId)->AsULong();
}

void FusionPacketBuilder::SetULong(int fieldId, unsigned long long value)
{
	RemoveFieldById(fieldId);
	fields.push_back(FusionField::CreateFieldWithULong(fieldId, value));
}

std::string FusionPacketBuilder::GetString(int fieldId) const
{
	return GetFieldById(fieldId)->AsString();
}

void FusionPacketBuilder::SetString(int fieldId, const std::string& value)
{
	RemoveFieldById(fieldId);
	fields.push_back(FusionField::CreateFieldWithString(fieldId, value));
}

std::vector<unsigned char> FusionPacketBuilder::GetByteArray(int fieldId) const
{
	return GetFieldById(fieldId)->AsByteArray();
}

void FusionPacketBuilder::SetByteArray(int fieldId, const std::vector<unsigned char>& value)
{
	RemoveFieldById(fieldId);
	fields.push_back(FusionField::CreateFieldWithByteArray(fieldId, value));
}

std::vector<std::string> FusionPacketBuilder::GetStringArray(int fieldId, char separator) const
{
	return GetFieldById(fieldId)->AsStringArray(separator);
}

void FusionPacketBuilder::SetStringArray(int fieldId, const std::vector<std::string>& value, char separator)
{
	RemoveFieldById(fieldId);
	fields.push_back(FusionField::CreateFieldWithStringArray(fieldId, value, separator));
}

//============================================================================

void FusionPacketBuilder::RemoveFieldById(int fieldId)
{
	for(std::vector<FusionField*>::iterator it = fields.begin(); it != fields.end(); ++it)
	{
		if((*it)->fieldId == fieldId)
		{
			fields.erase(it);
			return;
		}
	}
}

const FusionField* FusionPacketBuilder::GetFieldById(int fieldId) const
{
	for(FusionField* field : fields)
	{
		if(field->fieldId == fieldId) return field;
	}
	return nullptr;
}

//============================================================================
