/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:13:29 by kamin             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/15 04:53:33 by ommohame         ###   ########.fr       */
=======
/*   Updated: 2022/09/15 14:39:22 by kamin            ###   ########.fr       */
>>>>>>> 352623a4e00c1c10e9048d0cbf8878c82606dd9b
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_wait(t_line **line)
{
	signal(SIGINT, SIG_IGN);
	wait(&(*line)->exit);
	(*line)->exit = WEXITSTATUS((*line)->exit);
	signal(SIGINT, clear_line);
}
