#include <windows.h>
#include <iostream>

#include "./Controllers/PlaygraundController.hpp"
#include "./Controllers/GameSettingController.hpp"
#include "./GameState.hpp"
#include "./PlayerState.hpp"
#include "./common_structures.h"

#define SIZE_5 5
#define SIZE_7 7

const char g_szClassName[] = "myWindowClass";

PlaygraundController* playgraund_controller;
GameSettingController* playgraund_setting;
GameState* game_state;

bool initialize_playgraund = true;
bool fill_playgraund = true;

inline void delete_global_parametes(bool with_settings);
inline void initialize_controller_and_game_state(HWND hwnd, int size_of_playgraund, Players first_player);
inline void fill_white_rectangle(HWND hwnd, int x_start, int y_start);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE: {

            playgraund_controller = new PlaygraundController();
            playgraund_setting = new GameSettingController(hwnd, 360, 10);
            game_state = new GameState();

            break;
        }
        case WM_COMMAND: {

           	if (HIWORD(wParam) == BN_CLICKED) {
                switch (LOWORD(wParam)) {
                    case ID_BUTTON_WITH_SIZE_5: {
                        
                        if (game_state->get_size_field() != SIZE_5) {
	                        
                            initialize_controller_and_game_state(hwnd, SIZE_5, Players::Blue);
                            playgraund_setting->set_player(Players::Blue);
                            fill_playgraund = true;
                            initialize_playgraund = true;
	                        InvalidateRect(hwnd, NULL, 0);

	                    }
                        break;
                    }
                    case ID_BUTTON_WITH_SIZE_7: {

                    	if (game_state->get_size_field() != SIZE_7) {
							
							initialize_controller_and_game_state(hwnd, SIZE_7, Players::Red);
                            playgraund_setting->set_player(Players::Red);
                            fill_playgraund = true;
	                        initialize_playgraund = true;
	                        InvalidateRect(hwnd, NULL, 0);

	                    }	
                        break;
                    } 
                    default: {

                        playgraund_controller->set_player_step((int) wParam, game_state->get_ball());
                        Players current_player = game_state->who_making_move_now();
                        game_state->set_move(current_player, (int)wParam);
                        playgraund_setting->set_player(increase(current_player));
                        InvalidateRect(GetDlgItem(hwnd, wParam), NULL, 0);

                    }
                }
            }
        }
        case WM_PAINT: {

            if (fill_playgraund) {
                fill_white_rectangle(hwnd, 30, 30);
                fill_playgraund = false;
            }
            if (initialize_playgraund) {
                playgraund_controller->draw_all_buttons(hwnd);
                initialize_playgraund = false;
            }
            playgraund_controller->redraw_buttons(hwnd);
            playgraund_setting->update_view();

            // Part of game logic
            Players winner = game_state->get_winner();
            if (not_equal_player(winner, Players::None)) {

                std::string description = to_string(winner);
                int msg_id = MessageBox(hwnd, to_string(winner).c_str(), "Winner", MB_OK);
                if (msg_id > 0) {
                    delete_global_parametes(false);
                    initialize_controller_and_game_state(hwnd, 0, Players::None);

                    playgraund_setting->set_as_unchecked();
                    fill_playgraund = true;
                    InvalidateRect(hwnd, NULL, 0);
                }
            }
            break;
        }
        case WM_KEYDOWN:
            break;
        case WM_MOUSEWHEEL:
            break;
        case WM_KEYUP:
            break;
        case WM_CLOSE: {
            delete_global_parametes(true);
            DestroyWindow(hwnd);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_SIZE:
            InvalidateRect(hwnd, NULL, 0);
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;


    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.lpszMenuName  = NULL;    
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "The title of my window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    srand(time(NULL));

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

inline void fill_white_rectangle(HWND hwnd, int x_start, int y_start) {

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    RECT rect = {
        x_start, y_start, 
        x_start + SIZE_7 * button_width,
        y_start +  (2 * SIZE_7 - 1) * button_height,
    };
    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
    EndPaint(hwnd, &ps);
}

inline void delete_global_parametes(bool with_settings) {

    if (playgraund_controller != nullptr) {
        delete playgraund_controller;
        playgraund_controller = nullptr;
    }
    if (game_state != nullptr) {
        delete game_state;
        game_state = nullptr;
    }
    if (with_settings) {
        if (playgraund_setting != nullptr) {
            delete playgraund_setting;
            playgraund_setting = nullptr;
        }
    }
}

inline void initialize_controller_and_game_state(HWND hwnd, int size_of_playgraund, Players first_player){

    if (playgraund_controller != nullptr) {
        delete playgraund_controller;
    }
    if (game_state != nullptr) {
        delete game_state;
    }

    if (size_of_playgraund == 0) {

        playgraund_controller = new PlaygraundController();
        game_state = new GameState();
    
    } else {

        playgraund_controller = new PlaygraundController(hwnd, size_of_playgraund, 30, 30);
        game_state = new GameState(size_of_playgraund, first_player);
    
    }
}