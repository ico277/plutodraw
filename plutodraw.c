#include <stdio.h>
#include <ncurses.h>
#include <pluto.h>

int main()
{
    mousemask(ALL_MOUSE_EVENTS, NULL);
    int c = getch();
    MEVENT event;
    while (true)
    {
        switch (c)
        {
        case KEY_MOUSE:
            if (getmouse(&event) == OK)
            {
                if (event.bstate & BUTTON1_PRESSED) // This works for left-click
                {
                    printf("left click\n");
                    break;
                }
                else if (event.bstate & BUTTON3_PRESSED) // This doesn't capture right-click
                {
                    printf("right click\n");
                    break;
                }
                else {
                    fprintf(stderr, "Event: %i", event.bstate); // Doesn't print anything on right-click
                    break;
                }
            } else {
                printf("there was an error\n");
                return 1;
            }
            break;
        default:
            break;
        }
    }
}