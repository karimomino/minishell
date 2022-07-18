/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:20:16 by kamin             #+#    #+#             */
/*   Updated: 2022/07/18 18:01:18 by kamin            ###   ########.fr       */
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
	char		*in;
	t_line		*line;

	// in = NULL;
	// init_minishell(&infohis);
	while (1)
	{
		str = readline("enter a fucking command: ");
		line = parser_v3_0(str);
		if (line)
		{
			while (line->cmd)
			{
				exec_ft(line->cmd);
				line->cmd = line->cmd->next;
			}
		}
		free_nodes(line);
		free(line);
	}
	return (EXIT_SUCCESS);
}
