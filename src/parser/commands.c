/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:00:48 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/23 22:27:48 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	cmd_len(char *str, size_t i)
{
	while (str[i] == ' ' && str[i])
		i++;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			return (i - 1);
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
	*ret = ft_substr(str, *i, j - *i + 1);
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
	if (*i == j)
		return (0);
	new = ft_substr(str, *i, j - *i + 1);
	if (!new)
		return (-1);
	if (!*ret)
	{
		*ret = new;
		*i = j;
		return (1);
	}
	if (str[*i - 1] == ' ')
		tmp = alpha_strjoin(3, *ret, " ", new);
	else
		tmp = ft_strjoin(*ret, new);
	free(*ret);
	free(new);
	*ret = tmp;
	*i = j;
	return (1);
}
