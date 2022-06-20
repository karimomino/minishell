/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_rd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 03:07:15 by ommohame          #+#    #+#             */
/*   Updated: 2022/06/20 02:58:15 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/parser.h"

int	skip_quotes(char *str, int i)
{
	char	c;

	c = str[i++];
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] != c)
		return (-1);
	return (i);
}

static int	rd_count(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == 34 || str[i] == 39)
			i = skip_quotes(str, i);
		if (i == -1)
			return (-1);
		if (str[i] == '>' || str[i] == '<' || str[i + 1] == '\0')
		{
			count++;
			while (str[i] == '>' || str[i] == '<')
				i++;
		}
		i++;
	}
	return (count);
}

static int	rd_len(char *str, int i)
{
	while (str[i] == '>' || str[i] == '<')
		i++;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			i = skip_quotes(str, i);
		if (str[i] == '<' || str[i] == '>')
			return (i);
		i++;
	}
	return (i);
}

static char	**split_rds(char **rds, char *str, int count)
{
	int		i;
	int		j;
	int		x;

	i = 0;
	x = 0;
	while (x < count && str[i])
	{
		if (str[i] == '>' || str[i] == '<' || i == 0)
		{
			j = rd_len(str, i);
			if (i == 0)
				rds[x] = ft_substr(str, i, j - i - 1); 
			else
				rds[x] = ft_substr(str, i, j - i); 
			if (!rds[x])
				return (NULL);		
			rds[x] = ft_strtrim(rds[x], " ");
			i = j - 1;
			x++;
		}
		if (str[i] == 34 || str[i] == 39)
			i = skip_quotes(str, i);
		i++;
	}
	rds[x] = NULL;
	return (rds);
}

char	**ft_split_rd(char *str)
{
	int		rds_count;
	char	**rds;

	rds_count = rd_count(str);
	if (rds_count == -1)
		return (NULL);
	rds = (char **)malloc(sizeof(char) * (rds_count + 1));
	if (!rds_count)
		return (NULL);
	rds = split_rds(rds, str, rds_count);
	for (int i = 0; rds[i]; i++)
		ft_printf("rds[%d]: %s\n", i, rds[i]);
	return (rds);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	str[1000];
// 	char	**rds;

// 	scanf("%99[^\n]", str);
// 	rds = ft_split_rd(str);
// 	for (int i = 0; rds[i]; i++)
// 	{
// 		printf("%s\n", rds[i]);
// 		free(rds[i]);
// 	}
// 	free(rds);
// 	return (1);
// }