#include "../minishell.h"

int	ft_echo(t_list *elem)
{
	int		i;
	int		j;
	int		flag_n;

	i = 0;
	flag_n = 0;
	if (!(ft_strncmp(elem->cmds[1], "-n", 2)))
	{
		flag_n = 1;
		i++;
	}
	while (elem->cmds[++i] != NULL)
	{
		ft_putstr_fd(elem->cmds[i], STDOUT_FILENO);
		if (elem->cmds[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!flag_n)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}



int	ft_cd(t_list *elem)
{

	char s[100];
    //Printing the current working directory
    printf("%s\n",getcwd(s,100));
    //Changing the current working directory to the previous directory
    chdir("..");
    //Printing the now current working directory
    printf("%s\n",getcwd(s,100));
	return (0);
}

int	ft_pwd(t_list *elem)
{
	char dir[MAXDIR];
	
	getcwd(dir, MAXDIR);
	printf("%s\n", dir);
	printf("commanda pwd\n");
	free(dir);
	return (0);
}

int	ft_export(void)
{
	printf("commanda export\n");
	return (0);
}

int	ft_unset(void)
{
	printf("commanda unset\n");
	return (0);
}

int	ft_env(void)
{
	printf("commanda env\n");
	return (0);
}

int	ft_exit(void)
{
	printf("commanda exit\n");
	return (0);
}