/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 23:39:51 by kamin             #+#    #+#             */
/*   Updated: 2022/08/06 00:38:16 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_env(char **env)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (env[i++])
		ret++;
	return (ret);
}

int	ft_set(int i, char *val)
{
	environ[i] = ft_strdup(val);
	return (-1);
}

int	ft_unset(int i)
{
	environ[i] = NULL;
	return (-1);
}

int	export_executor(char *name, char *val, int ow, int ac)
{
	int	i;

	i = -1;
	while (++i < ac - 1 && ow != -1)
	{
		if (ow == 1 && !ft_strcmp((char *)name, environ[i]))
			ow = ft_set(i, val);
		else if (ow == 0 && i == ac - 2)
			ow = ft_set(i, val);
		if (ow == 2 && !ft_strcmp((char *)name, environ[i]))
			ow = ft_unset(i);
	}
	return (i);
}
