#include "../include/essFuncs.h"

// Take commands from the user
// 2 arguements, command to save and customshel to print
void takComm(char *comm, char *cusShel)
{
	if (cusShel == NULL || cusShel[0] == '\0') 
		printf("%s", ">> ");
	else
		printf("%s", cusShel);
	fgets(comm, BUF_SIZ, stdin); // getting the command from stdin

	if (comm[strlen(comm) - 1] == '\n') // removing the newline at the end of the command
		comm[strlen(comm) - 1] = '\0';

}

char **spComm(char *comm)
{
	int bufsiz = TOK_SIZ, pos = 0; // buffersize and position
	char **toks = malloc(bufsiz * sizeof(char *)); // creating an array of tokens
	char *tok;

	if (toks == NULL) { // Check if the allocation is successful
		fprintf(stderr, "Allocation failed\n");
		exit(EXIT_FAILURE);
	}

	// break into tokens
	tok = strtok(comm, TOK_DEL);
	while(tok != NULL) {
		toks[pos] = tok;
		pos++;

		// changing the bufsize if it is neccessary
		if (pos >= bufsiz) {
			bufsiz += TOK_SIZ;
			toks = realloc(toks, bufsiz * sizeof(char *));
			if (toks == NULL) { // Check if the allocation is successful
				fprintf(stderr, "Allocation failed\n");
				exit(EXIT_FAILURE);
			}
		}

		tok = strtok(NULL, TOK_DEL); // resuming the tokenization 
	}

	toks[pos] = NULL;
	return toks;
}

void execComm(char **comms)
{
	pid_t pid, wpid;
	int status;

	pid = fork();

	if (pid == 0) { // Child proccess
		if (execvp(comms[0], comms) == -1) { 
			perror("Can't run this child process");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) { // Error forking
		perror("Error forking");
	} else { // Parent proccess
		do {
			wpid = waitpid(pid, &status, WUNTRACED); // Wait untill child proccess finished	
		} while (!WIFEXITED(status) && !WIFSIGNALED(status)); // Until child exited or terminated
	}
}
