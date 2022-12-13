#ifndef _class_game_state_
#define _class_game_state_

#include <iostream>
#include <vector>
#include <limits>

#include "./common_structures.h"
#include "./PlayerState.hpp"

#include "./Libraries/src/graph.hpp"
#include "./Libraries/src/graph_math.hpp"
#include "./Libraries/src/edge.hpp"

class GameState {
public:

	GameState();
	GameState(int size_of_playgraund, Players who_will_start);
	
	void set_move(Players player, int id_hex);
	int get_last_move() { return last_move; }
	int get_size_field() { return game_field.size(); }
	Players get_winner();
	Players who_making_move_now() { return who_is_moving; }
	StatusHex get_ball();
	~GameState() { std::cout << "I'm delete game_state. Don't worry." << std::endl; }

private:

	std::vector<std::vector<StatusHex>> game_field;
	int last_move;
	Players who_is_moving;

	PlayerState blue_player;
	PlayerState red_player;
};

#endif