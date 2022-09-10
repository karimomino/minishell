/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 23:39:51 by kamin             #+#    #+#             */
/*   Updated: 2022/09/10 23:24:59 by kamin            ###   ########.fr       */
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
	if (environ[i])
		free(environ[i]);

	environ[i] = ft_strdup(val);
	return (-1);
}

int	ft_unset(int i)
{
	free(environ[i]);
	environ[i] = NULL;
	return (-1);
}

char *find_name(int i)
{
	char	*tmp;
	int		j;

	j = 0;
	while (environ[i][j] != '=' && environ[i][j] != '\0')
		j++;
	tmp = ft_substr(environ[i], 0, j);
	return (tmp);
}

void	export_executor(char *name, char *val, int ow, int ac)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (++i < ac - 1 && ow != -1)
	{
		if ((ow == 1 || ow == 2))
			tmp = find_name(i);
		if (ow == 1 && !ft_strncmp((char *)name, tmp, ft_strlen(tmp)))
			ow = ft_set(i, val);
		else if (ow == 0 && i == ac - 2)
			ow = add_to_env(val);
			// ow = ft_set(i, val);
		if (ow == 2 && !ft_strncmp((char *)name, tmp, ft_strlen(tmp)))
			ow = ft_unset(i);
		if (tmp)
			free (tmp);
	}
	// return (i);
}
