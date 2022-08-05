/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:20:16 by kamin             #+#    #+#             */
/*   Updated: 2022/08/05 20:31:02 by kamin            ###   ########.fr       */
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
	historyy(str);
	free(str);
	return (ret);
}

int	yalla(t_line **line)
{
	if ((*line)->npipes > 0)
		pipes((*line)->cmd, (*line)->ncmds);
	else
	{
		if (redirection((*line)->cmd) != 1)
			exec_ft((*line)->cmd);
	}
	// exec_ft((*line)->cmd);
	// print_line(*line);
	free_nodes(*line);
	free(*line);
	return (1);
}

int	minishell_loop(void)
{
	t_line		*line;
	// f builtins[7];

	// builtins[1] = &ft_echo;
	// builtins[2] = &ft_cd;
	// builtins[3] = &ft_pwd;
	// builtins[4] = &ft_env;
	// builtins[5] = &ft_export;
	// builtins[6] = &ft_exit;
	line = (t_line *)malloc(1 * sizeof(t_line));
	line->exit = 0;
	while (line->exit == 0)
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
