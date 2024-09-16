// para grafos dirigidos con un solo succ[i] O(n)
vi id_cycle(n, -2);
vector<map<int, int>> cycles; 
for (int p = 0; p < n; p++) {
	if (id_cycle[p] != -2) { continue; }
	vector<int> path{p};
	int at = p; 
	while (id_cycle[succ[at]] == -2) {
		at = succ[at];
		id_cycle[at] = -3;  // Leave breadcrumbs for this iteration
		path.push_back(at);
	}
    // at es donde termina el bucle at -> succ[at]
	std::map<int, int> cycle; // indice -> orden
	bool in_cycle = false;
	for (int i : path) {
        // i es donde comienza el bucle, at -> succ[at] = i
		in_cycle = in_cycle || i == succ[at]; 
		if (in_cycle) { cycle[i] = cycle.size(); } // almacena el orden
		id_cycle[i] = in_cycle ? cycles.size() : -1;
	}
	cycles.push_back(cycle);
}




