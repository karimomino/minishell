/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_q.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:30:53 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/16 05:06:08 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	word_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = skip_quotes(s, i);
		if ((s[i] == c && s[i]) || s[i + 1] == 0)
		{
			count++;
			while (s[i] == c && s[i + 1] == c)
				i++;
		}
		i++;
	}
	return (count);
}

static int	word_len(char *s, char c, int i)
{
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = skip_quotes(s, i);
		else if (s[i] == c && s[i])
			return (i);
		i++;
	}
	return (i);
}

static char	**splitbutnotsplit(char **str, char *s, char c, int i)
{
	int	x;

	x = 0;
	while (x < word_count(s, c) && s[i])
	{
		if (s[i] == c || i == 0)
		{
			while (s[i] == c && s[i])
				i++;
			str[x] = (char *)malloc(sizeof(char) * (word_len(s, c, i) - i + 1));
			if (!str[x])
				return (NULL);
			ft_strlcpy(str[x], s + i, (word_len(s, c, i) - i + 1));
			i = word_len(s, c, i) - 1;
			x++;
		}
		i++;
	}
	str[x] = NULL;
	return (str);
}

char	**ft_split_q(char *s, char c)
{
	int		i;
	char	**str;

	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!str)
		return (NULL);
	i = 0;
	splitbutnotsplit(str, s, c, i);
	return (str);
}
