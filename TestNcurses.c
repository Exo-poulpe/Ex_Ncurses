#include <ncurses.h>
#include <string.h>
#include <stdio.h>

#define WIDTH 30
#define HEIGHT 10

char *choices[] = {
    "poulpe1",
    "poulpe2",
    "poulpe3",
    "poulpe4",

};




int n_choices = sizeof(choices) / sizeof(char *);


void print_menu(WINDOW *menu_win, int highlight);

int main(void) {

    int MaxX=0,MaxY=0,x=0,y=0;
    int highlight = 1;
    int choice = 0;
    int ch = 0;
    int startx = (80 - WIDTH) / 2;
    int starty = (24 - HEIGHT) / 2;



    initscr();
    cbreak();
    noecho();
    getmaxyx(stdscr,MaxY,MaxY);

    WINDOW *win = newwin(HEIGHT, WIDTH, starty, startx);
    box(win,0,0);

    keypad(win, TRUE);

    refresh();




    curs_set(true);

    print_menu(win, highlight);
    /*mvwprintw(win, MaxY/4,MaxX/4 , "r - Run");
    mvwprintw(win, MaxY/4-1,MaxX/4 , "poulpw");
    mvwprintw(win, MaxY/4-1,MaxX/4  , "poulpe");
    mvwprintw(win, MaxY/4-1,MaxX/4 , "salut");
    wrefresh(win);*/
    while(1) {
        //clear();
        //printw("poulpe");

        //wrefresh(win);
        ch = wgetch(win);
        switch(ch) {
        case KEY_UP:
            if(highlight == 1)
                highlight = n_choices;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if(highlight == n_choices)
                highlight = 1;
            else
                ++highlight;
            break;
        case 10:
            choice = highlight;
            break;
        default:
            mvprintw(24, 0, "Char pressed is = %3d Hopefully it can be printed as '%c'", ch, ch);
            refresh();
            break;
        }
        print_menu(win, highlight);
        if(choice != 0 || ch == 'q') {
            break;
        }

    }

    clrtoeol();
    refresh();
    endwin();
    return 0;

}


void print_menu(WINDOW *menu_win, int highlight) {
    int x, y, i;

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(i = 0; i < n_choices; ++i) {
        if(highlight == i + 1) { /* High light the present choice */
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }
        ++y;
    }
    wrefresh(menu_win);
}

