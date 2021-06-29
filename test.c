#include <stdio.h>
#include <pluto.h>
#include <unistd.h>

int main()
{
    pluto_init_window(); 
    pluto_save_screen();
    for (int i = 0; i < 101; i++) {
        pluto_set_pix(0, i);
        pluto_set_pix(i, 0);
        pluto_write_out();
        pluto_render();
    }
    sleep(30);
    pluto_deinit();
}