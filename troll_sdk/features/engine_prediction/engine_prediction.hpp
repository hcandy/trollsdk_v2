#pragma once
#include "../../main.hpp"

namespace engine_prediction {
	inline struct stored_vars {
		float m_frame_time;
		float m_cur_time;
	}stored_vars;

	inline struct viewmodel_t {
		float m_viewmodel_cycle;
		float m_viewmodel_anim_time;
	}stored_viewmodel;

	void predict( c_usercmd* cmd );
	void restore( );

	void update( );

	void update_viewmodel_data( );
	void correct_viewmodel_data( );
}