/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:35:14 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/12 02:11:25 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_his_error(t_cmd cmd)
{
	int		fd;
	char	*path;

	if (cmd.nargs > 2)
	{
		ft_putstr_fd("minishell: history: too many arguments\n", 2);
		return (-1);
	}
	path = history_path();
	fd = open(path, O_RDONLY);
	free(path);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: FAILED to open history\n", 2);
		return (-1);
	}
	return (fd);
}

static char	**get_history(int fd)
{
	char	*tmp;
	char	**his;

	tmp = get_next_line(fd);
	if (!tmp)
		return (NULL);
	his = ft_split(tmp, '\n');
	free(tmp);
	return (his);
}

static int	check_his_args(t_cmd cmd)
{
	size_t	i;

	i = 0;
	while (cmd.token->next->token[i])
	{
		if (ft_isdigit(cmd.token->next->token[i++]) == 0)
		{
			ft_putstr_fd("minishell: history: ", 2);
			ft_putstr_fd(cmd.token->next->token, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (-1);
		}
	}
	return (1);
}

static void	his_args_cmd(t_cmd cmd, char **his)
{
	size_t		num;
	size_t		total;

	total = ft_strlenx2(his);
	num = ft_atoi(cmd.token->next->token);
	if (num > total)
		num = 0;
	else if (num < total)
		num = total - num;
	while (num < total)
		ft_putendl_fd(his[num++], 1);
}

int	print_history(t_cmd cmd)
{
	int			fd;
	size_t		num;
	char		**his;

	fd = check_his_error(cmd);
	if (fd == -1)
		return (-1);
	his = get_history(fd);
	close (fd);
	num = 0;
	if (cmd.nargs == 2)
	{
		if (check_his_args(cmd) == -1)
		{
			free_2d(his);
			return (-1);
		}
		his_args_cmd(cmd, his);
	}
	else
	{
		while (his[num])
			ft_putendl_fd(his[num++], 1);
	}
	free_2d(his);
	return (1);
}
