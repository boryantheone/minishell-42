#include "../minishell.h"

int ft_symbol(char c)
{
	if ((c >= 33 && c <= 35) || (c >= 58 && c <= 62) ||\
		(c >= 91 && c <= 94) || (c >= 124 && c <= 126) \
		|| c == 64 || c == '\0' || (c >= 37 && c <= 47))
		return (1);
	else
		return (0);
}

char	*ft_parse_with_envp(char **str, int flag)
{
	char	*temp;
	char	temp_symbol;
	char	*result;
	char	*result1;
	int		i;

	i = 0;
	printf("22 str before replace %s\n", *str);
	temp = ++(*str);
	temp_symbol = 0;
	result = NULL;
	result1 = NULL;
	while (temp[i] && !ft_limiter(temp[i]))
		i++;
	if (i)
		result1 = ft_substr(temp, 0, i);
	else
		result1 = ft_strdup("\0");
	if (!ft_strncmp(result1, "?", 1))
		result = ft_itoa(var->state);
	else if (i == 0 && flag == 0)
	{
		result = ft_strdup("$");
//		temp[i] = temp_symbol;
//		temp += 1;
	}
	else if (i > 0 || (i == 0 && flag == 1))
	{
		printf("res %s\n", result);
		result = ft_strdup(ft_get_env(result1));
		printf("result %s\n", result);
//		temp[i] = temp_symbol;
//		temp += i;
	}
	if((ft_symbol(temp[i])))
		i++;
	*str = temp + i;
	free(result1);
	printf("2! str after replace env %s\n", *str);
	return (result);
}

char	*ft_get_env(char *key)
{
	t_envp	*tmp;
	
	tmp = var->envp;
	if (*key == '$')
		return ("88228");
	if (*key == '\0')
		return ("\0");
	while (tmp)
	{
		printf("|key %s|\n", key);
		if (!ft_strncmp(tmp->var, key, (ft_strlen(key))))
			return (tmp->val);
		tmp = tmp->next;
	}
	return ("\0");
}