#include <stdio.h>
#include <conio.h>
#include <dos.h>


void scroll(int direction, char l_row, char l_col,
		char r_row, char r_col, char attr)
{
	union REGS r;

	if (direction)
	{
		r.h.al = 1;
		r.h.ah = direction;
		} else {
		r.h.al = 0;
		r.h.ah = 7;
	}
	r.h.ch = l_row;
	r.h.cl = l_col;
	r.h.dh = r_row;
	r.h.dl = r_col;
	r.h.bh = attr;

	int86(0x10, &r, &r);
}


void show_col(int bg_col, int text_col)
{
	switch (bg_col)
	{
		case 0: cprintf("BG: 0"); break;
		case 1: cprintf("BG: 1"); break;
		case 2: cprintf("BG: 2"); break;
		case 3: cprintf("BG: 3"); break;
		case 4: cprintf("BG: 4"); break;
		case 5: cprintf("BG: 5"); break;
		case 6: cprintf("BG: 6"); break;
		case 7: cprintf("BG: 7"); break;
	}

	cprintf(" ");

	switch (text_col)
	{
		case 0: cprintf(" Txt=BLACK"); break;
        case 1: cprintf(" Txt=BLUE");  break;
        case 2: cprintf(" Txt=GREEN"); break;
        case 3: cprintf(" Txt=CYAN");  break;
        case 4: cprintf(" Txt=RED"); break;
        case 5: cprintf(" Txt=MAGENTA"); break;
        case 6: cprintf(" Txt=BROWN");  break;
        case 7: cprintf(" Txt=LIGHTGRAY"); break;
        case 8: cprintf(" Txt=DARKGRAY");  break;
        case 9: cprintf(" Txt=LIGHTBLUE"); break;
        case 10: cprintf(" Txt=LIGHTGREEN"); break;
        case 11: cprintf(" Txt=LIGHTCYAN");  break;
        case 12: cprintf(" Txt=LIGHTRED");   break;
        case 13: cprintf(" Txt=LIGHTMAGENTA"); break;
        case 14: cprintf(" Txt=YELLOW");  break;
        case 15: cprintf(" Txt=WHITE");   break;
	}
}

int main()
{
    int bg_col;
	int text_col;
	int DOWN;
	int j;
	int k;
	clrscr();
	window(15, 10, 65, 20);

    bg_col = 0;
	text_col = 15;
	DOWN = 7;

	for ( j= 0; j < 8; j++) {
		text_col = 15;
		for (k = 0; k < 16; k++)
		{
		    scroll(DOWN, 10, 15, 20, 65, bg_col << 4);
		    gotoxy(2, 2);
		    textbackground(bg_col);
		    textcolor(text_col);
		    show_col(bg_col, text_col);
		    text_col--;
		    delay(200);
		}
		bg_col++	;
	}
	getch();
	return 0;
}