#include "../minishell.h"

char *ft_parse_with_envp(char **str)
{
	char	*temp;
	char	*result;
	int 	i;
	
	i = 0;
	temp = ++(*str);
	while (temp[i] && temp[i] != ' ')
		i++;
	if (!ft_strncmp(temp, "?", i))
		result = ft_itoa(var->state);
	else if (!i)
		result = ft_strdup("$");
	else
		result = ft_strdup(ft_get_env(temp));
	temp += i;
	*str = temp;
	return (result);
}

char *ft_get_env(char *key)
{
	while (var->envp)
	{
		if (!ft_strncmp(var->envp->var, key, ft_strlen(key)))
			return (var->envp->val);
		var->envp = var->envp->next;
	}
	return (NULL);
	
}