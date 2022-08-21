/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:20:16 by kamin             #+#    #+#             */
/*   Updated: 2022/08/21 16:18:36 by ommohame         ###   ########.fr       */
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
	int		ret;
	char	*str;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	str = readline("\033[1m\033[32menter a fucking command: \033[0m");
	if (!str)
		exit(0);
	if (!str[0])
		return (-1);
	ret = parser_v3_0(str, &*line);
	while (ret == 0)
	{
		tmp2 = readline("> ");
		if (!tmp2)
			return (-1);
		tmp  = strdup(str);
		str = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		ret = parser_v3_0(str, &*line);
		tmp = strdup(str);
		free(str);
		str = NULL;
		if (ret == 0)
		{
			free(tmp);
			tmp = NULL;
		}
	}
	if (tmp != NULL)
	{
		historyy(tmp);
		free(tmp);
	}
	else
	{
		historyy(str);
		free(str);
	}
	return (ret);
}

int	yalla(t_line **line)
{
	if ((*line)->npipes != 0)
		pipes((*line), (*line)->ncmds);
	else
	{
		if (redirection(*line) != 1)
			exec_ft((*line));
	}
	free(*line);
	return (1);
}

int	minishell_loop(void)
{
	t_line		*line;

	while (1)
	{
		if (reaser(&line) == 1)
		{
			yalla(&line);
		}
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
