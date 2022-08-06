/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:17:33 by kamin             #+#    #+#             */
/*   Updated: 2022/08/06 00:39:02 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin(t_cmd *in)
{
	int	ret;

	ret = 0;
	if (in->type == 1)
		ret = ft_echo(in);
	if (in->type == 2)
		ret = ft_cd(in);
	if (in->type == 3)
		ret = ft_pwd(in);
	if (in->type == 4)
		ft_env(in);
	if (in->type == 5)
		ft_export(in, 1);
	if (in->type == 6)
		ft_export(in, 2);
	if (in->type == 7)
		exit (SUCCESS);
	return (ret);
}

static void	is_file_helper(int *is, char ***p, char **path, char **f_path)
{
	int	i;

	i = -1;
	while (*is == -1 && (*p)[++i])
	{
		*f_path = ft_strjoin((*p)[i], *path);
		*is = access(*f_path, F_OK);
		if (*is == -1)
		{
			free(*f_path);
			*f_path = NULL;
		}
	}
}

static char	*is_file_found(char *token)
{
	char	**paths;
	char	*path;
	char	*f_path;
	int		is_file;
	int		i;

	i = -1;
	paths = ft_split(getenv("PATH"), ':');
	path = ft_strjoin("/", token);
	is_file = -1;
	is_file_helper(&is_file, &paths, &path, &f_path);
	free(path);
	while (paths[++i])
		free(paths[i]);
	free(paths);
	if (is_file != 0 && f_path != NULL)
		free(f_path);
	if (is_file == 0)
		return (f_path);
	else
		return (NULL);
}

int	exec_bin(t_cmd *in)
{
	int		ret;
	pid_t	pid;
	char	*path;

	path = is_file_found(in->token->token);
	pid = fork();
	ret = 0;
	if (pid == -1)
		return (errno);
	else if (!pid)
	{
		ret = execve(path, ft_split(in->exec, ' '), environ);
		printf("minishell: %s: command not found\n", in->token->token);
		t_infoo.retVal = 127;
		exit(t_infoo.retVal);
	}
	else
		wait(&t_infoo.retVal);
	if (path)
		free(path);
	return (ret);
}

int	exec_ft(t_cmd *in)
{
	int	ret;

	ret = 0;
	if (in->nargs)
	{
		if (in->type)
			ret = exec_builtin(in);
		else
			ret = exec_bin(in);
	}
	return (ret);
}
