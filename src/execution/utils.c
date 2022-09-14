/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:13:29 by kamin             #+#    #+#             */
/*   Updated: 2022/09/14 17:17:50 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_wait(t_line **line)
{
	signal(SIGINT, do_nothing);
	signal(SIGQUIT, do_nothing);
	wait(&(*line)->exit);
	(*line)->exit = WEXITSTATUS((*line)->exit);
	signal(SIGINT, clear_line);
	signal(SIGQUIT, clear_line);
}
