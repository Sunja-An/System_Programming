#pragma once

#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

void Print_Success();
void Print_Failed();
void Print_Delete();

void Flag_Error(char *function_name);