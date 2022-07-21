/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:20:16 by kamin             #+#    #+#             */
/*   Updated: 2022/07/20 22:07:02 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_minishell(char **in)
{
	*in = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, clear_line);
	signal(SIGQUIT, clear_line);
	init_history();
}

int	reaser(t_line **line)
{
	int			ret;
	char		*str;

	str = readline("\033[1m\033[32menter a fucking command: \033[0m");
	if (!str)
		exit (EXIT_FAILURE);
	if (!str[0])
		return (-1);
	ret = parser_v3_0(str, &*line);
	while (ret == 0)
	{
		str = ft_strjoin(str, readline("> "));
		ret = parser_v3_0(str, &*line);
	}
	historyy(str);
	free(str);
	return (ret);
}

int	yalla(t_line **line, char **in)
{
	print_line(*line);
	while ((*line)->cmd)
	{
		exec_ft((*line)->cmd);
		redirection(*(*line)->cmd, "test ", &*in);
		(*line)->cmd = (*line)->cmd->next;
	}
	free_nodes(*line);
	free(*line);
	return (1);
}

int	minishell_loop(char **in)
{
	t_line		*line;

	while (1)
	{
		if (reaser(&line) == 1)
			yalla(&line, &*in);
	}
	return (1);
}

int	main(void)
{
	char		*in;

	init_minishell(&in);
	if (minishell_loop(&in) == -1)
		exit (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
