#include "PlayerState.hpp"

inline bool check_index(int index, int size_field);
inline std::vector<int> get_possible_neighbors(int i_index, int j_index, int size_field);

PlayerState::PlayerState(): history_of_steps(0) {

	graph = Graph();
}

PlayerState::PlayerState(int size_of_playgraund): history_of_steps(0) {

	graph = Graph(size_of_playgraund * size_of_playgraund);
}

PlayerState& PlayerState::operator=(const PlayerState& player_state) {

	this->graph = player_state.graph;
	this->history_of_steps = player_state.history_of_steps;

	return *this;
}

void PlayerState::save_step(int id_hex, const std::vector<std::vector<StatusHex>>& current_field) {

	history_of_steps.push_back(id_hex);
	add_connections(current_field);
}

int PlayerState::make_step() {

	return INT_MAX; // mocked
}

bool PlayerState::check_state(const std::vector<int>& border_up, const std::vector<int>& border_down) {

	int ostov_cost = 0;
	std::vector<int> vec_border_up(0), vec_border_down(0);
	std::set<int> all_ver;
	bool response = false;

	auto ostov_tree = graph_algorithms::kruscal(graph, standart_connection_weight, ostov_cost);
	for (auto edge = ostov_tree.begin(); edge != ostov_tree.end(); ++edge) {
		all_ver.insert(edge->vertex_a);
		all_ver.insert(edge->vertex_b);
	}

	for (auto item = border_up.begin(); item != border_up.end(); ++item) {
		if (all_ver.find(*item) != all_ver.end()) {
			vec_border_up.push_back(*item);
		}
	}

	for (auto item = border_down.begin(); item != border_down.end(); ++item) {
		if (all_ver.find(*item) != all_ver.end()) {
			vec_border_down.push_back(*item);
		}
	}

	for (auto f_ver = border_up.begin(); f_ver != border_up.end(); ++f_ver) {
		for (auto s_ver = border_down.begin(); s_ver != border_down.end(); ++s_ver) {
			if (graph.is_connected_with(*f_ver, *s_ver, standart_connection_weight)){
				response = true;
			}
		}
	}

	return response;
}

void PlayerState::add_connections(const std::vector<std::vector<StatusHex>>& field) {
	
	int last_step = history_of_steps.back(), size_of_field = round(sqrt(graph.V()));
	int i_index = last_step / size_of_field,
		j_index = last_step % size_of_field;

	auto neighbors = get_possible_neighbors(i_index, j_index, size_of_field);

	if (neighbors.size() > 0) {

		for (auto ver = neighbors.begin(); ver != neighbors.end(); ++ver){
			int nei_i_index = *ver / size_of_field,
				nei_j_index = *ver % size_of_field;
			bool is_neighbord = equal_status_hex(field[i_index][j_index], field[nei_i_index][nei_j_index]);

			if (is_neighbord) {

				graph.set_edge_value(last_step, *ver, standart_connection_weight);
			}
		}
	}
}

inline bool check_index(int index, int size_field){

	return (index >= 0) && (index < size_field);
}

inline std::vector<int> get_possible_neighbors(int i_index, int j_index, int size_field) {

	std::vector<std::pair<int, int>> delta_indexes { //(i, j)
		{-1, 0}, {-1, 1}, {0, 1}, {1, 0}, {1, -1}, {0, -1}
	};
	std::vector<int> neighbors;

	for (auto delta = delta_indexes.begin(); delta != delta_indexes.end(); ++delta) {
		int temp_i_index = i_index + delta->first,
			temp_j_index = j_index + delta->second;

		if (check_index(temp_i_index, size_field) && check_index(temp_j_index, size_field)) {
			neighbors.push_back(temp_i_index * size_field + temp_j_index);
		}
	}
	return neighbors;
}