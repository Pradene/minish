/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:40:37 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/18 19:41:15 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_attribute(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) < 0)
		return ;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
		return ;
}
