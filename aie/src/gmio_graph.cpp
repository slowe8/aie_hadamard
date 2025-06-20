#include <iostream>
#include <adf.h>
#include "gmio_graph.hpp"

hadamardGraph G;

#if defined(__AIESIM__) || defined(__X86SIM__)
int main() {
	const int qubit = 1;
	const int num_qubits = 3;
	const int size = 2 << num_qubits;

	cfloat *input_state = (cfloat*) GMIO::malloc(size * sizeof(cfloat));
	cfloat *output_state = (cfloat*) GMIO::malloc(size * sizeof(cfloat));
	
	input_state[0] = {1.0, 0.0};
	for (int i = 1; i < size; i++) {
		input_state[i] = {0.0, 0.0};
	}

	G.init();

	G.in_stream.gm2aie_nb(input_state, size * sizeof(cfloat));
	G.out_stream.aie2gm_nb(output_state, size * sizeof(cfloat));

	G.run(1);
	
	G.update(G.qubit, 1);
	G.update(G.num_qubits, 3);

	G.out_stream.wait();

	for (int i = 0; i < size; i++) {
		std::cout << output_state[i].real << "\n";
	}

	GMIO::free(input_state);
	GMIO::free(output_state);

	G.end();

	return 0;
}
#endif
