//============================================================================

// This file autogenerates classes from the .def files
		
//	class FusionPacket_Login : private FusionPacketIO
//	{
//	public:
//		FusionPacket_Login(const FusionPacket& packet) : FusionPacketIO(packet), version(*(FusionPacketIO*) this) { }
//		
//		FusionPacketIO_UShortProxy<1>	protocolVersion;
//		FusionPacketIO_ByteProxy<2>		clientType;
//	};
//	
//	
//	class FusionPacketBuilder_Login : public FusionPacketBuilder
//	{
//	public:
//		FusionPacketBuilder_Login() : FusionPacketBuilder(FusionPacketType::LOGIN), version(*(FusionPacketIO*) this) { }
//		
//		FusionPacketIO_UShortProxy<1>	protocolVersion;
//		FusionPacketIO_ByteProxy<2>		clientType;
//	};


#define BeginPacket(className, packetType)						\
	class FusionPacket_##className : private FusionPacketIO		\
	{															\
	public:														\
		FusionPacket_##className(const FusionPacket& packet) : FusionPacketIO(packet)

#define ByteField(fieldId, variableName)
#define UShortField(fieldId, variableName)
#define UIntField(fieldId, variableName)
#define ULongField(fieldId, variableName)
#define StringField(fieldId, variableName)
#define ByteArrayField(fieldId, variableName)
#define StringArrayField(fieldId, separator, variableName)
#define EnumField(fieldId, enumType, variableName)
#define EndPacket(className)

	#include PACKET_DEFINITION_FILE

#undef BeginPacket
#undef ByteField
#undef UShortField
#undef UIntField
#undef ULongField
#undef StringField
#undef ByteArrayField
#undef StringArrayField
#undef EnumField
#undef EndPacket


#define BeginPacket(className, packetType)
#define ByteField(fieldId, variableName)	\
			, variableName(*(FusionPacketIO*) this)
#define UShortField(fieldId, variableName)	\
			, variableName(*(FusionPacketIO*) this)
#define UIntField(fieldId, variableName)	\
			, variableName(*(FusionPacketIO*) this)
#define ULongField(fieldId, variableName)	\
			, variableName(*(FusionPacketIO*) this)
#define StringField(fieldId, variableName)	\
			, variableName(*(FusionPacketIO*) this)
#define ByteArrayField(fieldId, variableName)	\
			, variableName(*(FusionPacketIO*) this)
#define StringArrayField(fieldId, separator, variableName)	\
			, variableName(*(FusionPacketIO*) this)
#define EnumField(fieldId, enumType, variableName)	\
			, variableName(*(FusionPacketIO*) this)
#define EndPacket(className)

	#include PACKET_DEFINITION_FILE

#undef BeginPacket
#undef ByteField
#undef UShortField
#undef UIntField
#undef ULongField
#undef StringField
#undef ByteArrayField
#undef StringArrayField
#undef EnumField
#undef EndPacket


#define BeginPacket(className, packetType) 	\
			{ }								\

#define ByteField(fieldId, variableName)					FusionPacketIO_ByteProxy<fieldId>	variableName;
#define UShortField(fieldId, variableName)					FusionPacketIO_UShortProxy<fieldId>	variableName;
#define UIntField(fieldId, variableName)					FusionPacketIO_UIntProxy<fieldId>	variableName;
#define ULongField(fieldId, variableName)					FusionPacketIO_ULongProxy<fieldId>	variableName;
#define StringField(fieldId, variableName)					FusionPacketIO_StringProxy<fieldId>	variableName;
#define ByteArrayField(fieldId, variableName)				FusionPacketIO_ByteArrayProxy<fieldId>	variableName;
#define StringArrayField(fieldId, separator, variableName)	FusionPacketIO_StringArrayProxy<fieldId, separator>	variableName;
#define EnumField(fieldId, enumType, variableName)			FusionPacketIO_EnumProxy<fieldId, FusionEnum::enumType, FusionEnum::enumType##StorageType> variableName;
#define EndPacket(className)				\
	};										\

	#include PACKET_DEFINITION_FILE

#undef BeginPacket
#undef ByteField
#undef UShortField
#undef UIntField
#undef ULongField
#undef StringField
#undef ByteArrayField
#undef StringArrayField
#undef EnumField
#undef EndPacket

#define BeginPacket(className, packetType)									\
	class FusionPacketBuilder_##className : public FusionPacketBuilder		\
	{																		\
	public:																	\
		FusionPacketBuilder_##className() : FusionPacketBuilder(FusionEnum::PacketType::packetType)
	
#define ByteField(fieldId, variableName)
#define UShortField(fieldId, variableName)
#define UIntField(fieldId, variableName)
#define ULongField(fieldId, variableName)
#define StringField(fieldId, variableName)
#define ByteArrayField(fieldId, variableName)
#define StringArrayField(fieldId, separator, variableName)
#define EnumField(fieldId, enumType, variableName)
#define EndPacket(className)
	
	#include PACKET_DEFINITION_FILE
	
#undef BeginPacket
#undef ByteField
#undef UShortField
#undef UIntField
#undef ULongField
#undef StringField
#undef ByteArrayField
#undef StringArrayField
#undef EnumField
#undef EndPacket
	
	
#define BeginPacket(className, packetType)
#define ByteField(fieldId, variableName)	\
	, variableName(*(FusionPacketIO*) this)
#define UShortField(fieldId, variableName)	\
	, variableName(*(FusionPacketIO*) this)
#define UIntField(fieldId, variableName)	\
	, variableName(*(FusionPacketIO*) this)
#define ULongField(fieldId, variableName)	\
	, variableName(*(FusionPacketIO*) this)
#define StringField(fieldId, variableName)	\
	, variableName(*(FusionPacketIO*) this)
#define ByteArrayField(fieldId, variableName)	\
	, variableName(*(FusionPacketIO*) this)
#define StringArrayField(fieldId, separator, variableName)	\
	, variableName(*(FusionPacketIO*) this)
#define EnumField(fieldId, enumType, variableName)	\
	, variableName(*(FusionPacketIO*) this)
#define EndPacket(className)
	
	#include PACKET_DEFINITION_FILE
	
#undef BeginPacket
#undef ByteField
#undef UShortField
#undef UIntField
#undef ULongField
#undef StringField
#undef ByteArrayField
#undef StringArrayField
#undef EnumField
#undef EndPacket
	
	
#define BeginPacket(className, packetType) 	\
			{ }								\

#define ByteField(fieldId, variableName)					FusionPacketIO_ByteProxy<fieldId>	variableName;
#define UShortField(fieldId, variableName)					FusionPacketIO_UShortProxy<fieldId>	variableName;
#define UIntField(fieldId, variableName)					FusionPacketIO_UIntProxy<fieldId>	variableName;
#define ULongField(fieldId, variableName)					FusionPacketIO_ULongProxy<fieldId>	variableName;
#define StringField(fieldId, variableName)					FusionPacketIO_StringProxy<fieldId>	variableName;
#define ByteArrayField(fieldId, variableName)				FusionPacketIO_ByteArrayProxy<fieldId>	variableName;
#define StringArrayField(fieldId, separator, variableName)	FusionPacketIO_StringArrayProxy<fieldId, separator>	variableName;
#define EnumField(fieldId, enumType, variableName)			FusionPacketIO_EnumProxy<fieldId, FusionEnum::enumType, FusionEnum::enumType##StorageType> variableName;
#define EndPacket(className)				\
	};										\

	#include PACKET_DEFINITION_FILE
	
#undef BeginPacket
#undef ByteField
#undef UShortField
#undef UIntField
#undef ULongField
#undef StringField
#undef ByteArrayField
#undef StringArrayField
#undef EnumField
#undef EndPacket
	
//============================================================================
