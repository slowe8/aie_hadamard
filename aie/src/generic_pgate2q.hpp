#pragma once

#include <adf/stream/types.h>

#include "pgate2q.hpp"

void generic_pgate2q(
	input_stream_cfloat *input_state,
	output_stream_cfloat *output_state,
	int32 num_qubits,
	Gate1Q gate,
	int32 control,
	int32 target,
	float32 paramter
);
