/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:42:22 by kamin             #+#    #+#             */
/*   Updated: 2022/09/17 16:12:45 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	to_expand(char c, char next)
{
	int			ret;
	static int	dq;
	static int	sq;
	static int	first;

	ret = 0;
	if (c == '\0')
	{
		dq = 0;
		sq = 0;
		first = 0;
		return (ret);
	}
	if (first == 0 && (c == '"' || c == '\''))
		first = c;
	else if (first != 0 && (char)first == c)
		first = 0;
	if (!check_char(c, &dq, &sq) && first != '\''
		&& ((c == '$' && dq == 1 && !ft_strchr("=+)(^%\"\'\0",next))
			|| (c == '$' && !sq && !dq && !ft_strchr("=+)(^%\"\'\0",next))))
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

char	*combined(char *tok, char *val, char *var, int *index)
{
	ssize_t	tok_i;
	int		i;
	char	*com;
	// const int	quotes = stopper_finder(tok);

	i = -1;
	tok_i = 0;
	(void)index;
	com = (char *)ft_calloc((calc_malloc_size(tok, var, val) + 1), 1);
	while (++i < *index)
		com[i] = tok[i];
	// i += cpy_sec(i, &com, tok + *index, '$');
	// if (ft_strchr("\"\'\0",tok[*index + 1]))
	// {
	// 	com[i] = tok[*index];
	// 	i++;
	// 	(*index)++;
	// }
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
		if(!ft_strcmp(*tmp, ""))
			*string = ft_strdup(" ");
		else
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
