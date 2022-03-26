
#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <signal.h>

# define MAXDIR 4096

typedef struct s_envp
{
	char			*var;
	char			*val;
	struct s_envp	*next;
}	t_envp;

//struct for variables
typedef struct s_var
{
	t_envp	*envp;
	t_envp	*export;
	int		state;
}	t_var;

typedef struct s_fds
{
	int				fd_in;
	int				fd_out;
	int				fd_heredoc;
	struct s_fds	*next;
}	t_fds;

t_var	*g_var;

void	ft_lstclear_fds(t_fds **lst);
void	ft_printlist_envp(t_envp *env);

//build_in3
int		ft_unset(t_list *elem);
int		ft_cd(t_list *elem);
//build_in2
int		ft_echo(t_list *elem);
int		ft_pwd(t_list *elem);
int		ft_exit(t_list *elem);
int		ft_env(t_list *elem);
int		ft_cd_change_oldpwd(t_envp **env, char *prev_pwd);
//build_in
int		ft_display_error(char *cmd, char *str);
int		ft_export(t_list *elem);
//preparser
int		ft_preparser(char *line);
//preparser_utils
int		ft_skip_space(const char *line, int *i);
int		ft_write_error(int flag);
//parser/parser - 5
t_list	*ft_parser(char *str);
char	*ft_parse_arguments(char **str);
//parser_quotes - 3
char	*ft_parse_single_quote(char **str);
char	*ft_parse_double_quote(char **str);
int		ft_add_in_result(char *result, char *temp, int i, int index);
//make_envp- 3
char	*ft_parse_with_envp(char **str, int flag);
char	*ft_get_env(char *key);
int		ft_lstsize_envp(t_envp *lst);
//new_env_list-5
char	*ft_get_var_or_val_envp(char *str, int or);
int		ft_make_env_list(char **env);
void	ft_lstadd_back_envp(t_envp **lst, t_envp *new);
t_envp	*ft_lstnew_env(char *str);
//parser_redirect - 5
void	ft_parser_redirect(char *str, t_fds *fds);
int		ft_perror(char *err_message, int return_value);
//new_fds_list
t_fds	*ft_fdsnew(int fd_read, int fd_write, int heredoc);
void	ft_fdsadd_back(t_fds **lst, t_fds *new);
char	*ft_replace_env(char *str);
//parser_fds
t_fds	*ft_parser_heredoc(char *str);

//parser_utils-5
char	*check_result(char *result, int index);
void	ft_free(char **dst);
int		ft_limiter(char c);
void	ft_skip_quotes(char **str);
void	ft_skip_redirect(char **str);
//parser_utils2-5
char	**ft_double_realloc(char **cmds, int size);
int		ft_str_double_len(char **cmds);//TODO:check str_doub_llen
int		ft_check_fds(t_fds *fds);
char	*ft_my_strjoin(char *s1, char *s2);
int		ft_perror_heredoc(char **stop, int flag);
//execute
void	ft_execute(t_list *elem, t_fds *fds);
//handler_cmd
int		ft_exec_buildin(t_list *elem);
char	**ft_new_envp_for_execve(void);

//handler_pipe
int		ft_exec_pipes(t_list *elem, t_fds *fds);
int		ft_exec_cmd(t_list *elem, t_fds *fds);
//checks
char	*ft_parsing_path(char *cmd, char **envp);
int		ft_is_a_directory(char *cmd);
void	ft_error_message_and_exit(int exit_status, char *cmd, int choice);
//signal
void	ft_init_signal_handler(void (*ft_handler)(int));
void	ft_handler_child(int sig);
void	ft_handler_main(int sig);
void	ft_handler_ctrl_d(void);
void	ft_handler_heredoc(int sig);
void	ft_handler_sigint(void);
//change fds
void	ft_dup_fd_in(int reserved_stdin, t_fds *fds);
void	ft_dup_fd_out(int reserved_stdout, t_fds **fds);
void	ft_dup_fd_in_out(t_fds **fds);
#endif 