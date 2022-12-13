#include "PlaygraundController.hpp"

inline void set_ball_in_button(HWND hwnd, LPPAINTSTRUCT lpPS,  long x_cor, long y_cor, HBITMAP picture, HBITMAP mask);
inline void redraw_button(HWND parent_hwnd,  long x_cor, long y_cor, HBITMAP picture, HBITMAP mask_for_picture);

PlaygraundController::PlaygraundController(): hexagonal_buttons(0) {

	load_nessary_pictures();
}

PlaygraundController::PlaygraundController(HWND parent_hwnd, int size_of_playgraund, int x_playgraund, int y_playgraund) {

	load_nessary_pictures();
	hexagonal_buttons = std::vector<std::vector<HWND>>(size_of_playgraund);
	int seed_for_button_id = 0;
	int x_temp = x_playgraund + (button_width / 2) * (size_of_playgraund - 1),
		y_temp = y_playgraund;

	for (size_t i = 0; i < hexagonal_buttons.size(); ++i) {
		hexagonal_buttons[i] = std::vector<HWND>(size_of_playgraund);
		for (auto item = hexagonal_buttons[i].begin(); item != hexagonal_buttons[i].end(); ++item){
			*item = CreateWindow("button", "", WS_VISIBLE | WS_CHILD | BS_BITMAP,
				x_temp, y_temp, button_width, button_height,
                parent_hwnd, (HMENU) seed_for_button_id, GetModuleHandle(NULL), NULL
            );

            if (*item == nullptr) {
            	std::cerr << "Problem with creating window" << std::endl;
            }

            ++seed_for_button_id;
            x_temp -= button_width / 2;
            y_temp += button_height;
		}

		x_temp += ((button_width / 2) * size_of_playgraund + button_width / 2);
		y_temp -= (button_height * (size_of_playgraund - 2) + button_height);
	}
}

PlaygraundController& PlaygraundController::operator=(PlaygraundController&& controller) {
	
	this->hexagonal_buttons = controller.hexagonal_buttons;
	this->picture_with_red_ball = controller.picture_with_red_ball;
	this->picture_with_blue_ball = controller.picture_with_blue_ball;
	this->picture_with_neutral_ball = controller.picture_with_neutral_ball;
	this->mask_for_ball = controller.mask_for_ball;

	this->id_button = controller.id_button;
	this->need_to_redraw = controller.need_to_redraw;
	this->next_picture = controller.next_picture;
	
	return *this;
}

PlaygraundController::~PlaygraundController() {

	for (int i = 0; i < hexagonal_buttons.size(); ++i) {
		for (auto item = hexagonal_buttons[i].begin(); item != hexagonal_buttons[i].end(); ++item) {
			if ( *item != nullptr ) {
				DestroyWindow((*item));
			}
		}
	}

	if (picture_with_red_ball != nullptr){
		DeleteObject(picture_with_red_ball);
    }
    if (picture_with_blue_ball != nullptr) {
    	DeleteObject(picture_with_blue_ball);
    }
    if (picture_with_neutral_ball != nullptr) {
    	DeleteObject(picture_with_neutral_ball);
    }
    if (mask_for_ball != nullptr) {
    	DeleteObject(mask_for_ball);
    }
}

bool PlaygraundController::redraw_buttons(HWND parent_hwnd) {

	if (need_to_redraw && (hexagonal_buttons.size() > 0)) {
		
		int size_of_playgraund = hexagonal_buttons.size();
		int i_index = id_button / size_of_playgraund,
			j_index = id_button % size_of_playgraund;
		
		if ((hexagonal_buttons[i_index][j_index] != nullptr) && (next_picture != nullptr)) {
			RECT data_deleted_button = delete_button();
			redraw_button(parent_hwnd, data_deleted_button.left, data_deleted_button.top, next_picture, mask_for_ball);
			
			need_to_redraw = false;
			id_button = INT_MAX;
			next_picture = nullptr;
		}
	}

	return !need_to_redraw;
}

void PlaygraundController::draw_all_buttons(HWND parent_hwnd) {
	if ((hexagonal_buttons.size() > 0) && (parent_hwnd != nullptr)) {

		for (int i = 0; i < hexagonal_buttons.size(); ++i) {
			for (auto item = hexagonal_buttons[i].begin(); item != hexagonal_buttons[i].end(); ++item) {
				if (*item != nullptr) {
					redraw_button(*item, 0, 0, picture_with_neutral_ball, mask_for_ball);
				}
			}
		}
	} else {
		std::cout << "Problem with initialize data in  draw_all_buttons()" << std::endl;
	}
}

void PlaygraundController::set_player_step(int _id_button, StatusHex new_step) {
	int size_of_playgraund = hexagonal_buttons.size();
	
	if ((size_of_playgraund != 0) && (_id_button < size_of_playgraund * size_of_playgraund)) {
		
		int i_index = _id_button / size_of_playgraund,
			j_index = _id_button % size_of_playgraund;
		
		if (hexagonal_buttons[i_index][j_index] != nullptr) {
			need_to_redraw = true;
			id_button = _id_button;

			switch (new_step) {
				case StatusHex::red_step: {
					next_picture = this->picture_with_red_ball;
					break;
				} 
				case StatusHex::blue_step: {
					next_picture = this->picture_with_blue_ball;
					break;
				} 
				default: {
					std::cerr << "Problem with setting next_picture" << std::endl;
				}
			}
		} else {
			std::cerr << "Problem with double setting step" << std::endl;
		}

	} else {
		std::cerr << "Problem with set player step" << std::endl;
	}
}

void PlaygraundController::load_nessary_pictures() {

	picture_with_red_ball = (HBITMAP)LoadImage(NULL, path_to_red_ball, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    picture_with_blue_ball = (HBITMAP)LoadImage(NULL, path_to_blue_ball, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    picture_with_neutral_ball = (HBITMAP)LoadImage(NULL, path_to_neutral_ball, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    mask_for_ball = (HBITMAP)LoadImage(NULL, path_to_mask_for_playgraund_button, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    if (picture_with_red_ball == nullptr){
        std::cerr << "Problem with loading red ball" << std::endl;
    }
    if (picture_with_blue_ball == nullptr) {
        std::cerr << "Problem with loading blue ball" << std::endl;
    }
    if (picture_with_neutral_ball == nullptr) {
        std::cerr << "Problem with loading neutral ball" << std::endl;
    }
    if (mask_for_ball == nullptr) {
        std::cerr << "Problem with loading mask" << std::endl;
    }
}

RECT PlaygraundController::delete_button() {

	int size_of_playgraund = hexagonal_buttons.size();
	int i_index = this->id_button / size_of_playgraund;
	int j_index = id_button % size_of_playgraund;
	RECT button_meta_data;

	if (hexagonal_buttons[i_index][j_index] != nullptr){

		GetWindowRect(hexagonal_buttons[i_index][j_index], &button_meta_data);
		MapWindowPoints(HWND_DESKTOP, GetParent(hexagonal_buttons[i_index][j_index]), (LPPOINT) &button_meta_data, 2);
		if (!DestroyWindow(hexagonal_buttons[i_index][j_index])) {
			std::cerr << "Problem in process of deleting" << std::endl;
		}
		hexagonal_buttons[i_index][j_index] = nullptr;

	} else {
		std::cerr << "Problem with deleting button" << std::endl;
	}

	return button_meta_data;
}

void redraw_button(HWND parent_hwnd,  long x_cor, long y_cor, HBITMAP picture, HBITMAP mask_for_picture) {

	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(parent_hwnd, &ps);
	set_ball_in_button(parent_hwnd, &ps, x_cor, y_cor, picture, mask_for_picture);
	EndPaint(parent_hwnd, &ps);
}

void set_ball_in_button(HWND hwnd, LPPAINTSTRUCT lpPS,  long x_cor, long y_cor, HBITMAP picture, HBITMAP mask_for_ball) {

	RECT rcUser;
    HDC hdcMem;
    HBITMAP hbmMem, hbmOld;
    HBRUSH hbrBkGnd;

    GetClientRect(hwnd, &rcUser);
    hdcMem = CreateCompatibleDC(lpPS->hdc);
    hbmMem = CreateCompatibleBitmap(lpPS->hdc, rcUser.right - rcUser.left, rcUser.bottom - rcUser.top);
    hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

    hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    FillRect(hdcMem, &rcUser, hbrBkGnd);
    DeleteObject(hbrBkGnd);

    BITMAP new_picture, mask;
    GetObject(picture, sizeof(new_picture), &new_picture);
    GetObject(mask_for_ball, sizeof(mask), &mask);

    HDC hdcSprite = CreateCompatibleDC(hdcMem);
    HBITMAP oldSprite = (HBITMAP)SelectObject(hdcSprite, mask_for_ball);
    BitBlt(hdcMem, x_cor, y_cor, x_cor + mask.bmWidth, y_cor + mask.bmHeight, hdcSprite, 0, 0, SRCCOPY);

    oldSprite = (HBITMAP)SelectObject(hdcSprite, picture);
    BitBlt(hdcMem, x_cor, y_cor, x_cor + new_picture.bmWidth, y_cor + new_picture.bmHeight, hdcSprite, 0, 0, SRCPAINT);
    DeleteDC(hdcSprite);
    BitBlt(lpPS->hdc,
           rcUser.left, 
           rcUser.top,
           rcUser.right - rcUser.left,
           rcUser.bottom - rcUser.top,
           hdcMem,
           0, 0,
           SRCCOPY);

    SelectObject(hdcMem, hbmOld);
    DeleteObject(hbmMem);
    DeleteDC(hdcMem);
}