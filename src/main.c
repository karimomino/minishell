/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:20:16 by kamin             #+#    #+#             */
/*   Updated: 2022/07/14 21:05:29 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_minishell(t_infohis **info)
{
	*info = (t_infohis *)malloc(sizeof(t_infohis));
	if (!*info)
		return (-1);
	(*info)->history = (t_history *)malloc(sizeof(t_history));
	// if (!((*info)->history))
	// 	return (-1);
	(*info)->history = NULL;
	return (1);
}

int	main(void)
{
	int			ret;
	char		*str;
	t_line		*line;
	t_infohis	*infohis;

	init_minishell(&infohis);
	while (1)
	{
		str = readline("minishell - enter a fucking command: ");
		ret = parser_v3_0(str, &line);
		while (ret == 0)
		{
			str = ft_strjoin(str, readline("> "));
			ret = parser_v3_0(str, &line);
		}
		historyy(str, &infohis);
		if (ret == 1)
		{
			// print_line(line);
			while (line->cmd)
			{
				if (line->cmd->token)
				{
					if (ft_strncmp(line->cmd->token->token, "history", 7) == 0) 
						print_history(*infohis, *line->cmd);
					else
						exec_ft(line->cmd);
				}
				redirection(*line->cmd, "test ");
				line->cmd = line->cmd->next;
			}
			free_nodes(line);
			free(line);
		}
		free(str);
	}
	return (EXIT_SUCCESS);
}
