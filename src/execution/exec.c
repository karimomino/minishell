/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:17:33 by kamin             #+#    #+#             */
/*   Updated: 2022/08/15 18:13:55 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin(t_line *line)
{
	int	ret;

	ret = 0;
	if (line->cmd->type == 1)
		ret = ft_echo(line->cmd);
	else if (line->cmd->type == 2)
		ret = ft_cd(line->cmd);
	else if (line->cmd->type == 3)
		ret = ft_pwd(line->cmd);
	else if (line->cmd->type == 4)
		ft_env(line->cmd);
	else if (line->cmd->type == 5)
		ft_export(line->cmd, 1);
	else if (line->cmd->type == 6)
		ft_export(line->cmd, 2);
	else if (line->cmd->type == 7)
		ft_exit(line);
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

int	exec_bin(t_line *line)
{
	int		ret;
	pid_t	pid;
	char	*path;
	char	**tmp;

	path = is_file_found(line->cmd->token->token);
	ret = 0;
	pid = fork();
	if (pid == -1)
		return (errno);
	else if (!pid)
	{
		tmp = ft_split(line->cmd->exec, ' ');
		ret = execve(path, tmp, environ);
		printf("minishell: %s: command not found\n", line->cmd->token->token);
		free_nodes(line);
		free(line);
		free_2d(tmp);
		t_infoo.retVal = 127;
		exit(t_infoo.retVal);
	}
	else
		wait(&t_infoo.retVal);
	if (path)
		free(path);
	return (ret);
}

int	exec_ft(t_line *line)
{
	int		ret;
	t_token	*head;
	t_cmd	*cmdd;

	ret = 0;
	cmdd = line->cmd;
	head = line->cmd->token;
	if (line->cmd->nargs)
	{
		if (line->cmd->type)
			ret = exec_builtin(line);
		else
			ret = exec_bin(line);
	}
	line->cmd = cmdd;
	line->cmd->token = head;
	return (ret);
}
