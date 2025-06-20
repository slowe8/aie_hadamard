#include "graph.hpp"

hadamardGraph G;

#if defined(__AIESIM__) || defined(__X86SIM__)
int main() {
	G.init();
	G.run(1);
	
	G.update(G.qubit, 1);
	G.update(G.num_qubits, 3);

	G.end();

	return 0;
}
#endif
