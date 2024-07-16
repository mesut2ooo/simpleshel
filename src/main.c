#include "../include/essFuncs.h"

int main()
{
	char a[234], b[3];
	takComm(a, b);

	char **c;
	c = spComm(a);

	execComm(c);
}
