
#include "../minishell.h"

int	ft_symbol(char c)
{
	if ((c >= 33 && c <= 35) || c == 60 || c == 62 || \
		(c >= 91 && c <= 94) || (c >= 124 && c <= 126) \
		|| c == 64 || (c >= 40 && c <= 41))
		return (1);
	else
		return (0);
}

char	*ft_parse_with_envp(char **str, int flag)
{
	char	*temp;
	char	temp_symbol;
	char	*result;
	int		i;
	int		len;

	i = 0;
	temp = ++(*str);
	result = NULL;
	while (temp[i] && !ft_limiter(temp[i]))
		i++;
	temp_symbol = temp[i];
	temp[i] = 0;
	if (!ft_strncmp(temp, "?", 1))
		result = ft_itoa(g_var->state);
	else if (i == 0 && flag == 0)
	{
		result = ft_strdup("$");
		i++;
	}
	else if (i > 0)
		result = ft_strdup(ft_get_env(temp));
	len = (int)ft_strlen(temp);
	temp[i] = temp_symbol;
	if ((ft_symbol(temp[i])) && len <= 2)
		i++;
	*str = temp + i;
	return (result);
}

char	*ft_get_env(char *key)
{
	t_envp	*tmp;

	tmp = g_var->envp;
	if (*key == '$')
		return ("88228");
	if (*key == '\0')
		return ("\0");
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, key, (ft_strlen(key))))
			return (tmp->val);
		tmp = tmp->next;
	}
	return ("\0");
}

int	ft_lstsize_envp(t_envp *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		i++;
		lst = lst -> next;
	}
	return (i);
}