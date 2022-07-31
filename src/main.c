/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:20:16 by kamin             #+#    #+#             */
/*   Updated: 2022/07/31 14:43:57 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_minishell(void)
{
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
	// print_line(*line);
	historyy(str);
	free(str);
	return (ret);
}

int	yalla(t_line **line)
{
	// print_line(*line);
	if ((*line)->cmd->token)
		ft_expansion(line);
	while ((*line)->cmd)
	{
		if (redirection((*line)->cmd) == 1)// || redirection_in((*line)->cmd) == 1)
			;
		else
			exec_ft((*line)->cmd);
		(*line)->cmd = (*line)->cmd->next;
	}
	// pipes((*line)->cmd);
	free_nodes(*line);
	free(*line);
	return (1);
}

int	minishell_loop(void)
{
	t_line		*line;

	while (1)
	{
		if (reaser(&line) == 1)
			yalla(&line);
	}
	return (1);
}

int	main(void)
{
	init_minishell();
	if (minishell_loop() == -1)
		exit (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
