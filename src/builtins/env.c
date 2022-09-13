/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:52:30 by kamin             #+#    #+#             */
/*   Updated: 2022/09/13 18:11:33 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_setenv(const char *name, const char *value, int overwrite)
{
	char	*tmp;
	char	*val;
	int		ac;

	val = NULL;
	if (overwrite == 2)
		ac = count_env((environ)) + 1;
	else
	{
		ac = count_env((environ)) + 1 + !overwrite;
		tmp = ft_strjoin(name, "=");
		val = ft_strjoin(tmp, value);
		free(tmp);
	}
	export_executor((char *)name, val, overwrite, ac);
	if (overwrite != 2)
		free(val);
}

int	ft_env(t_cmd *in)
{
	int	i;

	i = 0;
	(void)in;
	while (environ[i] != NULL)
	{
		ft_putstr_fd(environ[i++], 1);
		ft_putstr_fd("\n", 1);
	}
	return (SUCCESS);
}

static int	export_error(char *name, int ow)
{
	if (ow == 1 && (ft_strchr(name, ' ') || !ft_strcmp(name, "")
			|| !ft_isalpha(name[0]) || name == NULL))
	{
		errno = EINVAL;
		perror("minishell: export: \'=\': ");
		return (1);
	}
	// if (ow == 1 && (!ft_strcmp(val, "") || val == NULL))
	// 	return (-1);
	return (0);
}

static void	export_selector(char *name, char *val, int ow)
{
	if (getenv(name) != NULL && ow == 1)
		ft_setenv(name, val, 1);
	else if (getenv(name) == NULL && ow == 1)
		ft_setenv(name, val, 0);
	else if (ow == 2)
		ft_setenv(name, NULL, 2);
}

int	ft_export(t_cmd *cmd, int ow)
{
	char	*name;
	char	*val;
	char	*tmp;
	int		i;
	int		err;

	i = 0;
	if (cmd->token->next)
		tmp = cmd->token->next->token;
	else
	{
		ft_env(cmd);
		return (1);
	}
	while (tmp[i] != '=' && tmp[i] != '\0')
		i++;
	name = ft_substr(tmp, 0, i);
	val = ft_substr(tmp, ++i, ft_strlen(tmp));
	err = export_error(name, ow);
	if (!err)
		export_selector(name, val, ow);
	free(name);
	free(val);
	return (err);
}
