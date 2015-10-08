#pragma once

#include <functional>
#include <vector>

#include "APIMain.h"

namespace GWAPI {

	/*
	
		StoC Manager v1
		See https://github.com/GameRevision/GWLP-R/wiki/GStoC for some already explored packets.
	*/

	class StoCMgr {
	public:

		/* 
			Base structure definition for stoc packets
			Inherit this, then ignore added header, just all other fields of packet in your definitions.
		*/
		struct StoCPacketBase {
			DWORD header;
		};
		typedef std::function<void(StoCPacketBase*)> Handler;



		/* Use this to add handlers to the stocmgr, primary function. */
		void AddGameServerEvent(DWORD packetheader, Handler func);

	private:

		typedef bool(__fastcall *StoCHandler_t)(StoCPacketBase* pak, DWORD unk);

		struct StoCHandler {
			DWORD* packettemplate;
			int templatesize;
			StoCHandler_t handlerfunc;
		};
		typedef GW::gw_array<StoCHandler> StoCHandlerArray;


		

		StoCMgr(GWAPIMgr* obj);
		~StoCMgr();

		static bool __fastcall StoCHandlerFunc(StoCPacketBase* pak, DWORD unk);

		static StoCHandler* game_server_handler_;
		static DWORD game_server_handler_count_;
		static StoCHandler* original_functions_;
		static std::vector<Handler>* event_calls_;
		friend class GWAPIMgr;
		GWAPIMgr* const parent_;
	};
}