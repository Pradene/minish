/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:13:36 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/14 22:13:48 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(void)
{
	char	dir[BUFFER_SIZE];

	if (getcwd(dir, BUFFER_SIZE) == NULL)
		return ;
	printf("%s\n", dir);
}
