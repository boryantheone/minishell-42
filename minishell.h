#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft/libft.h"
 #include <fcntl.h>

#define MAXDIR 4096

//struct for variables
typedef struct s_var
{
	char 	**envp;
	int		count_pipe;
	int		size_of_list;
} t_var;

int ft_exec_pipes(t_var *var, t_list *elem);
int	ft_exec_cmd(t_list *elem, t_var *var);

//build_in
int	ft_echo(t_list *elem);
int	ft_cd(t_list *elem);
int	ft_pwd(t_list *elem);
int	ft_export(void);
int	ft_unset(void);
int	ft_env(void);
int	ft_exit(void);


#endif 