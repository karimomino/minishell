/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 15:53:21 by kamin             #+#    #+#             */
/*   Updated: 2021/10/16 02:09:59 by kamin            ###   ########.fr       */
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
	while (*s == c && *s != '\0')
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

	while (*sc != '\0' && *sc == c)
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
	while (*sc == c)
		sc++;
	while (i < wc && *sc != '\0')
	{
		wl = ft_word_len(sc, c);
		split[i] = (char *)malloc((wl + 1) * sizeof(char));
		while (*sc == c && c != 0)
			sc++;
		ft_strlcpy(split[i], sc, wl + 1);
		sc += wl;
		while (*sc == c && c != 0)
			sc++;
		i++;
	}
	split[i] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		wc;
	char	*sc;
	char	**split;

	sc = (char *)s;
	wc = ft_word_count(sc, c);
	split = ft_alloc_split(sc, wc, c);
	if (wc == 0 || *sc == '\0')
		return (split);
	split = ft_alloc_words(split, sc, c, wc);
	return (split);
}

// #include "ft_strlcpy.c"
// #include "ft_strlen.c"
// int main()
// {
// 	char * * tab = ft_split("    ", ' ');
// 	return (0);
// }
