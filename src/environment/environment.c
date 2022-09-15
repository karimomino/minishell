/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 01:54:06 by kamin             #+#    #+#             */
/*   Updated: 2022/09/15 14:24:07 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_to_env(char *val)
{
	int		c_size;
	char	**new;
	int		i;

	i = -1;
	c_size = 0;
	while (environ != NULL && environ[c_size++])
		;
	new = (char **)malloc(sizeof(char *) * (c_size + 1))
		;
	while (environ[++i])
	{
		new[i] = ft_strdup(environ[i]);
		free(environ[i]);
	}
	new[i++] = ft_strdup(val);
	new[i] = NULL;
	free(environ);
	environ = new;
	return (-1);
}

static void	init_shlvl(void)
{
	int	curr;

	curr = ft_atoi(getenv("SHLVL"));
	if (curr == 1000)
		curr = 1;
	else
		curr++;
	ft_setenv("SHLVL", ft_itoa(curr), 1);
}

void	init_environment(void)
{
	char	**env;
	char	buff[MAX_PATH];
	int		c_size;
	int		i;

	c_size = -1;
	i = -1;
	while (environ != NULL && environ[++c_size])
		;
	if (c_size > 0)
	{
		env = (char **)malloc((c_size + 1) * sizeof(char *));
		while (environ[++i])
				env[i] = ft_strdup((environ[i]));
		env[i] = NULL;
	}
	else
	{
		env = (char **)malloc((3) * sizeof(char *));
		env[0] = ft_strjoin("PWD=", getcwd(buff, MAX_PATH));
		env[1] = ft_strdup("SHLVL=1");
		env[2] = NULL;
	}
	environ = env;
	if (c_size > 0)
		init_shlvl();
}
