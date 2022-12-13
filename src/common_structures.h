#ifndef _common_structures_
#define _common_structures_

#include <iostream>
#include <string>

enum StatusHex{
    blue_step,
    red_step,
    neutral_step,
};

enum Players{
	Blue,
	Red,
	None,
};

inline Players increase(const Players& player){
	if (player == Players::Blue) {
		return Players::Red;
	} else if (player == Players::Red){
		return Players::Blue;
	} else {
		std::cout << "Problem with operator++ in PLayers" << std::endl;
		return Players::None;
	}
}

inline bool equal_status_hex(const StatusHex& first_hex, const StatusHex& second_hex) {
	return ((int)first_hex == (int)second_hex);
}

inline std::string to_string(const Players& player) {
	
	std::string output;
	switch(player) {
		case Players::Red: {
			output = std::string("Red Player");
			break;
		}
		case Players::Blue: {
			output = std::string("Blue player");
			break;
		}
		default: {
			output = std::string("None player");
		}
	}

	return output;
}

inline bool not_equal_player(const Players& first_player, const Players& second_player) {
	return ((int)first_player != (int)second_player);
}

inline std::ostream& operator<<(std::ostream & os, Players& player) {
	if (player == Players::Red){
		os << "Red";
	} else if (player == Players::Blue) {
		os << "Blue";
	} else {
		os << "None";
	}
	return os;
}

#endif