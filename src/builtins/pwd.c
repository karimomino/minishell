/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:00 by kamin             #+#    #+#             */
/*   Updated: 2022/08/01 20:59:25 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmd *in)
{
	char	cwd[MAX_PATH];

	(void)in;
	if (getcwd(cwd, MAX_PATH))
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
