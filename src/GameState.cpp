#include "GameState.hpp"

inline StatusHex get_status_hex(Players player);
inline Players get_previus_player(Players player);
inline std::vector<int> get_upper_border_red_player(int size_of_field);
inline std::vector<int> get_down_border_red_player(int size_of_field);
inline std::vector<int> get_upper_border_blue_player(int size_of_field);
inline std::vector<int> get_down_border_blue_player(int size_of_field);
void print_vector(const std::vector<int>& vec);

GameState::GameState() {

	game_field = std::vector<std::vector<StatusHex>>(0);
	last_move = INT_MAX;
	who_is_moving = Players::None;

	blue_player = PlayerState();
	red_player = PlayerState();
}

GameState::GameState(int size_of_playgraund, Players who_will_start) {

	game_field = std::vector<std::vector<StatusHex>>(size_of_playgraund);
	for (int i = 0; i < game_field.size(); ++i){
		game_field[i] = std::vector<StatusHex>(size_of_playgraund);
		for (auto item = game_field[i].begin(); item != game_field[i].end(); ++item){
			*item = StatusHex::neutral_step;
		}
	}

	blue_player = PlayerState(size_of_playgraund);
	red_player = PlayerState(size_of_playgraund);
	last_move = INT_MAX;
	who_is_moving = who_will_start;
}

void GameState::set_move(Players player, int id_hex) {

	int size_of_playgraund = game_field.size();
	bool is_correct_id = (id_hex < size_of_playgraund * size_of_playgraund);
	bool is_correct_player = (player == who_is_moving);

	if ((size_of_playgraund > 0) && is_correct_id && is_correct_player) {

		int i_index = id_hex / size_of_playgraund,
			j_index = id_hex % size_of_playgraund;
		bool is_correct_move = (game_field[i_index][j_index] == StatusHex::neutral_step);

		if (is_correct_move) {

			game_field[i_index][j_index] = get_status_hex(player);
			who_is_moving = increase(who_is_moving);

			if (player == Players::Blue) {
				blue_player.save_step(id_hex, game_field);
			} else  if (player == Players::Red) {
				red_player.save_step(id_hex, game_field);
			} else {
				std::cerr << "Problem GameState::set_move()" << std::endl;
			}
		}

	} else {
		std::cerr << "Uncorrect setting move" << std::endl;
	}
}

StatusHex GameState::get_ball() {

	StatusHex status_hex;
	if (who_is_moving == Players::Red) {
		status_hex = red_step;
	} else if (who_is_moving == Players::Blue) {
		status_hex = blue_step;
	} else {
		std::cerr << "Problem with method GameState::get_ball" << std::endl;
	}

	return status_hex;
}

Players GameState::get_winner() {

	Players winner = Players::None;
	Players prev_player = get_previus_player(who_is_moving);
	if (prev_player == Players::Blue) {

		auto upper_border = get_upper_border_blue_player(game_field.size());
		auto down_border = get_down_border_blue_player(game_field.size());
		
		if (blue_player.check_state(upper_border, down_border)) {
			winner = Players::Blue;
		}

	} else if (prev_player == Players::Red) {

		auto upper_border = get_upper_border_red_player(game_field.size());
		auto down_border = get_down_border_red_player(game_field.size());

		if (red_player.check_state(upper_border, down_border)) {
			winner = Players::Red;
		}

	} else {
		std::cerr << "Problem with get_winner()" << std::endl;
	}

	return winner;
}

inline StatusHex get_status_hex(Players player) {

	StatusHex output = StatusHex::neutral_step;
	switch (player) {
		case Players::Red: {
			output = StatusHex::red_step;
			break;
		}
		case Players::Blue: {
			output = StatusHex::blue_step;
			break;
		}
		default: 
			std::cerr << "Problem in get_status_hex" << std::endl;
	}

	return output;
}

inline Players get_previus_player(Players player) {

	Players prev_player = Players::None;
	switch (player) {
		case Players::Blue:
			prev_player = Players::Red;
			break;
		case Players::Red:
			prev_player = Players::Blue;
			break;
		default: {
			std::cerr << "Problem in GameState::get_previus_player" << std::endl;
		}
	}

	return prev_player;
}

inline std::vector<int> get_upper_border_red_player(int size_of_field) {

	std::vector<int> output = std::vector<int>(0);
	for (int i = 0; i < size_of_field; ++i) {
		output.push_back(i);
	}
	return output;
}

inline std::vector<int> get_down_border_red_player(int size) {

	std::vector<int> output = std::vector<int>(0);
	for (int i = size * (size - 1); i < size * size ; ++i){
		output.push_back(i);
	}
	return output;
}

inline std::vector<int> get_upper_border_blue_player(int size_of_field) {

	std::vector<int> output = std::vector<int>(0);
	for (int i = 0; i <= size_of_field * (size_of_field - 1);){
		output.push_back(i);
		i += size_of_field;
	}
	return output;
}

inline std::vector<int> get_down_border_blue_player(int size) {

	std::vector<int> output = std::vector<int>(0);
	for (int i = size - 1; i < size * size; ){
		output.push_back(i);
		i += size;
	}
	return output;
}

/// For debugging
void print_vector(const std::vector<int>& vec) {
	for (auto item = vec.begin(); item != vec.end(); ++item) {
		std::cout << " " << *item;
	}

	std::cout << std::endl;
}