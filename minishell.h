#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

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
	t_envp	*export;
	int		count_pipe;
	int		size_of_list;
	int		state; //состояние программы(сигнал ошибки мб или типа того)
} t_var;

int ft_exec_pipes(t_var *var, t_list *elem);
int	ft_exec_cmd(t_list *elem, t_var *var);
char	*ft_get_var_or_val_envp(char *str, int or);
int	ft_cd_change_pwd(char *new_pwd, char *prev_pwd, t_envp **env);
int	ft_cd_change_oldpwd(t_envp **env, char *prev_pwd);
void ft_printlist_envp(t_envp *env);
void	ft_lstadd_back_envp(t_envp **lst, t_envp *new);
t_envp	*ft_lstnew_env(char *str);
int	ft_strcmp(const char *s1, const char *s2);
void ft_lstdelone_envp(t_var *var, t_list *elem, int j, int index);

//main/main
void ft_error(void);
//main/preparser
int ft_preparser(char *line);


//build_in
int	ft_echo(t_list *elem);
int	ft_cd(t_list *elem, t_var *var);
int	ft_pwd(t_list *elem);
int ft_export(t_list *elem, t_var *var);
int ft_unset(t_var *var, t_list *elem);
int	ft_env(t_list *elem, t_var *var);
int	ft_exit(t_list *elem);

//preparser
int	ft_preparser(char *line);
int	ft_skip_space(char *line);
//parser
void    ft_parser(char *str, t_list *arguments);

#endif 