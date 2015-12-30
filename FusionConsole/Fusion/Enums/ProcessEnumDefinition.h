//============================================================================

// This file autogenerates classes from the .def files

//  enum class PacketType : UShort
//  {
//		ERROR = 0,
//  }


#define BeginEnum(className, storageType)		\
	typedef storageType className##StorageType;	\
	enum class className : storageType::NativeType	\
	{
#define Value(V, N) N = V,
#define EndEnum(className) };

	#include ENUM_DEFINITION_FILE

#undef BeginEnum
#undef Value
#undef EndEnum
	
//============================================================================
