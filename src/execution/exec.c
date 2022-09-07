/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:17:33 by kamin             #+#    #+#             */
/*   Updated: 2022/09/07 16:28:32 by ommohame         ###   ########.fr       */
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
	is_file = access(token, F_OK);
	paths = NULL;
	f_path = NULL;
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

static int	cmd_child(t_line *line, char *path, int ret)
{
	if (path == NULL)
	{
		path = ft_strdup(getenv("PWD"));
		printf("PATH: %s\n", path);
	}
	ret = execve(path, ft_split(line->cmd->exec, ' '), environ);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(line->cmd->token->token, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_nodes(line);
	free(line);
	g_exitval = 127;
	exit(g_exitval);
	return (ret);
}

int	exec_bin(t_line *line)
{
	int		ret;
	pid_t	pid;
	char	*path;

	path = is_file_found(line->cmd->token->token);
	pid = fork();
	ret = 0;
	if (pid == -1)
		return (errno);
	else if (!pid)
		ret = cmd_child(line, path, ret);
	else
	{
		wait(&g_exitval);
		g_exitval = WEXITSTATUS(g_exitval);
		printf("THIS IS THE EXIT STATUS: %d\n", g_exitval);
	}
	if (path)
		free(path);
	return (ret);
}

int	exec_ft(t_line *line)
{
	int		ret;
	t_token	*head;

	head = line->cmd->token;
	ret = 0;
	if (line->cmd->nargs)
	{
		if (line->cmd->type)
			ret = exec_builtin(line);
		else
			ret = exec_bin(line);
	}
	line->cmd->token = head;
	if (line->ncmds == 1)
		free_cmd(line->cmd);
	return (ret);
}
