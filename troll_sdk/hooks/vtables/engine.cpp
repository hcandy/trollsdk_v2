#include "../hooks.hpp"

void __cdecl hooks::engine::cl_move::hook( float accumulated_extra_samples, bool final_tick ) {
	o_cl_move( accumulated_extra_samples, final_tick );
}

void __fastcall hooks::engine::fire_game_event::hook( void* ecx, void* edx ) {
	if ( !g_local || !g_local->is_alive( ) )
		return o_fire_game_event( ecx, 0 );

	/* get this from CL_FireEvents string "Failed to execute event for classId" in engine.dll */
	auto event = *( event_t** ) ( uintptr_t( i::clientstate ) + 0x4E6C );
	while ( event ) {
		event->delay = 0.0f;
		event = event->next;
	}

	return o_fire_game_event( ecx, 0 );
}

void __fastcall hooks::engine::get_viewangles::hook( void* ecx, void* edx, vec3_t& ang ) {
	if ( g::should_store_angle ) {
		/* may need in some feature idk */
		g::should_store_angle = false;
	}

	o_get_viewangles( ecx, 0, ang );
}

bool __fastcall hooks::engine::is_connected::hook( void* ecx, void* edx ) {
	return o_is_connected( ecx, 0 );
}

bool __fastcall hooks::engine::is_hltv::hook( void* ecx, void* edx ) {
	static auto return_to_setup_vel = ( void* ) utils::find_sig_ida( "client.dll", "84 C0 75 38 8B 0D ? ? ? ? 8B 01 8B 80" );
	static auto return_to_accumulate_layers = ( void* ) utils::find_sig_ida( "client.dll", "84 C0 75 0D F6 87" );

	if ( _ReturnAddress( ) == return_to_setup_vel || _ReturnAddress( ) == return_to_accumulate_layers )
		return true;

	return o_is_hltv( ecx, 0 );
}

bool __fastcall hooks::engine::is_in_game::hook( void* ecx, void* edx ) {
	return o_is_in_game( ecx, 0 );
}

bool __fastcall hooks::engine::is_paused::hook( void* ecx, void* edx ) {
	static auto return_to_extrapolation = ( void* ) ( utils::find_sig_ida( "client.dll", "FF D0 A1 ?? ?? ?? ?? B9 ?? ?? ?? ?? D9 1D ?? ?? ?? ?? FF 50 34 85 C0 74 22 8B 0D ?? ?? ?? ??" ) + 0x29 );

	if ( _ReturnAddress( ) == return_to_extrapolation )
		return true;

	return o_is_paused( ecx, 0 );
}