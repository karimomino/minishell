/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:17:33 by kamin             #+#    #+#             */
/*   Updated: 2022/09/15 19:37:34 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin(t_line **line)
{
	int	ret;

	ret = 0;
	if ((*line)->cmd->type == 1)
		ret = ft_echo((*line)->cmd);
	else if ((*line)->cmd->type == 2)
		ret = ft_cd((*line)->cmd);
	else if ((*line)->cmd->type == 3)
		ret = ft_pwd((*line)->cmd);
	else if ((*line)->cmd->type == 4)
		ret = ft_env((*line)->cmd);
	else if ((*line)->cmd->type == 5)
		ret = ft_export((*line)->cmd, 1);
	else if ((*line)->cmd->type == 6)
		ret = ft_export((*line)->cmd, 2);
	else if ((*line)->cmd->type == 7)
		ret = ft_exit(line);
	else if ((*line)->cmd->type == 8)
		ret = print_history(*(*line)->cmd);
	(*line)->exit = ret;
	return (ret);
}

static char	*is_file_found(char *token)
{
	char	**paths;
	char	*path;
	char	*f_path;
	int		is_file;

	is_file = access(token, F_OK);
	f_path = NULL;
	paths = NULL;
	if (is_file && getenv("PATH"))
	{
		paths = ft_split(getenv("PATH"), ':');
		path = ft_strjoin("/", token);
		files_access(&is_file, &paths, &path, &f_path);
		free(path);
	}
	free_paths(&paths, &f_path, is_file);
	if (is_file == 0)
		return (f_path);
	else
		return (NULL);
}

void	exec_errors(t_line *line, char *path, int *is_dir)
{
	char	*tmp;

	tmp = NULL;
	check_access(line, path, is_dir);
	if (*is_dir == 1 || *is_dir == 2 || *is_dir == 3)
	{
		line->exit = 126;
		if (*is_dir == 2)
			errno = EACCES;
		else if (*is_dir == 1)
			errno = EISDIR;
		else if (*is_dir == 3)
			errno = ENOENT;
		tmp = alpha_strjoin(2, "minishell: ", path);
		perror(tmp);
		if (tmp)
			free(tmp);
		exit(line->exit = 126);
	}
}

int	exec_bin(t_line **line)
{
	int		ret;
	pid_t	pid;
	char	*path;

	path = is_file_found((*line)->cmd->token->token);
	ret = 0;
	if ((*line)->npipes != 0)
		ret = cmd_child(line, path);
	else
	{
			pid = fork();
		ret = 0;
		if (pid == -1 && (*line)->npipes != 0)
			return (errno);
		else if (!pid)
			ret = cmd_child(line, path);
		else
			ms_wait(line);
	}
	if (path)
		free(path);
	return (ret);
}

int	exec_ft(t_line **line)
{
	int		ret;
	t_token	*head;

	head = (*line)->cmd->token;
	ret = 0;
	if ((*line)->cmd->nargs)
	{
		if ((*line)->cmd->type)
			ret = exec_builtin(line);
		else
			ret = exec_bin(line);
	}
	(*line)->cmd->token = head;
	if ((*line)->ncmds == 1)
		free_cmd((*line)->cmd);
	return (ret);
}
