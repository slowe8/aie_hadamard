#include <cmath>

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

#include <aie_api/aie.hpp>
#include <adf.h>

#include "generic_gate1q.hpp"

using namespace adf;

void generic_gate1q(
	input_stream_cfloat *input_state,
	output_stream_cfloat *output_state,
	int32 num_qubits,
	int32 gate,
	int32 target
) {

	Gate1Q gate_id = static_cast<Gate1Q>(gate);

	const int N = 1 << num_qubits;		// Size of state
	const int stride = 1 << target;

	cfloat state[N];
	for (int i = 0; i < N; ++i) {
		state[i] = readincr(input_state);
	}

	const float norm = 1.0f / std::sqrtf(2.0f);
	const cfloat S_PHASE(0, 1);
	const cfloat SDG_PHASE(0, -1);
	const cfloat T_PHASE(std::cos(M_PI / 4.0f), std::sin(M_PI / 4.0f));
	const cfloat TDG_PHASE(std::cos(-M_PI / 4.0f), std::sin(M_PI / 4.0f));

	for (int i = 0; i < N; i += 2 * stride) chess_prepare_for_pipelining {
		for (int j = 0; j < stride; j++) {
			int idx0 = i + j;
			int idx1 = idx0 + stride;
	
			cfloat a = state[idx0];
			cfloat b = state[idx1];

			switch (gate_id) {
				case Gate1Q::H:
					state[idx0] = norm * (a + b);
					state[idx1] = norm * (a - b);
					break;
				case Gate1Q::X:
					state[idx0] = b;
					state[idx1] = a;
					break;
				case Gate1Q::Y:
					state[idx0] = cfloat(0, -1) * b;
					state[idx1] = cfloat(0, -1) * a;
					break;
				case Gate1Q::Z:
					state[idx0] = a;
					state[idx1] = -b;
					break;
				case Gate1Q::S:
					state[idx0] = a;
					state[idx1] = S_PHASE * b;
					break;
				case Gate1Q::SDG:
					state[idx0] = a;
					state[idx1] = SDG_PHASE * b;
					break;
				case Gate1Q::T:
					state[idx0] = a;
					state[idx1] = T_PHASE * b;
					break;
				case Gate1Q::TDG:
					state[idx0] = a;
					state[idx1] = TDG_PHASE * b;
					break;
				default:
					state[idx0] = a;
					state[idx1] = b;
					break;
			}
		}
	}
	
	for (int i = 0; i < N; i++) {
		writeincr(output_state, state[i]);
	}

}
