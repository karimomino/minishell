/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:00:48 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/14 21:44:48 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	cmd_len(char *str, size_t i)
{
	while (str[i] == ' ' && str[i])
		i++;
	while (str[i])
	{
		if (str[i] == '>' || str[i + 1] == '<')
			return (i);
		else if (str[i] == '\"' || str[i] == '\'')
			i = skip_quotes(str, i);
		else if (str[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}

int	get_cmd(char *str, char **ret, int *i)
{
	int		j;

	j = cmd_len(str, *i);
	*ret = ft_substr(str, *i, j - *i);
	*i = j;
	if (!*ret)
		return (-1);
	return (1);
}

int	get_args(char *str, char **ret, int *i)
{
	int		j;
	char	*tmp;
	char	*new;

	j = cmd_len(str, *i);
	new = ft_substr(str, *i, j - *i);
	if (!new)
		return (-1);
	if (!*ret)
	{
		*ret = new;
		*i = j;
		return (1);
	}
	if (str[*i - 1] == ' ')
		tmp = ft_strjoin(*ret, " ");
	else
		tmp = ft_strdup(*ret);
	free (*ret);
	*ret = ft_strjoin(tmp, new);
	free (tmp);
	free(new);
	if (!*ret)
		return (-1);
	*i = j;
	return (1);
}
