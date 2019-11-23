#ifndef GAME_H
# define GAME_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <ctime>
#include <irrKlang.h>

# define COL	40
# define ROW	40
# define FPS	20

# define UP		1
# define DOWN	-1
# define RIGHT	2
# define LEFT	-2
# define MAX	60

void	display_cb();
void	reshape_cb(int x, int y);
void	timer_cb(int time);
void	keyboard_cb(int,int,int);
void	initGrid(int x, int y);
void	drawGrid();
void	unit(int x, int y);
void	drawSnake();
void	random(int &x, int &y);
void	drawFood();

#endif