/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards_dirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 21:07:33 by tmalless          #+#    #+#             */
/*   Updated: 2023/06/30 21:20:18 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**add_dir(char *s, char **tab, int d_number)
{
	int	i;

	i = 0;
	d_number++;
	while (tab[i])
		i++;
	tab[i] = ft_strdup(s);
	return (tab);
}

int	fill_dir(char *dir, char **motif, int stars, int *z)
{
	z[1]--;
	while (++z[1] < dsize(motif))
	{
		if (z[1] == dsize(motif) - 1 && (stars == 0 || stars == 1))
		{
			if (ft_strncmp(motif[dsize(motif) - 1], &dir[ft_strlen(dir)
						- ft_strlen(motif[dsize(motif) - 1])],
					ft_strlen(motif[dsize(motif) - 1])) != 0)
				return (0);
			else
				return (1);
		}
		else
		{
			if (!ft_strnstr(&dir[z[0]], motif[z[1]], ft_strlen(dir) - z[0]))
				return (0);
			else
			{
				dir = ft_strnstr(&dir[z[0]], motif[z[1]],
						ft_strlen(dir) - z[0]) + ft_strlen(motif[z[1]]);
				z[0] = 0;
			}
		}
	}
	return (1);
}

int	corresponding_dir(char *dir, char **motif, int stars)
{
	int	z[2];
	int	ret;

	z[0] = 0;
	z[1] = 0;
	if (!motif)
		return (1);
	if (dir[0] == '.')
		return (0);
	if ((stars == 0 || stars == 2) && motif[0])
	{
		if (ft_strncmp(motif[0], dir, ft_strlen(motif[0])) != 0)
			return (0);
		else
		{
			z[0] = ft_strlen(motif[0]) - 1;
			z[1] = 1;
		}
	}
	ret = fill_dir(dir, motif, stars, z);
	if (ret == 0)
		return (0);
	else
		return (1);
}
