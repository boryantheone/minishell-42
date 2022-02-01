#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>


//struct for variables
typedef struct s_var
{
	char	**cmd;  //commands
	int		**fdp;	//fd for pipe
	int		*fdr;	//fd for redirect
} t_var;


#endif 