#include <adf.h>

#include "generic_gate1q.hpp"

using namespace adf;

class Gate1QGraph : public graph {
	kernel gate1q_k;

public:
	input_plio in_stream;
	input_port gate;
	input_port target;
	input_port num_qubits;
	output_plio out_stream;

	Gate1QGraph() {
		gate1q_k = kernel::create(generic_gate1q);
		source(gate1q_k) = "generic_gate1q.cc";

		runtime<ratio>(gate1q_k) = 1.0;

		in_stream = input_plio::create("input", plio_64_bits, "data/input.txt");
		out_stream = output_plio::create("output", plio_64_bits, "data/output.txt");

		connect<stream>(in_stream.out[0], gate1q_k.in[0]);
		connect<stream>(gate1q_k.out[0], out_stream.in[0]);
		connect<parameter>(num_qubits, gate1q_k.in[1]);
		connect<parameter>(gate, gate1q_k.in[2]);
		connect<parameter>(target, gate1q_k.in[3]);
	}
};
