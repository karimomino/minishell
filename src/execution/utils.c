/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:13:29 by kamin             #+#    #+#             */
/*   Updated: 2022/09/15 19:37:11 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_wait(t_line **line)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait(&(*line)->exit);
	(*line)->exit = WEXITSTATUS((*line)->exit);
	signal(SIGINT, clear_line);
}

int	cmd_child(t_line **line, char *path)
{
	int	ret;
	int	is_dir;

	is_dir = 0;
	if (path == NULL && (((*line)->cmd->token->token[0] == '.'
				&& (*line)->cmd->token->token[1] == '/')
			|| (*line)->cmd->token->token[0] == '/'))
			path = ft_strdup((*line)->cmd->token->token);
	exec_errors(*line, path, &is_dir);
	ret = execve(path, (*line)->cmd->exec, environ);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((*line)->cmd->token->token, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_nodes((*line));
	free((*line));
	(*line)->exit = 127;
	exit((*line)->exit);
	return (ret);
}

void	check_access(t_line *line, char *path, int *is_dir)
{
	struct stat	info;

	stat(path, &info);
	if (S_ISDIR(info.st_mode) != 0)
		*is_dir = 1;
	if (!access(path, F_OK) && access(path, X_OK))
		*is_dir = 2;
	if (access(path, F_OK) && ft_strchr(line->cmd->token->token, '/'))
		*is_dir = 3;
}

void	files_access(int *is, char ***p, char **path, char **f_path)
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

void	free_paths(char ***paths, char **f_path, int is_file)
{
	int	i;

	i = -1;
	while (*paths && (*paths)[++i])
		free((*paths)[i]);
	if (*paths)
		free(*paths);
	if (is_file != 0 && *f_path != NULL)
		free(*f_path);
}
