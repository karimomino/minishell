/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 04:09:48 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/16 04:12:17 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_the_history(char *str)
{
	size_t		i;
	size_t		j;
	char		*tmp;
	char		**his;

	i = 0;
	his = ft_split(str, '\n');
	while (his[i])
	{
		j = 0;
		while (ft_isdigit(his[i][j]))
			j++;
		tmp = ft_strtrim(his[i++] + j, " ");
		add_history(tmp);
		free(tmp);
	}
	free_2d(his);
}

int	init_history(void)
{
	int		fd;
	char	*tmp;
	char	*path;

	path = history_path();
	fd = open(path, O_RDONLY | O_APPEND | O_CREAT, 0644);
	free(path);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: FAILED to open history file\n", 2);
		return (-1);
	}
	tmp = get_next_line(fd);
	if (!tmp)
	{
		ft_putstr_fd("minishell: FAILED to read history file\n", 2);
		return (-1);
	}
	add_the_history(tmp);
	free(tmp);
	close(fd);
	return (1);
}
