/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 23:39:51 by kamin             #+#    #+#             */
/*   Updated: 2022/09/17 22:11:36 by ommohame         ###   ########.fr       */
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
	char	**env;
	int		j;
	int		environ_i;

	j = 0;
	while (environ != NULL && environ[j++])
		;
	env = (char **)malloc(sizeof(char *) * (j))
		;
	j = -1;
	environ_i = -1;
	while (environ[++j])
	{
		if (j == i)
			free(environ[++environ_i]);
		if (environ[++environ_i])
			env[j] = ft_strdup(environ[environ_i]);
		free(environ[environ_i]);
	}
	env[j] = NULL;
	free(environ);
	environ = env;
	return (-1);
}

char	*find_name(int i)
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
		if (ow == 2 && !ft_strncmp((char *)name, tmp, ft_strlen(tmp)))
			ow = ft_unset(i);
		if (tmp)
			free (tmp);
	}
}
