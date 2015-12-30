//============================================================================

#pragma once
#include "FusionPacketBuilder.h"
#include "FusionEnums.h"
#include "FusionPacketIO.h"

//============================================================================

namespace migme
{
//============================================================================

	#define PACKET_DEFINITION_FILE "FusionPacket_AccountBalance.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
	
	#define PACKET_DEFINITION_FILE "FusionPacket_Avatar.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_Chat.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_ChatListVersion.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_Contact.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_ContactListVersion.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_Emoticon.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_EmoticonHotkeys.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_EndMessages.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_EndStickerPack.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_Error.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_GetChats.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_GetContacts.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_GetContactsComplete.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_GetGroupChatParticipants.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_GetEmoticon.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
	
	#define PACKET_DEFINITION_FILE "FusionPacket_GetEmoticonsComplete.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
	
	#define PACKET_DEFINITION_FILE "FusionPacket_GetGift.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_GetMessages.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_GetStickerPackList.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_GetStickerPack.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_GiftHotkeys.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_Group.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
	
	#define PACKET_DEFINITION_FILE "FusionPacket_GroupChat.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_GroupChatInvite.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_GroupChatParticipants.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_HaveLatestContactList.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
	
	#define PACKET_DEFINITION_FILE "FusionPacket_JoinChatRoom.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
	
	#define PACKET_DEFINITION_FILE "FusionPacket_LatestMessagesDigest.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_LeaveChatRoom.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_LeaveGroupChat.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
	
	#define PACKET_DEFINITION_FILE "FusionPacket_Login.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_LoginChallenge.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_LoginOk.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_LoginResponse.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_Message.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_Ping.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_Presence.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_SetPresence.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
	#define PACKET_DEFINITION_FILE "FusionPacket_SetStatusMessage.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_StatusMessage.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_StickerPack.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE

	#define PACKET_DEFINITION_FILE "FusionPacket_StickerPackList.packetdef"
	#include "Packets/ProcessPacketDefintion.h"
	#undef PACKET_DEFINITION_FILE
		
//============================================================================
} // namespace migme
//============================================================================
