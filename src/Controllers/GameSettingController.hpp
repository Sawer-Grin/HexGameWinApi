#ifndef _class_game_setting_controller_
#define _class_game_setting_controller_

#define ID_GROUP_BOX_SETTINGS 202
#define ID_BUTTON_WITH_SIZE_5 204
#define ID_BUTTON_WITH_SIZE_7 208
#define ID_GROUP_BOX_CURRENT_PLAYER 210
#define ID_CURRENT_PLAYER 212

#include "windows.h"

#include <iostream>

#include "../PlayerState.hpp"
#include "../common_structures.h"

class GameSettingController {
public:

	GameSettingController();
	GameSettingController(HWND parent_hwnd, int x_start, int y_start);
	GameSettingController& operator=(GameSettingController&& controller);
	void set_as_unchecked();
	void set_player(Players player);
	void update_view();
	~GameSettingController();

private:

	HWND block_for_choosing;
	HWND choosing_size_of_playgraund_5;
    HWND choosing_size_of_playgraund_7;

    HWND block_for_current_player;
    HWND label_with_player;

    bool player_changed;
    Players current_player;
};

#endif