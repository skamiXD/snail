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

int apple_x = 20, apple_y = 5;

int tailLen;

char direction;

int snail_X = WIDTH/2, snail_Y = HEIGHT/2;

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

void logic(char key) {
	switch(key) {
		case('A'):
			snail_Y--;
			break;
		case('B'):
			snail_Y++;
			break;
		case('D'):
			snail_X--;
			break;
		case('C'):
			snail_X++;
			break;
	}
}

void catchApple() {
	//DEFINING RANDOM X AND Y TO SPAWN FRUIT
	apple_x = rand() % (WIDTH - 1);
	apple_y = rand() % (HEIGHT - 1);
	if (apple_x == 0 || apple_y == 0){
		catchApple();
	}
	tailLen++;
}

//FUNCTION TO CREATE MAP OF GAME
void createUI () {
	//SPAWNING APPLE IN DIFFRENT LOCATION WHEN SNAI TOUCHES IT
	if(snail_Y == apple_y && snail_X == apple_x)
	{
		catchApple();
	}

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
			}else if(i == snail_Y && j == snail_X) {
				printf("O");
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
	printf("\n");
}

//MAIN FUNCTION
int main() {
	//CLEARING TERMINAL
	system("clear");
	//CALLING SET TERMIOS FUNCTION
	setTermios();
	
	char key;

	//CALLING GET ARROW KEYS FUNCTION IN WHILE LOOP TO LISTEN TO IT EVERY SECOND
	while (1)
	{	
		system("clear");
		//CALLING FUNCTION TO CREATE UI
		createUI();
		//ENING GAME WHEN COLLISION WITH WALLS HAPPEN
		if(snail_X == -1 || snail_X == WIDTH - 1 || snail_Y == -1 || snail_Y == HEIGHT + 1)
		{
			printf("game over");
			break;
		}
		//sleep(1);
		logic(getchar());
	} 

	//SETTING TERMIOS TO ORIGINAL SETTINGS OR FLAGS
	tcsetattr(STDIN_FILENO, TCSANOW, &original);

	return 1;
}
