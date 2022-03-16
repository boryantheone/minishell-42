#include "../minishell.h"

char	*ft_parse_with_envp(char **str, int flag)
{
	char	*temp;
	char	temp_symbol;
	char	*result;
	int		i;

	i = 0;
	temp = ++(*str);
	temp_symbol = 0;
	result = NULL;
	while (temp[i] && !ft_limiter(temp[i]))
		i++;
	printf("temp_ ii %d\n", i);
	if (temp[i])
		temp_symbol = temp[i];
	printf("temp_symbol %c\n", temp_symbol);
	temp[i] = 0;
	if (!ft_strncmp(temp, "?", 1))
	{
		result = ft_itoa(var->state);
		temp[i] = temp_symbol;
		temp += 1;
	}
	else if (i == 0 && flag == 0)
	{
		result = ft_strdup("$");
//		temp[i] = temp_symbol;
//		temp += 1;
	}
	else if (i > 0)
	{
		printf("res %s\n", result);
		result = ft_strdup(ft_get_env(temp));
		temp[i] = temp_symbol;
		temp += i;
	}
	*str = temp;
	printf("2! str after replace env %s\n", str);
	return (result);
}

char	*ft_get_env(char *key)
{
//	if (*key == '$')
//		return ("88228");
	while (var->envp)
	{
		if (!ft_strncmp(var->envp->var, key, (ft_strlen(key) - 1)))
			return (var->envp->val);
		var->envp = var->envp->next;
	}
	return ("\0");
}