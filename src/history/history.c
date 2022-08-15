/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 03:28:06 by ommohame          #+#    #+#             */
/*   Updated: 2022/08/06 16:31:05 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_history(void)
{
	int		fd;
	size_t	i;
	size_t	j;
	char	*tmp1;
	char	**his;

	fd = open("./src/history/.history", O_RDONLY | O_APPEND | O_CREAT, 0644);
	tmp1 = get_next_line(fd);
	close(fd);
	if (!tmp1)
		return (-1);
	his = ft_split(tmp1, '\n');
	free(tmp1);
	i = 0;
	while (his[i])
	{
		j = 0;
		while (ft_isdigit(his[i][j]))
			j++;
		tmp1 = ft_strtrim(his[i++] + j, " ");
		add_history(tmp1);
		free(tmp1);
	}
	free_2d(his);
	return (1);
}

int	history_file(char *str, int i)
{
	int		fd;

	fd = open("./src/history/.history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd <= 0)
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

size_t	get_cmd_num(void)
{
	int		i;
	int		fd;
	char	*tmp1;
	char	**tmp2;

	fd = open("./src/history/.history", O_RDONLY | O_APPEND | O_CREAT, 0644);
	tmp1 = get_next_line(fd);
	close(fd);
	if (!tmp1)
		return (1);
	tmp2 = ft_split(tmp1, '\n');
	free(tmp1);
	i = ft_strlenx2(tmp2);
	free_2d(tmp2);
	return (i + 1);
}

int	historyy(char *str)
{
	size_t		i;

	i = get_cmd_num();
	add_history(str);
	if (history_file(str, i) == -1)
		return (-1);
	return (1);
}

int	print_history(t_cmd cmd)
{
	int			fd;
	size_t		num;
	size_t		total;
	size_t		i;
	char		*tmp1;
	char		**tmp2;

	if (cmd.nargs > 2)
	{
		ft_printf("minishell: history: too many arguments\n");
		return (-1);
	}
	fd = open("./src/history/.history", O_RDONLY);
	if (fd <= 0)
	{
		ft_printf("minishell: FAILED to read history\n");
		return (-1);
	}
	num = 0;
	tmp1 = get_next_line(fd);
	if (!tmp1)
		return (-1);
	tmp2 = ft_split(tmp1, '\n');
	free(tmp1);
	total = ft_strlenx2(tmp2);
	if (cmd.nargs == 2)
	{
		i = 0;
		while (cmd.token->next->token[i])
		{
			if (ft_isdigit(cmd.token->next->token[i++]) == 0)
			{
				printf("minishell: history: %s: numeric argument required\n", 
				cmd.token->next->token);
			}
		}
		num = ft_atoi(cmd.token->next->token);
		if (num > total)
			num = 0;
		else if (num < total)
			num = total - num;
		while (num < total)
			ft_printf("%s\n", tmp2[num++]);
	}
	else
	{
		while (tmp2[num])
			ft_printf("%s\n", tmp2[num++]);
	}
	free_2d(tmp2);
	return (1);
}
