/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:20:16 by kamin             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/26 03:45:05 by ommohame         ###   ########.fr       */
=======
/*   Updated: 2022/07/22 14:20:32 by kamin            ###   ########.fr       */
>>>>>>> origin/karim_staging
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_minishell(char **in)
{
	*in = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, clear_line);
<<<<<<< HEAD
	signal(SIGQUIT, clear_line);
	init_history();
=======
	str = get_next_line(open("./src/history/.history", O_RDONLY | O_APPEND | O_CREAT, 0644));
	if (str != NULL)
	{
		tmp = ft_split(str, '\n');
		for (int i = 0; tmp[i]; i++)
			add_history(tmp[i]);
	}
>>>>>>> origin/karim_staging
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
<<<<<<< HEAD
	// int		pid;

	// print_line(*line);
	(void)in;
=======
	// print_line(*line);
	ft_expansion(line);
>>>>>>> origin/karim_staging
	while ((*line)->cmd)
	{
		if (redirection((*line)->cmd) == 1)// || redirection_in((*line)->cmd) == 1)
			;
		else
			exec_ft((*line)->cmd);
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
