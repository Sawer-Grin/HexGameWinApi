#include "GameSettingController.hpp"

void set_ball_in_button_s(HWND hwnd, LPPAINTSTRUCT lpPS,  long x_cor, long y_cor, HBITMAP picture, HBITMAP mask_for_ball);

GameSettingController::GameSettingController() {

	block_for_choosing = nullptr;
	choosing_size_of_playgraund_5 = nullptr;
	choosing_size_of_playgraund_7 = nullptr;

	block_for_choosing = nullptr;
	label_with_player = nullptr;
}

GameSettingController::GameSettingController(HWND parent_hwnd, int x_start, int y_start) {
	
	block_for_choosing = CreateWindowW(L"Button", L"Choose size", 
    	WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
    	x_start, y_start, 120, 110, parent_hwnd, (HMENU)ID_GROUP_BOX_SETTINGS, GetModuleHandle(NULL), NULL);
	if (block_for_choosing == nullptr) {
		std::cerr << "Problem with creating block_for_choosing" << std::endl;
	}
	choosing_size_of_playgraund_5 = CreateWindowW(L"Button", L"5",
    	WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
    	x_start + 10, y_start + 30, 100, 30, parent_hwnd, (HMENU)ID_BUTTON_WITH_SIZE_5, GetModuleHandle(NULL), NULL);
    if (choosing_size_of_playgraund_5 == nullptr) {
   		std::cerr << "Problem with creating choosing_size_of_playgraund_5" << std::endl;
    }

    choosing_size_of_playgraund_7 = CreateWindowW(L"Button", L"7",
    	WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
    	x_start + 10, y_start + 55, 100, 30, parent_hwnd, (HMENU)ID_BUTTON_WITH_SIZE_7, GetModuleHandle(NULL), NULL);
    if (choosing_size_of_playgraund_7 == nullptr) {
		std::cerr << "Problem with creating `choosing_size_of_playgraund_7" << std::endl;
    }

    block_for_current_player = CreateWindowW(L"Button", L"Player Now", 
    	WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
    	x_start, y_start + 150, 120, 70, parent_hwnd, (HMENU)ID_GROUP_BOX_CURRENT_PLAYER, GetModuleHandle(NULL), NULL);
    if (block_for_current_player == nullptr) {
    	std::cerr << "Problem with creating `block_for_current_player" << std::endl;
    }

    label_with_player = CreateWindowW(L"edit", L"Text",
    	WS_CHILD | WS_VISIBLE | WS_TABSTOP,
    	10, 30, 80, 20, block_for_current_player, (HMENU)ID_CURRENT_PLAYER, GetModuleHandle(NULL), NULL);
    if (label_with_player == nullptr) {
    	std::cerr << "Problem with creating label" << std::endl;
    }

    EnableWindow(block_for_current_player, false);
    SetWindowText(label_with_player, to_string(Players::None).c_str());
    player_changed = true;
    current_player = Players::None;
}

GameSettingController& GameSettingController::operator=(GameSettingController&& controller) {

	this->block_for_choosing = controller.block_for_choosing;
	this->choosing_size_of_playgraund_5 = controller.choosing_size_of_playgraund_5;
	this->choosing_size_of_playgraund_7 = controller.choosing_size_of_playgraund_7;

	this->block_for_current_player = controller.block_for_current_player;
	this->label_with_player = controller.label_with_player;

	player_changed = true;
	this->current_player = controller.current_player;

	return *this;
}

void GameSettingController::set_as_unchecked() {

	::SendMessage( choosing_size_of_playgraund_5, BM_SETCHECK, BST_UNCHECKED, (LPARAM)0 );
	::SendMessage( choosing_size_of_playgraund_7, BM_SETCHECK, BST_UNCHECKED, (LPARAM)0 );
}

void GameSettingController::set_player(Players player) {

	player_changed = true;
	current_player = player;
}

void GameSettingController::update_view() {

	PAINTSTRUCT ps;
	if (player_changed) {
		SetWindowText(label_with_player, to_string(current_player).c_str());
		player_changed = false;
	}
}

GameSettingController::~GameSettingController() {

	if (block_for_choosing != nullptr) {
		DestroyWindow(block_for_choosing);
	}

	if (choosing_size_of_playgraund_5 != nullptr) {
		DestroyWindow(choosing_size_of_playgraund_5);
	}

	if (choosing_size_of_playgraund_7 != nullptr) {
		DestroyWindow(choosing_size_of_playgraund_7);
	}

	if (block_for_current_player != nullptr) {
		DestroyWindow(block_for_current_player);
	}

	if (label_with_player != nullptr) {
		DestroyWindow(label_with_player);
	}
}