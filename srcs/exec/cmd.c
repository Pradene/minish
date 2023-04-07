/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:11:08 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/07 15:08:36 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_cmd(t_data *data)
{
	char	*prompt;
	char	*s;

	prompt = get_prompt();
	if (!prompt)
		error(NULL);
	s = readline(prompt);
	free(prompt);
	if (!s)
		ex();
	/* cmd = lexer(s);
	printf("zebi : %s\n", cmd);
	get_tokens(&tokens, cmd);
	parse(&data->cmds, tokens);
	ft_lstclear(&tokens);
	// EXECUTION
	// builtin(&data->env, s);
	// execute(s, data->env);
	print_cmds(data->cmds);
	clear_cmds(&data->cmds); */
	parse(&data->root, &s);
	add_history(s);
	free_tree(&data->root);
	free(s);
}
