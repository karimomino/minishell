/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:00 by kamin             #+#    #+#             */
/*   Updated: 2022/06/19 11:24:56 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_pwd(void)
{
	char	cwd[MAX_PATH];

	if (getcwd(cwd, MAX_PATH))
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
