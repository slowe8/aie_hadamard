#pragma once

#include <adf/stream/types.h>

#include "gate1q.hpp"

void generic_gate1q(
	input_stream_cfloat *input_state,
	output_stream_cfloat *output_state,
	int32 num_qubits,
	Gate1Q gate,
	int32 target
);
