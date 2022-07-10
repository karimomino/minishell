/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:20:16 by kamin             #+#    #+#             */
/*   Updated: 2022/07/10 18:01:52 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*str;
	t_line	*line;

	while (1)
	{
		str = readline("enter a fucking command: ");
		line = parser_v3_0(str);
		if (!line)
			return (EXIT_FAILURE);
		while (line->cmd)
		{
			exec_ft(line->cmd);
			line->cmd = line->cmd->next;
		}	
		free_nodes(line);
		free(line);
	}
	return (EXIT_SUCCESS);
}
