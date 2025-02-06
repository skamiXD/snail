#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

//SNAKE GAME
#define HEIGHT 20
#define WIDTH 40

//DEFINING ESCAPE KEY
#define KEY_ESCAPE  0x001b

//CREATING STUCTURE TERMIOS
struct termios original, changed;

//FUNCTION TO CHANGE TERMIOS FLAGS
void setTermios(){
	//GETTING ORIGINAL FLAGS
	tcgetattr(STDIN_FILENO, &original);
	//COPYING ORIGINAL FLAGS
	changed = original;
	
	//TURN OFF CANONICAL MODE
	changed.c_lflag &= ~ICANON;
	changed.c_lflag &= ~ECHO;

	//SETTING FLAGS TO MODIFIED FLAGS
	tcsetattr(STDIN_FILENO, TCSANOW, &changed);
}

//FUNCTION TO GET ARROW KEYS
char getKey() {
	char c;
	c = getchar();
	if (c == KEY_ESCAPE)
	{	
		c = getchar();
		if (c == '[')
		{
			switch(getchar())
			{
				case('A'):
					c = 'A';
					break;
				case('B'):
					c = 'B';
					break;
				case('C'):
					c = 'C';
					break;
				case('D'):
					c = 'D';
					break;
			}
		} else
		{
			c = ' ';
		}
	}
	return c;
}

//FUNCTION TO CREATE MAP OF GAME
void createUI () {
	//DEFINING RANDOM X AND Y TO SPAWN FRUIT
	int apple_x = rand() % (WIDTH - 1) + 1;
	int apple_y = rand() % (HEIGHT - 1) + 1;
	
	//FOR A TOP WALL
	for (int i = 0; i <= WIDTH; i++)
	{
		printf("-");
	}
	printf("\n");
	for (int i = 0; i <= HEIGHT; i++)
	{
		printf("#");
		for (int j = 0; j <= WIDTH - 2; j++)
		{
			if (j == apple_x && i == apple_y)
			{
				printf("*");
			}else {

			printf(" ");
			}
		}
		printf("#\n");
	}

	for (int i = 0; i <= WIDTH; i++)
	{
		printf("-");
	}
}

//MAIN FUNCTION
int main() {
	//CLEARING TERMINAL
	system("clear");
	//CALLING SET TERMIOS FUNCTION
	setTermios();
	int snake_health = 3;
	bool Horizontal = true;
	//CALLING FUNCTION TO CREATE UI
	createUI();
	
	//CALLING GET ARROW KEYS FUNCTION IN WHILE LOOP TO LISTEN TO IT EVERY SECOND
	while (1)
	{
		getKey();
	}

	//FUNCTIN TO CREATE SNAKE (PROBABLY WILL CAHNGE)
	for (int i = 0; i <= snake_health; i++)
	{
		if (i == snake_health)
		{
			printf(">");
		}
		else
		{
			printf("=");
		}
	}

	//SETTING TERMIOS TO ORIGINAL SETTINGS OR FLAGS
	tcsetattr(STDIN_FILENO, TCSANOW, &original);

	return 1;
}
