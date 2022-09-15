/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:20:16 by kamin             #+#    #+#             */
/*   Updated: 2022/09/15 01:58:30 by kamin            ###   ########.fr       */
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

int	reaser(t_line **line)
{
	int		ret;
	char	*str;
	char	*prompt;

	prompt = alpha_strjoin(6, "\001\e[1;91m\002", getenv("USER"),
			"👁minishell: \001\e[1;95m\002",
			getenv("PWD"), " 🍆: ", "\001\e[0;39m\002");
	str = readline(prompt);
	if (!str)
		exit(0);
	if (!str[0])
		return (-1);
	ret = parser_v3_0(str, line);
	historyy(str);
	free(str);
	free(prompt);
	return (ret);
}

int	yalla(t_line **line)
{
	if ((*line)->npipes != 0)
		pipes(line, (*line)->ncmds);
	else
	{
		if (redirection(line) == 0)
			exec_ft(line);
	}
	return (SUCCESS);
}

int	minishell_loop(void)
{
	t_line		*line;

	line = (t_line *)ft_calloc(1, sizeof(t_line));
	if (!line)
		return (-1);
	line->exit = 0;
	line->end = 0;
	while (line->end == 0)
	{
		if (reaser(&line) == 1)
			yalla(&line);
	}
	free(line);
	return (1);
}

int	main(void)
{
	init_minishell();
	if (minishell_loop() == -1)
		exit (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
