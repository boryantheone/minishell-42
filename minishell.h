#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft/libft.h"

//struct for pipes
typedef struct s_pipe
{
	int	count_pipe;
	int	fd_close;
	int	fd_open;
} t_pipe;

//struct for variables
typedef struct s_var
{
	char 	**envp;
	t_list	*elem;
	int		count_pipe;
	int		size_of_list;
} t_var;

void ft_load_cmds(t_var *elem);


#endif 