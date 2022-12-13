#include "dsu.hpp"

int DSU::find(int v) {

	if ( v >= vertices_tree.size() )
		return -1;

	return (vertices_tree[v] == v) ? v : (vertices_tree[v] = find(vertices_tree[v]));
}

void DSU::unite(int f_vertex, int s_vertex){

	if ( (f_vertex >= vertices_tree.size()) && (s_vertex >= vertices_tree.size()) ) {
		return;
	}

	f_vertex = vertices_tree[f_vertex];
	s_vertex = vertices_tree[s_vertex];
	if (rank[f_vertex] < rank[s_vertex])
		vertices_tree[f_vertex] = s_vertex;
	else if (rank[f_vertex] > rank[s_vertex])
		vertices_tree[s_vertex] = f_vertex;
	else {
		vertices_tree[s_vertex] = f_vertex;
		rank[f_vertex] += 1;
	}
}

void DSU::make_set(int vertex) {

	if (vertex >= vertices_tree.size())
		return;

	vertices_tree[vertex] = vertex;
	rank[vertex] = 0;
}