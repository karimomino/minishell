/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:17:33 by kamin             #+#    #+#             */
/*   Updated: 2022/08/05 18:48:29 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	exec_builtin(t_cmd *in, f *builtins)
// {
// 	int		ret;
// 	pid_t	pid;

// 	pid = fork();
// 	ret = 0;
// 	if (pid == -1)
// 		return (errno);
// 	else if (!pid)
// 	{
// 		if (in->type == 5)
// 			builtins[5](in, 1);
// 		else if (in->type == 6)
// 			builtins[5](in, 2);
// 		else
// 			builtins[in->type](in);
// 		t_infoo.retVal = 127;
// 		exit(t_infoo.retVal);
// 	}
// 	else
// 		wait(&t_infoo.retVal);
// 	return (ret);
// }

int	exec_builtin(t_cmd *in, f *builtins)
{
	int	ret;

	ret = 0;
	(void)builtins;
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

static char	*is_file_found(char *token)
{
	char	**paths;
	char	*path;
	char	*f_path;
	int		i;
	int		is_file;

	paths = ft_split(getenv("PATH"), ':');
	i = -1;
	is_file = -1;
	path = ft_strjoin("/", token);
	while (is_file == -1 && paths[++i])
	{
		f_path = ft_strjoin(paths[i], path);
		is_file = access(f_path, F_OK);
		if (is_file == -1)
		{
			free(f_path);
			f_path = NULL;
		}
	}
	free(path);
	if (is_file != 0 && f_path != NULL)
		free(f_path);
	if (is_file == 0)
		return (ft_strjoin(paths[i], ft_strjoin("/", token)));
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
		ret = execve(path, ft_split(in->cmd, ' '), environ);
		printf("minishell: %s: command not found\n", in->token->token);
		t_infoo.retVal = 127;
		exit(t_infoo.retVal);
	}
	else
		wait(&t_infoo.retVal);
	return (ret);
}

int	exec_ft(t_cmd *in, f *builtins)
{
	int	ret;

	ret = 0;
	if (in->nargs)
	{
		if (in->type)
			ret = exec_builtin(in, builtins);
		else
			ret = exec_bin(in);
	}
	return (ret);
}
