/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 03:28:06 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/16 04:12:40 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*history_path(void)
{
	char	*tmp;
	char	*path;
	char	*final;

	tmp = getenv("_");
	if (!tmp)
		return (NULL);
	path = ft_substr(tmp, 0, ft_strlen(tmp) - 12);
	final = ft_strjoin(path, "/src/history/.history");
	free(path);
	return (final);
}

static size_t	get_cmd_num(void)
{
	int		fd;
	char	*tmp1;
	char	**tmp2;
	char	*path;

	path = history_path();
	fd = open(path, O_RDONLY | O_APPEND | O_CREAT, 0644);
	free(path);
	if (!fd)
		return (0);
	tmp1 = get_next_line(fd);
	close(fd);
	if (!tmp1)
		return (0);
	tmp2 = ft_split(tmp1, '\n');
	free(tmp1);
	free_2d(tmp2);
	return (ft_strlenx2(tmp2) + 1);
}

static int	history_file(char *str, size_t i)
{
	int		fd;
	char	*path;

	path = history_path();
	fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	free(path);
	if (fd < 0)
	{
		ft_printf("minishell: FAILED to save history\n");
		return (-1);
	}
	if (i != 1)
		ft_putchar_fd('\n', fd);
	ft_putnbr_fd(i, fd);
	ft_putchar_fd(' ', fd);
	ft_putstr_fd(str, fd);
	close(fd);
	return (1);
}

int	historyy(char *str)
{
	size_t		i;

	add_history(str);
	i = get_cmd_num();
	if (i == 0)
		return (-1);
	if (history_file(str, i) == -1)
		return (-1);
	return (1);
}
