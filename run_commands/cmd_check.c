/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:52:03 by jcollin           #+#    #+#             */
/*   Updated: 2022/03/25 16:12:08 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_a_directory(char *cmd)
{
	struct stat	dir;

	stat(cmd, &dir);
	return (S_ISDIR(dir.st_mode));
}

void	ft_error_message_and_exit(int exit_status, char *cmd, int choice)
{
	ft_putstr_fd("minishelchik: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (choice == 0)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (choice == 1)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	g_var->state = exit_status;
	exit(g_var->state);
}

char	*ft_parsing_help(char *cmd, char *envp)
{
	int		i;
	char	**paths;
	char	*cmdpath;
	char	*path;

	path = envp;
	i = 0;
	paths = ft_split(path + 5, ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmdpath = ft_strjoin(path, cmd);
		free(path);
		if (access(cmdpath, R_OK) == 0)
		{
			ft_free(paths);
			return (cmdpath);
		}
		free(cmdpath);
		i++;
	}
	ft_free(paths);
	return ("command not found");
}

char	*ft_parsing_path(char *cmd, char **envp)
{
	int	i;

	i = 0;
	if (cmd == NULL || ft_strchr(cmd, '/') != 0)
		return (cmd);
	while (envp[i] && envp[i] != ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if ((ft_strnstr(envp[i], "PATH=", 5)) == NULL)
		return ("command not found");
	return (ft_parsing_help(cmd, envp[i]));
}
