#include "graph.hpp"
#include "gate1q.hpp"

Gate1QGraph G;

#if defined(__AIESIM__) || defined(__X86SIM__)
int main() {
	G.init();
	G.run(1);
	
	G.update(G.gate, static_cast<int>(Gate1Q::X));
	G.update(G.target, 2);
	G.update(G.num_qubits, 3);

	G.end();

	return 0;
}
#endif
