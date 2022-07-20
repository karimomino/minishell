/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:20:25 by ommohame          #+#    #+#             */
/*   Updated: 2022/07/20 16:22:56 by ommohame         ###   ########.fr       */
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

int	is_builtin(char *str)
{
	int		i;
	char	**bins;

	i = 0;
	bins = builtins();
	if (!bins)
		return (-1);
	while (bins[i])
	{
		if (ft_strncmp(str, bins[i], ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen(bins[i]))
		{
			free_2d(bins);
			return (i + 1);
		}
		i++;
	}
	free_2d(bins);
	return (0);
}
