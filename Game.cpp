#include <Game.h>

//grid
int GridX ,GridY;
//food
bool food = true;
int FoodX, FoodY; 
//snake
int snake_len = 5;
short sDir = RIGHT;
int PosX[MAX] = {20, 20, 20, 20, 20};
int PosY[MAX] = {20,19,18,17,16};

//game
extern int score;
extern bool gameOver;
extern irrklang::ISoundEngine* soundengine;

void initGrid(int x, int y)
{
	GridX = x;
	GridY = y;
}

void drawGrid()
{
	for (int x = 0; x < GridX; x++)
	{
		for (int y = 0; y < GridY; y++)
		{
			unit(x,y);
		}
		
	}
}

void drawFood()
{
	if (food)
	{
		random(FoodX,FoodY);
		food = false;
	}
	glColor3f(1,0,0);
	glRectf(FoodX,FoodY, FoodX + 1, FoodY + 1);

}

void random(int &x, int &y)
{
	int _maxX = GridX-2;
	int _maxY = GridY-2;
	int _min = 1;
	srand(time(NULL));
	x = _min + rand() % (_maxX - _min);
	y = _min + rand() % (_maxY - _min);
}

void drawSnake()
{
	//Assign
	for (int i = snake_len - 1 ; i > 0 ; i --)
	{
		PosX[i] = PosX[i - 1];
		PosY[i] = PosY[i - 1];
	}
	if (sDir == UP)
		PosY[0]++;
	else if (sDir == DOWN)
		PosY[0]--;
	else if (sDir == RIGHT)
		PosX[0]++;
	else if (sDir == LEFT)
		PosX[0]--;
	//Draw
	for (int i=0; i < snake_len ;i++)
	{
		if (i == 0)
			glColor3f(0,1,0);
		else
			glColor3f(0,0,1);
		glRectd(PosX[i], PosY[i], PosX[i] +1, PosY[i] + 1);
	}

	//Game overs
	if ( PosX[0] == 0 || PosX[0] == GridX - 1 || PosY[0] == 0 || PosY[0] == GridY - 1)
		gameOver = true;
	for(int i = 1; i < snake_len; i++){
		if(PosX[i] == PosX[0] && PosY[i] == PosY[0]){
			gameOver = true;
		}
}
	// INC game score
	if ( PosX[0] == FoodX && PosY[0] == FoodY)
	{
		soundengine->play2D("eat.wav",false);
		score++;
		snake_len++;
		if (snake_len > MAX)
			snake_len = MAX;
		food = true;
	}
}

// draw simple square
void unit(int x, int y)
{
	if (x== 0 || y == 0 || x== GridX -1 || y == GridY - 1)
	{
		glLineWidth(3.0);
		glColor3f(1,0,0);
	}
	else 
	{
		glLineWidth(1.0);
		glColor3f(1,1,1);
	}
	glBegin(GL_LINE_LOOP); //first and last point will be connected
		glVertex2f(x,y);
		glVertex2f(x + 1, y);
		glVertex2f(x + 1, y + 1);
		glVertex2f(x , y + 1);
	glEnd();
}