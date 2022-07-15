/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:24:27 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/15 01:41:25 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*realloc_str(char *str, char *line)
// {
// 	size_t		i;
// 	size_t		j;
// 	size_t		len;
// 	char		*tmp;

// 	i = 0;
// 	while (str[i] && str[i] == line[i])
// 		i++;
// 	if (!str[i])
// 	{
// 		free(str);
// 		return (NULL);
// 	}
// 	len = gnl_strlen(str);
// 	tmp = (char *)malloc(sizeof(char) * (len - i + 1));
// 	if (!tmp)
// 		return (NULL);
// 	j = 0;
// 	while (str[i])
// 		tmp[j++] = str[i++];
// 	tmp[j] = 0;
// 	free (str);
// 	return (tmp);
// }

// char	*linooo(char *str)
// {
// 	size_t		i;
// 	char		*line;

// 	i = 0;
// 	if (!str[i])
// 		return (NULL);
// 	while (str[i] && str[i] != '\n')
// 		i++;
// 	if (str[i] == '\n')
// 		line = (char *)malloc(sizeof(char) * (i + 2));
// 	else
// 		line = (char *)malloc(sizeof(char) * (i + 1));
// 	if (!line)
// 		return (NULL);
// 	i = -1;
// 	while (str[++i] && str[i] != '\n')
// 		line[i] = str[i];
// 	if (str[i] == '\n')
// 		line[i++] = '\n';
// 	line[i] = 0;
// 	return (line);
// }

char	*reading(char *str, char *bfr, int fd)
{
	int		ret;

	ret = read(fd, bfr, BUFFER_SIZE);
	if (ret == -1)
	{
		free (bfr);
		return (NULL);
	}
	bfr[ret] = 0;
	str = gnl_strjoin(str, bfr);
	while (ret != 0)
	{
		ret = read(fd, bfr, BUFFER_SIZE);
		if (ret == -1)
		{
			free (bfr);
			return (NULL);
		}
		bfr[ret] = 0;
		str = gnl_strjoin(str, bfr);
	}
	free(bfr);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*bfr;
	char		*str;

	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bfr = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!bfr)
		return (NULL);
	str = reading(str, bfr, fd);
	if (!str)
		return (NULL);
	return (str);
}
