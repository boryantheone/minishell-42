#include "../minishell.h"

char	*ft_parse_with_envp(char **str)
{
	char	*temp;
	char	temp_symbol;
	char	*result;
	int		i;

	i = 0;
	temp = ++(*str);
	result = NULL;
	while (temp[i] && ft_limiter(temp[i]))
		i++;
	temp_symbol = temp[i];
	temp[i] = 0;
	if (!ft_strncmp(temp, "?", 1))
	{
		result = ft_itoa(var->state);
		temp[i] = temp_symbol;
		temp += 1;
	}
	else if (i == 0)
		result = ft_strdup("$");
	else if (i > 0)
	{
		result = ft_strdup(ft_get_env(temp));
		temp[i] = temp_symbol;
		temp += i;
	}
	*str = temp;
	return (result);
}

char	*ft_get_env(char *key)
{
	if (*key == '$')
		return ("88228");
	while (var->envp)
	{
		if (!ft_strncmp(var->envp->var, key, (ft_strlen(key) - 1)))
			return (var->envp->val);
		var->envp = var->envp->next;
	}
	return ("\0");
}