/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@42abudhabi.ae>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:20:25 by ommohame          #+#    #+#             */
/*   Updated: 2022/09/12 15:07:58 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static char	**builtins(void)
{
	char			**bins;

	bins = (char **)malloc(sizeof(char *) * 9);
	if (!bins)
		return (NULL);
	bins[0] = ft_strdup("echo");
	bins[1] = ft_strdup("cd");
	bins[2] = ft_strdup("pwd");
	bins[3] = ft_strdup("env");
	bins[4] = ft_strdup("export");
	bins[5] = ft_strdup("unset");
	bins[6] = ft_strdup("exit");
	bins[7] = ft_strdup("history");
	bins[8] = NULL;
	return (bins);
}

static char	*cmd_tolower(char *cmd)
{
	size_t	i;
	char	*str;

	i = 0;
	str = ft_strdup(cmd);
	if (!str)
		return (NULL);
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int	is_builtin(char *cmd)
{
	size_t	i;
	char	*str;
	char	**bins;

	bins = builtins();
	if (!bins)
		return (-1);
	str = cmd_tolower(cmd);
	if (!str)
		return (-1);
	i = 0;
	while (bins[i])
	{
		if (ft_strncmp(str, bins[i], ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen(bins[i]))
		{
			free(str);
			free_2d(bins);
			return (i + 1);
		}
		i++;
	}
	free(str);
	free_2d(bins);
	return (0);
}
