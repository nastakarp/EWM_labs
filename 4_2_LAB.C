#include <stdio.h>
#include <conio.h>
#include <bios.h>
#include <dos.h>

#define ESCAPE 27 //объявление константы ESCAPE, которая соответствует ASCII-коду клавиши "Esc" (27).

#define UP 72
#define DOWN 80

#define LEFT 75
#define RIGHT 77

#define X1 15
#define X2 65
#define Y1 10
#define Y2 20

int keypressed(){ // проверяет, была ли нажата клавиша.
	union REGS r;
	r.h.ah = 0x0B; // запись значения 0x0B (функция DOS, которая проверяет ввод с клавиатуры) в старший байт регистра ah.
	int86(0x21, &r, &r); //вызов DOS-прерывания 0x21, которое обрабатывает системные функции.
	return r.h.al; // возврат значения регистра al (младшего байта), которое указывает, была ли нажата клавиша.
	               //Если клавиша была нажата, это значение будет ненулевым.
}

int getKey(){ //возвращает целое значение (код нажатой клавиши).
	union REGS r;
	r.h.ah = 0x7;
                    /*установка значения регистра ah на 0x7.
                    Это код функции BIOS для "ввода символа с клавиатуры" (без эха на экран),
                    которая ожидает нажатие клавиши и возвращает её код.
                    Эхо — это автоматическое отображение нажатой клавиши в консоль.*/
	int86(0x16, &r, &r); //прерывание 0x16 для работы с клавиатурой.
	return r.h.al; //возврат значения из регистра al, который содержит код нажатой клавиши.
}

int main(){
	int x, y, ch; //ch — переменная для хранения кода нажатой клавиши.
	x = y = 1;
	window(X1, Y1, X2, Y2); //размеры окна
	textbackground(7); // установка фона текста
	textcolor(4); //установка цвета текста
	_setcursortype(_NOCURSOR); //отключение видимости курсора
	gotoxy(x, y); //перемещение курсора в координаты (x, y).
	clrscr(); //очистка экрана.
	printf("*");
	gotoxy(x, y);
	do {
		ch = getKey(); //Программа ожидает нажатие клавиши, считывая её код через функцию getKey()
		if (ch == 0 || ch == 224) { //проверка на то, была ли нажата функциональная клавиша (клавиши-стрелки возвращают такие коды).
			switch (getKey()) {
			case DOWN:
				clrscr();
				if (y <= (Y2 - Y1)) {
					y++;
					gotoxy(x, y);
					printf("*");
					gotoxy(x, y);
				}
				else {
					y = 1;
					gotoxy(x, y);
					printf("*");
					gotoxy(x, y);
				}
				break;
			case UP:
				clrscr();
				if (y - 1 >= 1) {
					y--;
					gotoxy(x, y);
					printf("*");
					gotoxy(x, y);
				}
				else {
					y = Y2 - Y1 + 1;
					gotoxy(x, y);
					printf("*");
					gotoxy(x, y);
				}
				break;
			case LEFT:
				clrscr();
				if (x - 1 >= 1) {
					x--;
					gotoxy(x, y);
					printf("*");
					gotoxy(x, y);
				}
				else {
					x = X2 - X1 + 1;
					gotoxy(x, y);
					printf("*");
					gotoxy(x, y);
				}
				break;
			case RIGHT:
				clrscr();
				if (x + 1 <= (X2 - X1) + 1) {
					x++;
					gotoxy(x, y);
					printf("*");
					gotoxy(x, y);
				}
				else {
					x = 1;
					gotoxy(x, y);
					printf("*");
					gotoxy(x, y);
				}
				break;
			}
		}
	} while (ch != ESCAPE); // программа продолжает работать, пока не будет нажата клавиша Esc

	return 0;
}
