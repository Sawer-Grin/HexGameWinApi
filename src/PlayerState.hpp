#ifndef _class_PlayerState_
#define _class_PlayerState_

#define standart_connection_weight 2

#include <iostream>
#include <vector>
#include <climits>
#include <set>

#include "./common_structures.h"
#include "./Libraries/src/graph.hpp"
#include "./Libraries/src/graph_math.hpp"
#include "./Libraries/src/edge.hpp"

class PlayerState {
public:

	PlayerState();
	PlayerState(int size_of_playgraund);
	PlayerState& operator= (const PlayerState& g);
	void save_step(int id_hex, const std::vector<std::vector<StatusHex>>& current_field);
	int make_step();
	bool check_state(const std::vector<int>& border_up, 
		const std::vector<int>& border_down);
	~PlayerState() { }

private:

	Graph graph;
	std::vector<int> history_of_steps;
	//AI *helper

	void add_connections(const std::vector<std::vector<StatusHex>>& field);									// Added connections for last element in history_of_steps
};

#endif