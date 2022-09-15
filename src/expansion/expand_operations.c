/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:42:22 by kamin             #+#    #+#             */
/*   Updated: 2022/09/14 22:07:53 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	to_expand(char c)
{
	int			ret;
	static int	dq;
	static int	sq;
	static int	first;

	ret = 0;
	if (first == 0 && (c == '"' || c == '\''))
		first = c;
	else if (first != 0 && (char)first == c)
		first = 0;
	if (first != '\'' && !check_char(c, &dq, &sq)
		&& ((c == '$' && dq == 1)
			|| (c == '$' && sq == 0 && dq == 0)))
			ret = 1;
	return (ret);
}

char	*get_variable_name(void *cmd, int flag)
{
	int		i;
	char	*var;
	char	*string;

	i = 0;
	string = *select_string(cmd, flag);
	if (!string)
		return (NULL);
	while (string[i] != '\0' && string[i] != '$')
		i++;
	if (string[i] == '\0')
		return (NULL);
	var = ft_substr(string + i + 1, 0, stopper_finder(string + i + 1));
	return (var);
}

char	*combined(char *tok, char *val, char *var)
{
	ssize_t	tok_i;
	int		i;
	char	*com;

	i = -1;
	tok_i = 0;
	com = (char *)ft_calloc((calc_malloc_size(tok, var, val) + 1), 1);
	i = cpy_sec(i, &com, tok, '$');
	i = cpy_sec(i, &com, val, '\0');
	if (i < 0)
		i = 0;
	tok_i += ft_strlen(var) + i + 1 - ft_strlen(val);
	if (tok_i < (ssize_t)ft_strlen(tok))
		i = cpy_sec(i, &com, tok + tok_i, '\0');
	com[i] = '\0';
	return (com);
}

int	expansion_free(char **string, char **tmp, char **var, char **env)
{
	if (tmp != NULL)
	{
		free(*string);
		*string = ft_strdup(*tmp);
	}
	if (*var != NULL && *env != NULL && ft_strcmp(*var, ""))
	{
		free(*tmp);
		free(*var);
		if (!ft_strcmp(*env, ""))
			free(*env);
		return (0);
	}
	return (1);
}
