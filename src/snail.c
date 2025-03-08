#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <pthread.h>

//SNAKE GAME
#define HEIGHT 20
#define WIDTH 40


//DEFINING ESCAPE KEY
#define KEY_ESCAPE  0x001b

int apple_x = 20, apple_y = 5;

char key;

int tailLen = 0;

int tailX[100], tailY[100];

char direction;

bool tailCol = false;

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
void* getKey(void* arg) {
	while (1)
	{
	usleep(100000);
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
					if (key == 'B')
					{
						c = 'B';
						break;
					}
					c = 'A';
					break;
				case('B'):
					if (key == 'A')
					{
						c = 'A';
						break;
					}
					c = 'B';
					break;
				case('C'):
					if (key == 'D')
					{
						c = 'D';
						break;
					}
					c = 'C';
					break;
				case('D'):
					if (key == 'C')
					{
						c = 'C';
						break;
					}
					c = 'D';
					break;
			}
		} else
		{
			c = ' ';
		}
	}
	key = c;
	}
}

void catchApple();

void addTale();

void logic() {
	switch(key) {
		case('A'):
			snail_Y--;
			addTale(snail_X, snail_Y + 1, tailX[tailLen - 1], tailY[tailLen - 1] - 1);
			break;
		case('B'):
			snail_Y++;
			addTale(snail_X, snail_Y - 1, tailX[tailLen - 1], tailY[tailLen - 1] + 1);
			break;
		case('D'):
			snail_X--;
			addTale(snail_X + 1, snail_Y, tailX[tailLen - 1] - 1, tailY[tailLen - 1]);
			break;
		case('C'):
			snail_X++;
			addTale(snail_X - 1, snail_Y, tailX[tailLen - 1] + 1, tailY[tailLen - 1]);
			break;
	}

	if(snail_Y == apple_y && snail_X == apple_x)
	{
		catchApple();
	}

	for (int i = 0; i < tailLen; i++)
	{
		if(snail_X == tailX[i] && snail_Y == tailY[i]) {
			tailCol = true;
		}
	}
}

void addTale(int x, int y) {
	if (apple_x == snail_X && apple_y == snail_Y) {
		tailLen++;
	}

	for (int i = tailLen - 1; i >= 0; i--)
	{
		if(i == 0)
		{
			tailX[i] = x;
			tailY[i] = y;
		}else 
		{
			tailX[i] = tailX[i - 1];
			tailY[i] = tailY[i - 1];
		}
	}
}

void catchApple() {
	//DEFINING RANDOM X AND Y TO SPAWN FRUIT
	apple_x = rand() % (WIDTH - 1);
	apple_y = rand() % (HEIGHT - 1);
	if (apple_x == 0 || apple_y == 0){
		catchApple();
	}
	for(int i = 0; i <= tailLen; i++)
	{
		if(tailX[i] == apple_x && tailY[i] == apple_y) {
			catchApple();
			break;
		}
	}
}

//FUNCTION TO CREATE MAP OF GAME
void createUI () {
	//SPAWNING APPLE IN DIFFRENT LOCATION WHEN SNAI TOUCHES IT
	int oneTimeX = 50;
	int oneTimeY = 50;

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
			for(int p = 0; p < tailLen; p++)
			{
				if(tailLen == 0){
					break;
				}else if (tailX[p] == j && tailY[p] == i) {	
					oneTimeX = tailX[p];
					oneTimeY = tailY[p];
				}
			}
			if (j == apple_x && i == apple_y) {
				printf("*");
			}else if(i == snail_Y && j == snail_X) {
				printf("O");
			}else if(oneTimeX == j && oneTimeY == i) {	
				//printf("%d %d", j, i);
				printf("o");
			}else  {
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
	oneTimeX = 50;
	oneTimeY = 50;
}

//MAIN FUNCTION
int main() {
	pthread_t thread_id;

	//CLEARING TMINAL
	system("clear");
	//CALLING SET TERMIOS FUNCTION
	setTermios();

	pthread_create(&thread_id, NULL, getKey, NULL);
	
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
		logic();
		if (tailCol == true) {
			break;
		}
		usleep(100000);
	} 

	//SETTING TERMIOS TO ORIGINAL SETTINGS OR FLAGS
	tcsetattr(STDIN_FILENO, TCSANOW, &original);

	return 1;
}
