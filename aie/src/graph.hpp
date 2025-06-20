#include <adf.h>

#include "hadamard_stream.hpp"

using namespace adf;

class hadamardGraph : public graph {
	kernel hadamard_k;

public:
	input_plio in_stream;
	input_port qubit;
	input_port num_qubits;
	output_plio out_stream;

	hadamardGraph() {
		hadamard_k = kernel::create(hadamard_stream);
		source(hadamard_k) = "hadamard_stream.cc";

		runtime<ratio>(hadamard_k) = 1.0;

		in_stream = input_plio::create("input", plio_64_bits, "data/input.txt");
		out_stream = output_plio::create("output", plio_64_bits, "data/output.txt");

		connect<stream>(in_stream.out[0], hadamard_k.in[0]);
		connect<stream>(hadamard_k.out[0], out_stream.in[0]);
		connect<parameter>(qubit, hadamard_k.in[1]);
		connect<parameter>(num_qubits, hadamard_k.in[2]);
	}
};
