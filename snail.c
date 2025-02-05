#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

//SNAKE GAME
#define HEIGHT 20
#define WIDTH 40

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
void getKey() {
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
			printf("You clicked: %c\n", c);
		}
	}
}

//FUNCTION TO SPAWS APPLE
void spawnApple();

//FUNCTION TO SETUP GAME
void setup () {
	spawnApple();
}

//APPLE FUNCTION
void spawnApple () {
	int x = rand() % (WIDTH - 1) + 1;
	int y = rand() % (HEIGHT - 1)  + 1;
}

//FUNCTION TO CREATE MAP OF GAME
void createUI () {
	int matrix[HEIGHT][WIDTH];
	
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
			printf(" ");
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

	setup();
	
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
