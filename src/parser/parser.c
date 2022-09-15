/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 03:52:28 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/15 18:03:52 by kamin            ###   ########.fr       */
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

static int	get_cmds(char **str, t_line **line)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (cmds(str[i], line) == -1)
		{
			free_nodes(*line);
			return (-1);
		}
		i++;
	}
	ft_expansion(line);
	get_struct_fake_string(line);
	remove_all_quotes(line);
	get_exec(line);
	return (1);
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

	cmd = NULL;
	cmd = ft_split_sc(str, '|');
	if (!cmd)
		return (-1);
	init_values((*line));
	if (get_cmds(cmd, line) == -1)
	{
		free_2d(cmd);
		return (-1);
	}
	ret = check_pipes(cmd, str, line);
	// printf("this is the val: %d\n", ret);
	free_2d(cmd);
	if (ret == 0 || ret == -1)
		return (ret);
	return (1);
}

// # include <readline/readline.h>
// # include <readline/history.h>

// int main(void)
// {
// 	char	*str;
// 	t_line	*line;

// 	line = (t_line *)ft_calloc(1, sizeof(t_line));
// 	str = readline("test: ");
// 	parser_v3_0(str, &line);
// }
