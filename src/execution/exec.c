/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:17:33 by kamin             #+#    #+#             */
/*   Updated: 2022/09/12 16:15:46 by kamin            ###   ########.fr       */
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
	is_file = access(token, F_OK);
	f_path = NULL;
	paths = NULL;
	if (is_file && getenv("PATH"))
	{
		paths = ft_split(getenv("PATH"), ':');
		path = ft_strjoin("/", token);
		is_file_helper(&is_file, &paths, &path, &f_path);
		free(path);
	}
	while (paths && paths[++i])
		free(paths[i]);
	if (paths)
		free(paths);
	if (is_file != 0 && f_path != NULL)
		free(f_path);
	if (is_file == 0)
		return (f_path);
	else
		return (NULL);
}

static int	cmd_child(t_line **line, char *path, int ret)
{
	if (path == NULL && (((*line)->cmd->token->token[0] == '.'
				&& (*line)->cmd->token->token[1] == '/')
			|| (*line)->cmd->token->token[0] == '/'))
		path = ft_strdup((*line)->cmd->token->token);
	else if (path == NULL)
		path = ft_strdup(getenv("PWD"));
	ret = execve(path, ft_split((*line)->cmd->exec, ' '), environ);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((*line)->cmd->token->token, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_nodes((*line));
	free((*line));
	(*line)->exit = 127;
	exit((*line)->exit);
	return (ret);
}

int	exec_bin(t_line **line)
{
	int		ret;
	pid_t	pid;
	char	*path;

	path = is_file_found((*line)->cmd->token->token);
	ret = 0;
	if ((*line)->npipes != 0)
		ret = cmd_child(line, path, ret);
	else
	{
			pid = fork();
		ret = 0;
		if (pid == -1 && (*line)->npipes != 0)
			return (errno);
		else if (pid == 0 || pid == -69)
			ret = cmd_child(line, path, ret);
		else if (pid != -69)
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
