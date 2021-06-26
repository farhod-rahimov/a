#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

#define ERROR "error: fatal"

typedef struct  s
{
	int     	pipe_flag;
	int     	num_of_args;
	char    	**args;
	
	struct s	*prev;
	struct s	*next;
	
}               t_s;

void ft_putstr(char *s1, char *s2, int fd);
void ft_error();

// error: cannot execute 
// error: cd: bad arguments
// error: cd: cannot change directory to