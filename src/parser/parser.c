/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/12 20:08:25 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	get_exec(t_line **line)
{
	size_t	i;
	char	**exec;
	t_cmd	*head;
	t_token	*head_t;

	head = (*line)->cmd;
	while ((*line)->cmd)
	{
		i = -1;
		head_t = (*line)->cmd->token;
		exec = (char **)malloc(sizeof(char *) * ((*line)->cmd->nargs + 1));
		if (!exec)
			return ;
		while (++i < (*line)->cmd->nargs)
		{
			exec[i] = ft_strdup((*line)->cmd->token->token);
			(*line)->cmd->token = (*line)->cmd->token->next;
		}
		exec[i] = NULL;
		(*line)->cmd->exec = exec;
		(*line)->cmd->token = head_t;
		(*line)->cmd = (*line)->cmd->next;
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
