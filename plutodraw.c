#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <signal.h>

#include <unistd.h>
#include <termios.h>

#include <pluto.h>

struct termios t_orig, t_chan;

void enable_raw_mode()
{
    tcgetattr(STDIN_FILENO, &t_orig);
    t_chan = t_orig;
    t_chan.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &t_chan);
}

void disable_raw_mode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &t_orig);
}

void handle_signal()
{
    disable_raw_mode();
    pluto_deinit();
    printf("exiting...\n");
}

int main()
{
    signal(SIGINT, handle_signal);
    enable_raw_mode();
    pluto_init_window();
    pluto_save_screen();
    _pluto_canvas.height -= 1;
    pluto_render();

    int cursor_x = 0;
    int cursor_y = 0;

    char key[3];
    bool exit = false;
    while (!exit)
    {
        key[0] = 0;
        key[1] = 0;
        key[2] = 0;
        read(STDIN_FILENO, &key[0], 3);
        //printf("keypress: %c\nkey int[0]: %d\nkey int[1]: %d\nkey int[2]: %d\nkey int[3]: %d\n\n", key[0], key[0], key[1], key[2], key[3]);
        if (key[0] == 27 && key[1] == 91)
        {
            switch (key[2])
            {
            case 'A':
                //printf("UP\n");
                if (cursor_x > 0)
                {
                    cursor_x--;
                }
                else
                {
                    cursor_x = _pluto_canvas.cwidth;
                }
                //printf("x:%iy:%i\n", cursor_x, cursor_y);
                break;
            case 'B':
                //printf("DOWN\n");
                if (cursor_x < _pluto_canvas.cwidth)
                {
                    cursor_x++;
                }
                else
                {
                    cursor_x = _pluto_canvas.cwidth;
                }
                //printf("x:%iy:%i\n", cursor_x, cursor_y);
                break;
            case 'C':
                //printf("RIGHT\n");
                if (cursor_y < _pluto_canvas.cheight)
                {
                    cursor_y++;
                }
                else
                {
                    cursor_y = 0;
                }
                //printf("x:%iy:%i\n", cursor_x, cursor_y);
                break;
            case 'D':
                //printf("LEFT\n");
                if (cursor_y > 0)
                {
                    cursor_y--;
                }
                else
                {
                    cursor_y = _pluto_canvas.cheight;
                }
                break;
            default:
                //printf("DUNNO\n");
                break;
            }
        }
        else if (key[0] == 'q' || key[0] == 'Q')
        {
            break;
        }
        else if (key[0] == 0)
        {
            continue;
        }
        pluto_set_pix(cursor_y, cursor_x);
        pluto_write_out();
        pluto_render();
        printf("\n\e[%i;%iH y: %i x: %i\n", _pluto_canvas.height + 1, _pluto_canvas.width, cursor_y, cursor_x);
    }
    handle_signal();
    return 0;
}
