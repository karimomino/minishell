/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 03:02:12 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/05 23:34:05 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	redir_len(char *str, size_t j)
{
	while ((str[j] == '>' || str[j] == '<') && str[j])
		j++;
	while (str[j] == ' ' && str[j])
	{
		if (str[j] == '\"' || str[j] == '\'')
			return (skip_quotes(str, j));
		j++;
	}
	while (str[j] != '>' && str[j] != '<' && str[j])
	{
		if (str[j] == '\"' || str[j] == '\'')
			return (skip_quotes(str, j));
		else if (str[j] == ' ')
			return (j);
		j++;
	}
	return (j);
}

int	define_redir(char *str, char **ret, int *i)
{
	int		j;
	char	*tmp;
	char	*new;

	j = redir_len(str, *i);
	if (j == 0)
		return (-1);
	new = ft_substr(str, *i, j - *i);
	if (!new)
		return (-1);
	if (!*ret)
	{
		*ret = new;
		*i = j;
		return (1);
	}
	tmp = ft_strjoin(*ret, new);
	free(*ret);
	free(new);
	if (!tmp)
		return (-1);
	*ret = tmp;
	*i = j;
	return (1);
}

char	*get_redir(char *str, int *i)
{
	int		j;
	int		flag;
	char	*tmp;
	char	*ret;

	j = redir_len(str, *i);
	tmp = ft_substr(str, *i, j - *i);
	ret = squeeze_space(tmp);
	free(tmp);
	*i = j;
	flag = 1;
	while (str[j])
	{
		if (str[j] == '>' || str[j] == '<')
			flag = -1;
		j++;
	}
	if (flag == 1)
		*i = -1;
	return (ret);
}

int	redir_what(char *str)
{
	size_t	i;
	int		in;
	int		out;

	i = 0;
	in = 0;
	out = 0;
	while ((str[i] == '>' || str[i] == '<') && str[i])
	{
		if (str[i] == '<')
			in++;
		if (str[i] == '>')
			out++;
		if (in > 3 || out > 3)
			return (-1);
		i++;
	}
	if (in <= 2 && out == 0)
		return (0);
	else if (out <= 2 && in == 0)
		return (1);
	else
		return (-1);
}

int	redir_type(char *str)
{
	int		i;

	i = 0;
	while ((str[i] == '>' || str[i] == '<') && str[i])
	{
		if (i > 3)
			return (-1);
		i++;
	}
	return (i);
}
