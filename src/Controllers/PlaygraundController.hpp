#ifndef _class_controller_playgraund_
#define _class_controller_playgraund_

#define path_to_blue_ball "./photos/hex_b.bmp"
#define path_to_red_ball "./photos/hex_r.bmp"
#define path_to_mask_for_playgraund_button "./photos/hex_mask.bmp"
#define path_to_neutral_ball "./photos/hex_n.bmp"
#define button_height 24
#define button_width 28

#include <iostream>
#include <map>
#include <vector>
#include <limits>

#include "windows.h"
#include "../common_structures.h"

// About HMENU --> You can't use id in interval from 0 to 200
// You can't use HMENU for some performance
class PlaygraundController {
public:

	PlaygraundController();
	PlaygraundController(HWND parent_hwnd, int size_of_playgraund, int x_playgraund, int y_playgraund);
	PlaygraundController& operator=(PlaygraundController&& controller);
	void set_player_step(int _id_button, StatusHex new_step);
	bool redraw_buttons(HWND parent_hwnd);
	void draw_all_buttons(HWND parent_hwnd);														// Needs call just one times.
	~PlaygraundController();

private:

	std::vector<std::vector<HWND>> hexagonal_buttons;
	HBITMAP picture_with_red_ball;
	HBITMAP picture_with_blue_ball;
	HBITMAP picture_with_neutral_ball;
	HBITMAP mask_for_ball;
	int id_button;			 																		// Index for redraw one button(Some optimisation)
	bool need_to_redraw;
	HBITMAP next_picture;																			// Do not destroy this value

	void load_nessary_pictures();
	RECT delete_button();
};

#endif