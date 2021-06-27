#include "header.h"

t_s *create_new_list(t_s *prev, int i, char **argv)
{
	int num_of_args;
	t_s *new;
	
	if ((new = (t_s *)malloc(sizeof(t_s))) == NULL)
		ft_error();
	new->pipe_flag = 0;
	new->prev = prev;
	new->next = NULL;
	
	num_of_args = 0;
	while (argv[i] && argv[i][0] != '|' && argv[i][0] != ';')
	{
		num_of_args++;
		i++;
	}
	new->num_of_args = num_of_args;
	if ((new->args = (char **)malloc(sizeof(char *) * (num_of_args + 1))) == NULL)
		ft_error();
	new->args[num_of_args] = NULL;

	if (prev)
		prev->next = new;
	
	return (new);
}

void get_args(char **argv, t_s *current)
{
	int i;
	int k;

	i = 1;
	k = 0;
	while (argv[i])
	{
		if (argv[i][0] == '|' || argv[i][0] == ';')
		{
			if (argv[i][0] == '|')
				current->pipe_flag = 1;
			if (argv[i + 1] == NULL)
				return ;
			current = create_new_list(current, ++i, argv);
			k = 0;
		}
		else
			current->args[k++] = argv[i++];
	}
}

void print_lists(t_s *head)
{
	int i;

	i = 0;
	while (head)
	{
		printf("pipe_flag %d\n", head->pipe_flag);
		printf("num_of_args %d\n", head->num_of_args);
		while (head->args[i])
			printf("%s ", head->args[i++]);
		i = 0;
		printf("\n");
		head = head->next;
	}
}

t_s *make_lists(char **argv)
{
	t_s *head;

	head = create_new_list(NULL, 1, argv);

	get_args(argv, head);
	return (head);
}

void ft_cd(t_s *list)
{
	if (list->num_of_args != 2)
		ft_putstr("error: cd: bad arguments", NULL);
	else if (chdir(list->args[1]) == -1)
	{
		ft_putstr("error: cd: cannot change directory to ", list->args[1]);
	}
}

void ft_execve(t_s *list, char **env)
{
	int status;
	pid_t child;

	if ((child = fork()) == 0)
	{
		if (execve(list->args[0], list->args, env) == -1)
			ft_putstr("error: cannot execute ", list->args[0]);
		exit(1);
	}
	else if (child == -1)
		ft_error();
	else
		waitpid(child, &status, 0);
}

void work_with_lists(t_s *current, char **env)
{
	int i = 0;
	int initial_0;
	int initial_1;
	int fd_pipe[2];

	if ((initial_0 = dup(0)) == -1)
		ft_error();
	if ((initial_1 = dup(1)) == -1)
		ft_error();
	while (current)
	{
		if (!current->prev && current->pipe_flag)
		{
			if (pipe(fd_pipe) == -1)
				ft_error();
			if (dup2(fd_pipe[1], 1) == -1)
				ft_error();
			close(fd_pipe[1]);
		}
		else if (current->prev && current->prev->pipe_flag && current->pipe_flag)
		{
			if (dup2(fd_pipe[0], 0) == -1)
				ft_error();
			close(fd_pipe[0]);
			
			if (pipe(fd_pipe) == -1)
				ft_error();
			if (dup2(fd_pipe[1], 1) == -1)
				ft_error();
			close(fd_pipe[1]);
		}
		else if (current->prev && current->prev->pipe_flag && !current->pipe_flag)
		{
			if (dup2(fd_pipe[0], 0) == -1)
				ft_error();
			close(fd_pipe[0]);
		}
		else if (current->prev && !current->prev->pipe_flag && current->pipe_flag)
		{
			if (pipe(fd_pipe) == -1)
				ft_error();
			if (dup2(fd_pipe[1], 1) == -1)
				ft_error();
			close(fd_pipe[1]);
		}
		if (current->num_of_args)
		{
			if (!strcmp(current->args[0], "cd"))
				ft_cd(current);
			else
				ft_execve(current, env);
		}
		if (dup2(initial_0, 0) == -1)
			ft_error();
		if (dup2(initial_1, 1) == -1)
			ft_error();
		current = current->next;
	}
	close(initial_0);
	close(initial_1);
}


int main(int argc, char **argv, char **env)
{
	t_s *head;

	if (argc == 0)
		return (0);
	head = make_lists(argv);
	// print_lists(head);
	work_with_lists(head, env);
	while (1)
	    ;
	return (0);
}
