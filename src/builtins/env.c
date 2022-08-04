/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:52:30 by kamin             #+#    #+#             */
/*   Updated: 2022/07/31 18:54:31 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env(char **env)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (env[i++])
		ret++;
	return (ret);
}

static int	ft_unset(int i)
{
	environ[i] = NULL;
	return (-1);
}

static int	ft_set(int i, char *val)
{
	environ[i] = ft_strdup(val);
	return (-1);
}

void	ft_setenv(const char *name, const char *value, int overwrite)
{
	char	*tmp;
	char	*val;
	int		ac;
	int		i;

	if (overwrite == 2)
		ac = count_env(environ) + 1;
	else
	{
		ac = count_env(environ) + 1 + !overwrite;
		tmp = ft_strjoin(name, "=");
		val = ft_strjoin(tmp, value);
		free(tmp);
	}
	i = -1;
	while (++i < ac - 1 && overwrite != -1)
	{
		if (overwrite == 1 && !ft_strncmp(name, environ[i], ft_strlen(name)))
			overwrite = ft_set(i, val);
		else if (overwrite == 0 && i == ac - 2)
			overwrite = ft_set(i, val);
		else if (overwrite == 2 && !ft_strncmp(name, environ[i], ft_strlen(name)))
			overwrite = ft_unset(i);
	}
	environ[i] = NULL;
	if (overwrite != 2)
		free(val);
}

void	ft_env(void)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
		printf("%s\n", environ[i++]);
}

void	ft_export(t_cmd *cmd, int ow)
{
	char	*name;
	char	*val;
	char	*tmp;
	int		i;

	i = 0;
	tmp = cmd->token->next->token;
	while (tmp[i] != '=')
		i++;
	name = ft_substr(tmp, 0, i);
	val = ft_substr(tmp, ++i, ft_strlen(tmp));
	if (ow == 1 && ft_strchr(name, ' '))
	{
		errno = 22;
		perror("minishell: export: \'=\': ");
		return ;
	}
	if (getenv(name) != NULL && ow == 1)
		ft_setenv(name, val, 1);
	else if (getenv(name) == NULL && ow == 1)
		ft_setenv(name, val, 0);
	else if (ow == 2)
		ft_setenv(name, NULL, 2);
	free(name);
	free(val);
}
