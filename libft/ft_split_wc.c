/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_wc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 22:13:55 by kamin             #+#    #+#             */
/*   Updated: 2022/03/17 13:05:36 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_len(char *s, char c)
{
	int	word_len;

	word_len = 0;
	while (*s == c)
		s++;
	while (*s != c && *s++ != 0)
		word_len++;
	return (word_len);
}

static int	ft_word_count(char const *s, char c)
{
	int	word_count;

	word_count = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		if (*s == c && *(s + 1) != c && *(s + 1) != '\0')
			word_count++;
		s++;
	}
	return (word_count + 1);
}

static char	**ft_alloc_split(char *sc, int wc, char c)
{
	char	**split;

	while (*sc == c)
		sc++;
	if (ft_strlen(sc) == 0)
		split = (char **)malloc(1 * sizeof(char *));
	else
		split = (char **)malloc((wc + 1) * sizeof(char *));
	if (wc == 0 || *sc == '\0')
		split[0] = NULL;
	return (split);
}

static char	**ft_alloc_words(char **split, char *sc, char c, int wc)
{
	int	i;
	int	wl;

	i = 0;
	while (i < wc)
	{
		while (*sc == c)
			sc++;
		if (*sc != '\0')
		{
			wl = ft_word_len(sc, c);
			split[i] = (char *)malloc((wl + 1) * sizeof(char));
			while (*sc == c && c != 0)
				sc++;
			ft_strlcpy(split[i], sc, wl + 1);
			sc += wl;
			while (*sc == c && c != 0)
				sc++;
		}
		i++;
	}
	split[i] = 0;
	return (split);
}

int	ft_split_wc(char const *s, char c, char ***sp)
{
	int		wc;
	char	*sc;

	sc = (char *)s;
	wc = ft_word_count(sc, c);
	*sp = ft_alloc_split(sc, wc, c);
	if (wc == 0 || *sc == '\0')
		return (0);
	*sp = ft_alloc_words(*sp, sc, c, wc);
	return (wc);
}
