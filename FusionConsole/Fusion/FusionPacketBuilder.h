//============================================================================

#pragma once
#include "FusionEnums.h"
#include "FusionPacketIO.h"
#include <vector>

//============================================================================

namespace migme
{
//============================================================================

	class FusionPacketBuilder : public IFusionPacketIO
	{
	public:
		FusionPacketBuilder() { }
		FusionPacketBuilder(const FusionPacket& p);
		FusionPacketBuilder(FusionEnum::PacketType type);
		~FusionPacketBuilder();
				
		FusionPacket* CreatePacket() const;
		std::vector<unsigned char> CreateData() const;
		
		virtual bool 				Exists(int fieldId) const 					{ return GetFieldById(fieldId) != nullptr; }
		
		virtual unsigned char		GetByte(int fieldId) const;
		virtual void				SetByte(int fieldId, unsigned char value);

		virtual unsigned short 		GetUShort(int fieldId) const;
		virtual void				SetUShort(int fieldId, unsigned short value);
		
		virtual unsigned int		GetUInt(int fieldId) const;
		virtual void				SetUInt(int fieldId, unsigned int value);
		
		virtual long long			GetLong(int fieldId) const;
		virtual void				SetLong(int fieldId, long long value);
		
		virtual unsigned long long	GetULong(int fieldId) const;
		virtual void				SetULong(int fieldId, unsigned long long value);
		
		virtual std::string			GetString(int fieldId) const;
		virtual void				SetString(int fieldId, const std::string& value);

		virtual std::vector<unsigned char> 	GetByteArray(int fieldId) const;
		virtual void						SetByteArray(int fieldId, const std::vector<unsigned char>& value);
		
		virtual std::vector<std::string> 	GetStringArray(int fieldId, char separator) const;
		virtual void						SetStringArray(int fieldId, const std::vector<std::string>& value, char separator);
		
	private:
		FusionEnum::PacketType 	type;
		
		std::vector<FusionField*> fields;

		size_t GetContentSize() const;
		void WriteToFusionPacket(FusionPacket* buffer) const;
		
		void RemoveFieldById(int fieldId);
		const FusionField* GetFieldById(int fieldId) const;
	};

//============================================================================
} // namespace migme
//============================================================================
