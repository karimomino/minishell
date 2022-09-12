/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/11 21:27:44 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	get_exec(t_line **line)
{
	char		*tmp;
	char		*main;
	t_cmd		*head;
	t_token		*head_t;

	head = (*line)->cmd;
	while ((*line)->cmd)
	{
		main = ft_strdup("");
		head_t = (*line)->cmd->token;
		while ((*line)->cmd->token)
		{
			tmp = alpha_strjoin(3, main, " ", (*line)->cmd->token->token);
			free (main);
			main = ft_strdup(tmp);
			free(tmp);
			(*line)->cmd->token = (*line)->cmd->token->next;
		}
		(*line)->cmd->exec = ft_strdup(main);
		(*line)->cmd->token = head_t;
		(*line)->cmd = (*line)->cmd->next;
		free(main);
	}
	(*line)->cmd = head;
}

static void	get_cmds(char **str, t_line **line)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (cmds(str[i], line) == -1)
			free_nodes(*line);
		i++;
	}
	ft_expansion(line);
	remove_all_quotes(line);
	get_exec(line);
	// print_line(*line);
}

void	init_values(t_line *line)
{
	line->ncmds = 0;
	line->nexec = 0;
	line->npipes = 0;
	line->cmd = NULL;
}

/*
*	returns -1 if for an error
*/
int	parser_v3_0(char *str, t_line **line)
{
	int		ret;
	char	**cmd;

	cmd = ft_split_sc(str, '|');
	if (!cmd)
		return (-1);
	init_values((*line));
	get_cmds(cmd, line);
	if (!(*line))
	{
		free_2d(cmd);
		free((*line));
		return (-1);
	}
	ret = check_pipes(cmd, str, line);
	free_2d(cmd);
	if (ret == 0 || ret == -1)
		return (ret);
	return (1);
}
