#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
// #include <stdio.h>

#define ERROR "error: fatal"

typedef struct  s
{
	int     	pipe_flag;
	int     	num_of_args;
	char    	**args;
	
	struct s	*prev;
	struct s	*next;
	
}               t_s;

void ft_putstr(char *s1, char *s2);
void ft_error();

// /usr/bin/grep
// /bin/ls
// ls ; ls | grep