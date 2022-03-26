/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:48:37 by jcollin           #+#    #+#             */
/*   Updated: 2022/03/26 15:48:39 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_symbol(char c)
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
	temp[i] = temp_symbol;
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
