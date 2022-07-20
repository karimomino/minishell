/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:20:16 by kamin             #+#    #+#             */
/*   Updated: 2022/07/20 20:22:59 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_minishell(char **in)
{
	char *str;
	char	**tmp;
	*in = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, clear_line);
	str = get_next_line(open("./src/history/.history", O_RDONLY | O_APPEND | O_CREAT, 0644));
	tmp = ft_split(str, '\n');
	for (int i = 0; tmp[i]; i++)
		add_history(tmp[i]);
}

int	reaser(t_line **line)
{
	int			ret;
	char		*str;

	str = readline("\033[1m\033[32menter a fucking command: \033[0m");
	if (!str)
		exit (EXIT_FAILURE);
	ret = parser_v3_0(str, &*line);
	while (ret == 0)
	{
		str = ft_strjoin(str, readline("> "));
		ret = parser_v3_0(str, &*line);
	}
	// if (ret == 1)
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
		usleep(100);
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
