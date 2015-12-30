//============================================================================

#pragma once
#include "FusionDataTypes.h"

//============================================================================

namespace migme
{
	namespace FusionEnum
	{
//============================================================================

		#define ENUM_DEFINITION_FILE "FusionEnum_ChatType.enumdef"
		#include "Enums/ProcessEnumDefinition.h"
		#undef ENUM_DEFINITION_FILE

		#define ENUM_DEFINITION_FILE "FusionEnum_ClientType.enumdef"
		#include "Enums/ProcessEnumDefinition.h"
		#undef ENUM_DEFINITION_FILE

		#define ENUM_DEFINITION_FILE "FusionEnum_ContentType.enumdef"
		#include "Enums/ProcessEnumDefinition.h"
		#undef ENUM_DEFINITION_FILE
				
		#define ENUM_DEFINITION_FILE "FusionEnum_EmoteContentType.enumdef"
		#include "Enums/ProcessEnumDefinition.h"
		#undef ENUM_DEFINITION_FILE
				
		#define ENUM_DEFINITION_FILE "FusionEnum_IMType.enumdef"
		#include "Enums/ProcessEnumDefinition.h"
		#undef ENUM_DEFINITION_FILE
			
		#define ENUM_DEFINITION_FILE "FusionEnum_MessageType.enumdef"
		#include "Enums/ProcessEnumDefinition.h"
		#undef ENUM_DEFINITION_FILE
				
		#define ENUM_DEFINITION_FILE "FusionEnum_PacketType.enumdef"
		#include "Enums/ProcessEnumDefinition.h"
		#undef ENUM_DEFINITION_FILE

		#define ENUM_DEFINITION_FILE "FusionEnum_PresenceType.enumdef"
		#include "Enums/ProcessEnumDefinition.h"
		#undef ENUM_DEFINITION_FILE

		#define ENUM_DEFINITION_FILE "FusionEnum_UserType.enumdef"
		#include "Enums/ProcessEnumDefinition.h"
		#undef ENUM_DEFINITION_FILE
			
//============================================================================
	} // namespace FusionEnums
} // namespace migme
//============================================================================
