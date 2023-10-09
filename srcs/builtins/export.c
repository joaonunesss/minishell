/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:03 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/09 17:46:47 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_minishell *ms)
{
	char	*key;
	char	*value;
	char	*equal_ptr;

	ft_unset(ms);
	if(ms->cmd_lst->args[1][0] == '-')
	{
		printf("minishell: export: no options supported\n");
		return ;
	}
	equal_ptr = ft_strchr(ms->cmd_lst->args[1], '=');
	key = ft_substr(ms->cmd_lst->args[1], 0, equal_ptr - ms->cmd_lst->args[1]);
	value = equal_ptr + 1;
	ft_add_env_back(&ms->env_lst, ft_new_env(key, value));
	free(key);
	// if(ms->n_pipes > 0)
	// 	ft_free_pipes(ms);
	if (ms->n_pipes != 0)
		exit(0);
}
