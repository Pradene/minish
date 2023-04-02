/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:11:08 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/14 22:11:22 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_cmd(t_data *data)
{
	char	*prompt;
	char	*s;
	t_list	*tokens;

	tokens = NULL;
	prompt = get_prompt();
	if (!prompt)
		error(NULL);
	s = readline(prompt);
	free(prompt);
	if (!s)
		ex();
	get_tokens(&tokens, s);
	parse(&data->cmds, tokens);
	ft_lstclear(&tokens);
	// EXECUTION
	// builtin(&data->env, s);
	// execute(s, data->env);
	print_cmds(data->cmds);
	clear_cmds(&data->cmds);
	add_history(s);
	free(s);
}
