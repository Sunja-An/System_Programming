#pragma once

#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <ncurses.h>

void Print_Success(WINDOW *scr, int page);
void Print_Delete(WINDOW *scr, int page, int n, int* input);