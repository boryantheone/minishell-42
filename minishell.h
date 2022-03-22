#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

#define MAXDIR 4096 //макс кол-во символов для названия пути

typedef struct s_envp
{
	char *var;
	char *val;
	struct s_envp *next;
}	t_envp;


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

typedef struct s_fds
{
	int				fd_in;
	int				fd_out;
	int 			fd_heredoc;
	struct s_fds	*next;
}	t_fds;

t_var *var;

char	*ft_get_var_or_val_envp(char *str, int or);
int		ft_cd_change_pwd(char *new_pwd, char *prev_pwd, t_envp **env);
int		ft_cd_change_oldpwd(t_envp **env, char *prev_pwd);
void	ft_printlist_envp(t_envp *env);
void	ft_lstadd_back_envp(t_envp **lst, t_envp *new);
t_envp	*ft_lstnew_env(char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_lstdelone_envp(t_var *var, t_list *elem, int j, int index);

//execute 
char	*ft_parsing_path(char *cmd, char **envp);
void	ft_execute(t_var *var, t_list *elem, t_fds *fds);
int		ft_exec_pipes(t_var *var, t_list *elem, t_fds *fds);
int		ft_exec_cmd(t_list *elem, t_var *var, t_fds *fds);
//handler_cmd
int		ft_exec_buildin(t_list *elem, t_var *var);
char	**ft_new_envp_for_execve(void);
int		ft_lstsize_envp(t_envp *lst);
//handler_pipe
void	ft_free(char **dst);
//main/main
void	ft_error(void);

//build_in3
int		ft_unset(t_var *var, t_list *elem);
//build_in2
int		ft_echo(t_list *elem);
int		ft_pwd(t_list *elem);
int		ft_exit(t_list *elem);
int		ft_env(t_list *elem, t_var *var);
//build_in
int		ft_display_error(char *cmd, char *str);
int		ft_cd(t_list *elem, t_var *var);
int 	ft_export(t_list *elem, t_var *var);
//preparser
int		ft_preparser(char *line);
int		ft_skip_space(char *line);
//parser
t_list	*ft_parser(char *str);
char	*ft_parse_arguments(char **str);
int	ft_str_double_len(char **cmds);
void ft_printlist(t_list *elem);
char	*ft_strcpy(char *dest, char *src);
char	*ft_get_var_or_val_envp(char *str, int or);
void	*ft_realloc(char *result, int size);
//parser_quotes
char *ft_parse_single_quote(char **str);
char *ft_parse_double_quote(char **str);
int		ft_add_in_result(char *result, char *temp, int i, int index);
char	*ft_strndup(char *src, int len);
//make_envp
char *ft_parse_with_envp(char **str, int flag);
char *ft_get_env(char *key);
//parser_redirect
int		ft_forward_redirect(char **str);
int		ft_reverse_redirect(char **str, t_fds *fds);
void	ft_parser_redirect(char *str, t_fds *fds);
//parser_fds
t_fds	*ft_parser_heredoc(char *str);
int ft_limiter(char c);
//utils
void ft_skip_quotes(char **str);
void	ft_skip_redirect(char **str);
void ft_printfds(t_fds *elem);

//checks
int	ft_check_fds(t_fds *fds);
int	ft_perror(char *err_message, int return_value);
int	ft_is_a_directory(char *cmd);
void	ft_error_message_and_exit(int exit_status, char *cmd, int choice);
#endif 