/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:44:36 by kamin             #+#    #+#             */
/*   Updated: 2022/06/15 20:13:39 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checker(char **argv)
{
	int	found;
	int	i;
	int	j;

	i = 0;
	found = 0;
	while (argv[i] && argv[i + 1] != 0 && !found)
	{
		j = i + 1;
		while (argv[j])
		{
			if (!ft_strcmp(argv[i], argv[j]))
				found = 1;
			j++;
		}
		i++;
	}
	return (found);
}

/*
** This Function Check If There Is More Than One Number Then Calls
** A Function To Check For Duplicates
** Params:
** 	NAME		TYPE		DESCRIPTION
** 	ac			INT			How many arguments were passed by the user
** 	ac			CHAR**		The arguments passed by the user
*/
int	ft_checkdup(int ac, char **argv)
{
	int		found;

	found = 0;
	if (ac > 2)
		found = checker(argv);
	return (found);
}
