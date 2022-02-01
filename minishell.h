#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft/libft.h"

//struct for variables
typedef struct s_var
{
	char 	**envp;
	t_list	*elem;
} t_var;

void ft_load_cmds(t_var *elem);


#endif 