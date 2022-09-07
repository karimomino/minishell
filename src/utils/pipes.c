/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:18:22 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/24 15:16:38 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

size_t	count_pipes(char *str)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i - 1] != '|' && str[i + 1] != '|')
			count++;
		else if (str[i] == '\'' || str[i] == '\"')
			i = skip_quotes(str, i);
		i++;
	}
	return (count);
}

size_t	count_cmds(char **cmd)
{
	size_t		i;
	size_t		count;
	char		*tmp;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		tmp = ft_strtrim(cmd[i], " ");
		if (tmp[0] && tmp != NULL)
			count++;
		free(tmp);
		i++;
	}
	return (count);
}

size_t	check_empty_pipe(char **cmd)
{
	size_t		i;
	char		*tmp;

	i = 0;
	while (cmd[i])
	{
		tmp = ft_strtrim(cmd[i++], " ");
		if (!tmp[0])
		{
			free(tmp);
			ft_putstr_fd("minishell: syntax error ", 2);
			ft_putstr_fd("near unexpected token '|'\n", 2);
			return (-1);
		}
		free(tmp);
	}
	return (1);
}

int	check_pipes(char **cmd, char *str, t_line **line)
{
	size_t	p_count;
	size_t	c_count;

	p_count = count_pipes(str);
	c_count = count_cmds(cmd);
	if (p_count != 0 && c_count != 0)
		if (check_empty_pipe(cmd) != 1)
			return (-1);
	if (c_count == 0 && p_count == 0)
		return (-1);
	else if ((p_count != c_count - 1 && c_count > 0 && p_count > 0)
		|| (p_count > 0 && c_count == 0))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		return (-1);
	}
	else
	{
		(*line)->ncmds = c_count;
		(*line)->npipes = p_count;
		return (1);
	}
}
