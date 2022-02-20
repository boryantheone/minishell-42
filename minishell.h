#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft/libft.h"
 #include <fcntl.h>

#define MAXDIR 4096 //макс кол-во символов для названия пути

typedef struct s_envp
{
	char *var;
	char *val;
	struct s_envp *next;
} t_envp;

//struct for variables
typedef struct s_var
{
	char	**envp_for_execve;
	t_envp 	*envp;
	int		count_pipe;
	int		size_of_list;
	int		state; //состояние программы(сигнал ошибки мб или типа того)
} t_var;

int ft_exec_pipes(t_var *var, t_list *elem);
int	ft_exec_cmd(t_list *elem, t_var *var);
char	*ft_get_var_or_val_envp(char *str, int or);
int	ft_cd_change_pwd(char *new_pwd, char *prev_pwd, t_envp **env);
int	ft_cd_change_oldpwd(t_envp **env, char *prev_pwd);


//build_in
int	ft_echo(t_list *elem);
int	ft_cd(t_list *elem, t_var *var);
int	ft_pwd(t_list *elem);
int	ft_export(void);
int	ft_unset(void);
int	ft_env(t_list *elem, t_var *var);
int	ft_exit(void);


#endif 