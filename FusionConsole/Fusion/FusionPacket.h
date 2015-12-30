//============================================================================

#pragma once
#include "FusionEnums.h"

//============================================================================

namespace migme
{
//============================================================================
	
	class FusionField;
	
//============================================================================
	
	struct FusionPacket
	{
		Byte		startOfPacket;
		UShort		type;
		UShort		transactionId;
		UInt		contentSize;
		
		bool HasValidHeader() const 				{ return startOfPacket == 2; 		}
		FusionEnum::PacketType GetType() const		{ return (FusionEnum::PacketType) (unsigned short) type; 	}
		unsigned short GetTransactionId() const		{ return transactionId; 			}
		unsigned GetContentSize() const				{ return contentSize;	 			}
		size_t GetPacketSize() const				{ return sizeof(FusionPacket) + contentSize; }
		
		size_t 				GetNumberOfFields() const;
		const FusionField* 	GetFieldByIndex(size_t i) const;
		bool 				HasFieldId(int fieldId) const							{ return GetFieldById(fieldId) != nullptr; }
		const FusionField* 	GetFieldById(int fieldId) const;
		
		static void* operator new(size_t size, size_t contentSize)		{
			FusionPacket* p = (FusionPacket*) ::operator new(size + contentSize);
			p->contentSize = (unsigned int) contentSize;
			return p;
		}
        
        std::string GetTypeString() const
        {
            switch (GetType()) {
                case FusionEnum::PacketType::ERROR:
                    return "ERROR";
                case FusionEnum::PacketType::OK:
                    return "OK";
                case FusionEnum::PacketType::PING:
                    return "PING";
                case FusionEnum::PacketType::PONG:
                    return "PONG";
                case FusionEnum::PacketType::ALERT:
                    return "ALERT";
                case FusionEnum::PacketType::HELP_TEXT:
                    return "HELP_TEXT";
                case FusionEnum::PacketType::GET_HELP_TEXT:
                    return "GET_HELP_TEXT";
                case FusionEnum::PacketType::LOGIN:
                    return "LOGIN";
                case FusionEnum::PacketType::LOGIN_CHALLENGE:
                    return "LOGIN_CHALLENGE";
                case FusionEnum::PacketType::LOGIN_RESPONSE:
                    return "LOGIN_RESPONSE";
                case FusionEnum::PacketType::LOGIN_OK:
                    return "LOGIN_OK";
                case FusionEnum::PacketType::ACTIVATE_ACCOUNT:
                    return "ACTIVATE_ACCOUNT";
                case FusionEnum::PacketType::RESEND_VERIFICATION_CODE:
                    return "RESEND_VERIFICATION_CODE";
                case FusionEnum::PacketType::IM_LOGIN:
                    return "IM_LOGIN";
                case FusionEnum::PacketType::IM_SESSION_STATUS:
                    return "IM_SESSION_STATUS";
                case FusionEnum::PacketType::IM_AVAILABLE:
                    return "IM_AVAILABLE";
                case FusionEnum::PacketType::SLIM_LOGIN:
                    return "SLIM_LOGIN";
                case FusionEnum::PacketType::SLIM_LOGIN_OK:
                    return "SLIM_LOGIN_OK";
                case FusionEnum::PacketType::CREATE_SESSION:
                    return "CREATE_SESSION";
                case FusionEnum::PacketType::SLIM_LOGIN_CHALLENGE:
                    return "SLIM_LOGIN_CHALLENGE";
                case FusionEnum::PacketType::GET_CONTACTS:
                    return "GET_CONTACTS";
                case FusionEnum::PacketType::GROUP:
                    return "GROUP";
                case FusionEnum::PacketType::CONTACT:
                    return "CONTACT";
                case FusionEnum::PacketType::GET_CONTACTS_COMPLETE:
                    return "GET_CONTACTS_COMPLETE";
                case FusionEnum::PacketType::PRESENCE:
                    return "PRESENCE";
                case FusionEnum::PacketType::ADD_CONTACT:
                    return "ADD_CONTACT";
                case FusionEnum::PacketType::REMOVE_CONTACT:
                    return "REMOVE_CONTACT";
                case FusionEnum::PacketType::UPDATE_CONTACT:
                    return "UPDATE_CONTACT";
                case FusionEnum::PacketType::ADD_GROUP:
                    return "ADD_GROUP";
                case FusionEnum::PacketType::REMOVE_GROUP:
                    return "REMOVE_GROUP";
                case FusionEnum::PacketType::UPDATE_GROUP:
                    return "UPDATE_GROUP";
                case FusionEnum::PacketType::MOVE_CONTACT:
                    return "MOVE_CONTACT";
                case FusionEnum::PacketType::CONTACT_REQUEST:
                    return "CONTACT_REQUEST";
                case FusionEnum::PacketType::ACCEPT_CONTACT_REQUEST:
                    return "ACCEPT_CONTACT_REQUEST";
                case FusionEnum::PacketType::REJECT_CONTACT_REQUEST:
                    return "REJECT_CONTACT_REQUEST";
                case FusionEnum::PacketType::GET_PERMISSION_LIST:
                    return "GET_PERMISSION_LIST";
                case FusionEnum::PacketType::PERMISSION_LIST:
                    return "PERMISSION_LIST";
                case FusionEnum::PacketType::SET_PERMISSION:
                    return "SET_PERMISSION";
                case FusionEnum::PacketType::VOICE_CAPABILITY:
                    return "VOICE_CAPABILITY";
                case FusionEnum::PacketType::HAVE_LATEST_CONTACT_LIST:
                    return "HAVE_LATEST_CONTACT_LIST";
                case FusionEnum::PacketType::CONTACT_LIST_VERSION:
                    return "CONTACT_LIST_VERSION";
                case FusionEnum::PacketType::STATUS_MESSAGE:
                    return "STATUS_MESSAGE";
                case FusionEnum::PacketType::USER_EVENT:
                    return "USER_EVENT";
                case FusionEnum::PacketType::DISPLAY_PICTURE:
                    return "DISPLAY_PICTURE";
                case FusionEnum::PacketType::GET_USER_INIT_DETAILS:
                    return "GET_USER_INIT_DETAILS";
                case FusionEnum::PacketType::GET_CONTACT_REQUESTS:
                    return "GET_CONTACT_REQUESTS";
                case FusionEnum::PacketType::MESSAGE:
                    return "MESSAGE";
                case FusionEnum::PacketType::WAP_PUSH:
                    return "WAP_PUSH";
                case FusionEnum::PacketType::FILE_RECEIVED:
                    return "FILE_RECEIVED";
                case FusionEnum::PacketType::MAIL_INFO:
                    return "MAIL_INFO";
                case FusionEnum::PacketType::UPLOAD_FILE:
                    return "UPLOAD_FILE";
                case FusionEnum::PacketType::SET_MESSAGE_EVENT:
                    return "SET_MESSAGE_EVENT";
                case FusionEnum::PacketType::MESSAGE_EVENT:
                    return "MESSAGE_EVENT";
                case FusionEnum::PacketType::LEAVE_PRIVATE_CHAT:
                    return "LEAVE_PRIVATE_CHAT";
                case FusionEnum::PacketType::GET_MESSAGES:
                    return "GET_MESSAGES";
                case FusionEnum::PacketType::GET_CHATS:
                    return "GET_CHATS";
                case FusionEnum::PacketType::HAVE_LATEST_CHAT_LIST:
                    return "HAVE_LATEST_CHAT_LIST";
                case FusionEnum::PacketType::CHAT:
                    return "CHAT";
                case FusionEnum::PacketType::CHAT_LIST_VERSION:
                    return "CHAT_LIST_VERSION";
                case FusionEnum::PacketType::END_MESSAGES:
                    return "END_MESSAGES";
                case FusionEnum::PacketType::LATEST_MESSAGES_DIGEST:
                    return "LATEST_MESSAGES_DIGEST";
                case FusionEnum::PacketType::SET_CHAT_NAME:
                    return "SET_CHAT_NAME";
                case FusionEnum::PacketType::SET_PRESENCE:
                    return "SET_PRESENCE";
                case FusionEnum::PacketType::SET_STATUS_MESSAGE:
                    return "SET_STATUS_MESSAGE";
                case FusionEnum::PacketType::SET_DISPLAY_PICTURE:
                    return "SET_DISPLAY_PICTURE";
                case FusionEnum::PacketType::AVATAR:
                    return "AVATAR";
                case FusionEnum::PacketType::DEVICE_MODE:
                    return "DEVICE_MODE";
                case FusionEnum::PacketType::GET_CHATROOMS:
                    return "GET_CHATROOMS";
                case FusionEnum::PacketType::CHATROOM:
                    return "CHATROOM";
                case FusionEnum::PacketType::GET_CHATROOMS_COMPLETE:
                    return "GET_CHATROOMS_COMPLETE";
                case FusionEnum::PacketType::JOIN_CHATROOM:
                    return "JOIN_CHATROOM";
                case FusionEnum::PacketType::LEAVE_CHATROOM:
                    return "LEAVE_CHATROOM";
                case FusionEnum::PacketType::CREATE_CHATROOM:
                    return "CREATE_CHATROOM";
                case FusionEnum::PacketType::KICK_CHATROOM_PARTICIPANT:
                    return "KICK_CHATROOM_PARTICIPANT";
                case FusionEnum::PacketType::GET_CHATROOM_PARTICIPANTS:
                    return "GET_CHATROOM_PARTICIPANTS";
                case FusionEnum::PacketType::CHATROOM_PARTICIPANTS:
                    return "CHATROOM_PARTICIPANTS";
                case FusionEnum::PacketType::MUTE_CHATROOM_PARTICIPANT:
                    return "MUTE_CHATROOM_PARTICIPANT";
                case FusionEnum::PacketType::UNMUTE_CHATROOM_PARTICIPANT:
                    return "UNMUTE_CHATROOM_PARTICIPANT";
                case FusionEnum::PacketType::ADD_FAVOURITE_CHATROOM:
                    return "ADD_FAVOURITE_CHATROOM";
                case FusionEnum::PacketType::REMOVE_FAVOURITE_CHATROOM:
                    return "REMOVE_FAVOURITE_CHATROOM";
                case FusionEnum::PacketType::GET_CHATROOM_CATEGORIES:
                    return "GET_CHATROOM_CATEGORIES";
                case FusionEnum::PacketType::CHATROOM_CATEGORY:
                    return "CHATROOM_CATEGORY";
                case FusionEnum::PacketType::GET_CHATROOM_CATEGORIES_COMPLETE:
                    return "GET_CHATROOM_CATEGORIES_COMPLETE";
                case FusionEnum::PacketType::GET_CATEGORIZED_CHATROOMS:
                    return "GET_CATEGORIZED_CHATROOMS";
                case FusionEnum::PacketType::GET_CATEGORIZED_CHATROOMS_COMPLETE:
                    return "GET_CATEGORIZED_CHATROOMS_COMPLETE";
                case FusionEnum::PacketType::CHATROOM_NOTIFICATION:
                    return "CHATROOM_NOTIFICATION";
                case FusionEnum::PacketType::CHATROOM_THEME:
                    return "CHATROOM_THEME";
                case FusionEnum::PacketType::CHATROOM_USER_STATUS:
                    return "CHATROOM_USER_STATUS";
                case FusionEnum::PacketType::GROUP_CHAT:
                    return "GROUP_CHAT";
                case FusionEnum::PacketType::CREATE_GROUP_CHAT:
                    return "CREATE_GROUP_CHAT";
                case FusionEnum::PacketType::GROUP_CHAT_INVITE:
                    return "GROUP_CHAT_INVITE";
                case FusionEnum::PacketType::LEAVE_GROUP_CHAT:
                    return "LEAVE_GROUP_CHAT";
                case FusionEnum::PacketType::GET_GROUP_CHAT_PARTICIPANTS:
                    return "GET_GROUP_CHAT_PARTICIPANTS";
                case FusionEnum::PacketType::GROUP_CHAT_PARTICIPANTS:
                    return "GROUP_CHAT_PARTICIPANTS";
                case FusionEnum::PacketType::GROUP_CHAT_USER_STATUS:
                    return "GROUP_CHAT_USER_STATUS";
                case FusionEnum::PacketType::INVITE_FRIEND:
                    return "INVITE_FRIEND";
                case FusionEnum::PacketType::GET_ACCOUNT_BALANCE:
                    return "GET_ACCOUNT_BALANCE";
                case FusionEnum::PacketType::ACCOUNT_BALANCE:
                    return "ACCOUNT_BALANCE";
                case FusionEnum::PacketType::RECHARGE:
                    return "RECHARGE";
                case FusionEnum::PacketType::FORGOT_PASSWORD:
                    return "FORGOT_PASSWORD";
                case FusionEnum::PacketType::GET_USER_PROFILE:
                    return "GET_USER_PROFILE";
                case FusionEnum::PacketType::USER_PROFILE:
                    return "USER_PROFILE";
                case FusionEnum::PacketType::UPDATE_USER_PROFILE:
                    return "UPDATE_USER_PROFILE";
                case FusionEnum::PacketType::CHANGE_PASSWORD:
                    return "CHANGE_PASSWORD";
                case FusionEnum::PacketType::TRANSFER_CREDIT:
                    return "TRANSFER_CREDIT";
                case FusionEnum::PacketType::GET_URL:
                    return "GET_URL";
                case FusionEnum::PacketType::DYNAMIC_MENU:
                    return "DYNAMIC_MENU";
                case FusionEnum::PacketType::WALLPAPER:
                    return "WALLPAPER";
                case FusionEnum::PacketType::GET_EMOTICON:
                    return "GET_EMOTICON";
                case FusionEnum::PacketType::EMOTICON:
                    return "EMOTICON";
                case FusionEnum::PacketType::CLEAR_EMOTICON:
                    return "CLEAR_EMOTICON";
                case FusionEnum::PacketType::EMOTICON_HOTKEYS:
                    return "EMOTICON_HOTKEYS";
                case FusionEnum::PacketType::MIDLET_TAB:
                    return "MIDLET_TAB";
                case FusionEnum::PacketType::MIDLET_ACTION:
                    return "MIDLET_ACTION";
                case FusionEnum::PacketType::CHANGE_USER_EVENT_SETTING:
                    return "CHANGE_USER_EVENT_SETTING";
                case FusionEnum::PacketType::OPEN_URL:
                    return "OPEN_URL";
                case FusionEnum::PacketType::PEN_URL_RESPONSE:
                    return "PEN_URL_RESPONSE";
                case FusionEnum::PacketType::TEXT_COLOUR:
                    return "TEXT_COLOUR";
                case FusionEnum::PacketType::LANGUAGE:
                    return "LANGUAGE";
                case FusionEnum::PacketType::GET_IM_ICONS:
                    return "GET_IM_ICONS";
                case FusionEnum::PacketType::IM_ICONS:
                    return "IM_ICONS";
                case FusionEnum::PacketType::GET_EMOTICONS_COMPLETE:
                    return "GET_EMOTICONS_COMPLETE";
                case FusionEnum::PacketType::GET_DYNAMIC_MENU_ICON:
                    return "GET_DYNAMIC_MENU_ICON";
                case FusionEnum::PacketType::DYNAMIC_MENU_ICON:
                    return "DYNAMIC_MENU_ICON";
                case FusionEnum::PacketType::GET_PRELOGIN_MARKETING_MSG:
                    return "GET_PRELOGIN_MARKETING_MSG";
                case FusionEnum::PacketType::PRELOGIN_MARKETING_MSG:
                    return "PRELOGIN_MARKETING_MSG";
                case FusionEnum::PacketType::APPLICATION_MENU:
                    return "APPLICATION_MENU";
                case FusionEnum::PacketType::APPLICATION_MENU_COMPLETE:
                    return "APPLICATION_MENU_COMPLETE";
                case FusionEnum::PacketType::GET_GIFT:
                    return "GET_GIFT";
                case FusionEnum::PacketType::GIFT_HOTKEYS:
                    return "GIFT_HOTKEYS";
                case FusionEnum::PacketType::GET_EMOTICON_HOTKEYS:
                    return "GET_EMOTICON_HOTKEYS";
                case FusionEnum::PacketType::GET_STICKER_PACK_LIST:
                    return "STICKER_PACK_LIST";
                case FusionEnum::PacketType::STICKER_PACK_LIST:
                    return "GET_STICKER_PACK";
                case FusionEnum::PacketType::GET_STICKER_PACK:
                    return "STICKER_PACK";
                case FusionEnum::PacketType::STICKER_PACK:
                    return "END_STICKER_PACK";
                case FusionEnum::PacketType::END_STICKER_PACK:
                    return "GET_UPLOAD_DATA_TICKET";
                case FusionEnum::PacketType::GET_UPLOAD_DATA_TICKET:
                    return "GET_UPLOAD_DATA_TICKET";
                case FusionEnum::PacketType::UPLOAD_ADDRESS_BOOK_CONTACTS:
                    return "UPLOAD_ADDRESS_BOOK_CONTACTS";
                default:
                    return "";
            }
        }
	};
	
//============================================================================
} // namespace migme
//============================================================================
