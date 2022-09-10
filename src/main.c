/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:20:16 by kamin             #+#    #+#             */
/*   Updated: 2022/09/09 19:37:49 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_minishell(void)
{
	init_environment();
	rl_catch_signals = 0;
	signal(SIGINT, clear_line);
	signal(SIGQUIT, clear_line);
	init_history();
}

int	reaser(t_line **line, int f, char *str)
{
	int		ret;

	if (f == 0)
		str = readline(PROMPT_MSG);
	if (!str)
		exit(0);
	if (!str[0])
		return (-1);
	ret = parser_v3_0(str, &*line);
	historyy(str);
	free(str);
	return (ret);
}

int	yalla(t_line **line)
{
	if ((*line)->npipes != 0)
		pipes((*line), (*line)->ncmds);
	else
	{
		if (redirection(*line) == 0)
			exec_ft((*line));
	}
	free(*line);
	return (1);
}

int	minishell_loop(void)
{
	t_line		*line;

	while (t_infoo.exit == 0)
	{
		if (reaser(&line, 0, NULL) == 1)
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
