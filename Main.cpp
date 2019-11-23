#include <Game.h>

extern short sDir;
bool gameOver = false;
int score = 0;

irrklang::ISoundEngine* soundengine = irrklang::createIrrKlangDevice();

void init()
{
	if (!soundengine)
		printf("[WARN] Error Starting SOUND engine!");
	soundengine->play2D("loop.wav", true);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	initGrid(COL, ROW);
}

int main(int ac, char **av)
{
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //rgba?
	glutInitWindowSize(500, 500);
	glutCreateWindow("Snake");
	glutDisplayFunc( display_cb );
	glutReshapeFunc( reshape_cb );
	glutTimerFunc(0, timer_cb, 0);
	glutSpecialFunc(keyboard_cb);
	init();
	glutMainLoop();
	soundengine->drop();
	return 0;
}

void display_cb()
{
	//draw double buffred bits
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	drawSnake();
	drawFood();
	glutSwapBuffers();
	if (gameOver)
	{
		printf("GAME OVER! SCORE: %d\n", score);
		exit(0);
	}
}

void reshape_cb(int x, int y)
{
	// Create a viewport of window size
	glViewport(0 ,0 ,x ,y);
	
	// create 40 x 40 grid
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // reset matrix
	glOrtho(0, COL , 0 , ROW , -1 , 1);
	glMatrixMode(GL_MODELVIEW);
}

void timer_cb(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, timer_cb, 0);
}

void keyboard_cb(int key,int,int)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (sDir != DOWN)
			sDir = UP;
		break;
	case GLUT_KEY_DOWN:
		if (sDir != UP)
			sDir = DOWN;
		break;
	case GLUT_KEY_RIGHT:
		if (sDir != LEFT)
			sDir = RIGHT;
		break;
	case GLUT_KEY_LEFT:
		if (sDir != RIGHT)
			sDir = LEFT;
		break;
	}
}