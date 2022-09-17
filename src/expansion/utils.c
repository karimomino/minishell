/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:34:59 by kamin             #+#    #+#             */
/*   Updated: 2022/09/17 14:49:23 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	stopper_finder(char *tok)
{
	int	i;

	i = -1;
	while (!ft_strchr(" $\'\"\0", tok[++i]))
		;
	// if (i == 0)
	// 	i++;
	return (i);
}

int	cpy_sec(int start, char **com, char *tok, char stopper)
{
	int	i;
	int	j;

	i = start;
	j = -1;
	while (tok[++j] != stopper)
	{
		if (i < 0)
			i = 0;
		(*com)[i] = (tok)[j];
		i++;
	}
	return (i);
}

size_t	calc_malloc_size(char *tok, char *var, char *val)
{
	size_t	size;

	size = ft_strlen(tok) + ft_strlen(val) - ft_strlen(var);
	return (size);
}

int	check_char(char c, int *dq, int *sq)
{
	int	ret;

	ret = 0;
	if (c == '"')
	{
		(*dq)++;
		if (*dq > 1)
			*dq = 0;
		ret = 1;
	}
	else if (c == '\'')
	{
		(*sq)++;
		if (*sq > 1)
			*sq = 0;
		ret = 1;
	}
	return (ret);
}

char	**select_string(void *cmd, int flag)
{
	if (flag)
		return ((char **)&((*(t_token **)cmd)->token));
	else
		return ((char **)&((*(t_redir **)cmd)->file));
}
