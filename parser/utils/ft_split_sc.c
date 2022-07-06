/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:30:53 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/06 20:52:25 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static int	cmd_count(char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			return (count);
		if (str[i] == 34 || str[i] == 39)
			i = skip_quotes(str, i);
		if (i == -1)
			return (-1);
		if ((str[i] == c && str[i - 1] != c && str[i + 1] != c)
			|| str[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static int	cmd_len(char *str, char c, int i)
{
	i++;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			i = skip_quotes(str, i);
		if (str[i] == c && str[i - 1] != c && str[i + 1] != c)
			return (i);
		i++;
	}
	return (i);
}

static char	**split_cmds(char **cmds, char *str, char c, int count)
{
	int		i;
	int		j;
	int		x;

	i = 0;
	x = 0;
	while (x < count && str[i])
	{
		if ((str[i] == c && str[i - 1] != c && str[i + 1] != c) || i == 0)
		{
			if (str[i] == c)
				i++;
			j = cmd_len(str, c, i);
			cmds[x] = ft_substr(str, i, j - i);
			if (!cmds[x])
				return (NULL);
			x++;
			i = j - 1;
		}
		if (str[i] == 34 || str[i] == 39)
			i = skip_quotes(str, i);
		i++;
	}
	cmds[x] = NULL;
	return (cmds);
}

char	**ft_split_sc(char *str, char c)
{
	int		cmds_count;
	char	**cmds;

	cmds_count = cmd_count(str, c);
	if (cmds_count == -1)
		return (NULL);
	cmds = (char **)ft_calloc((cmds_count + 1), sizeof(char *));
	if (!cmds_count)
		return (NULL);
	cmds = split_cmds(cmds, str, c, cmds_count);
	return (cmds);
}

// int	main(void)
// {
// 	char	str[1000];
// 	char	**cmds;

// 	scanf("%99[^\n]", str);
// 	cmds = ft_split_sc(str, '|');
// 	for (int i = 0; cmds[i]; i++)
// 		printf("%s\n", cmds[i]);
// 	for (int i = 0; cmds[i]; i++)
// 		free (cmds[i]);
// 	free (cmds);
// 	return (1);
// }
