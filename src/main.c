/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:20:16 by kamin             #+#    #+#             */
/*   Updated: 2022/07/11 02:13:20 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	int		ret;
	char	*str;
	t_line	*line;

	while (1)
	{
		str = readline("minishell - enter a fucking command: ");
		ret = parser_v3_0(str, &line);
		if (ret == -1)
			exit (EXIT_FAILURE);
		while (ret == 0)
		{
			str = ft_strjoin(str, readline("> "));
			ret = parser_v3_0(str, &line);
		}
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
