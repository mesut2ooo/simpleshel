#ifndef ESSFUNCS_H
#define ESSFUNCS_H

#define BUF_SIZ 256 // The buffer size
#define TOK_SIZ 32 // Token size
#define TOK_DEL " \t\r\n\a" // Token delimiters

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void takComm(char *comm, char *CusShel); // printing and taking command by reading the whole line
char **spComm(char *comm); // splitting commands by taking one and returning an array
void execComm(char **comm); // executing the command
#endif
