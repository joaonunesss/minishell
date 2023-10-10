/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:34:03 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/10 18:16:39 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_export_red(t_minishell *ms)
{
	t_env	*envi;

	envi = ms->env_lst;
	while (envi)
	{
		printf("declare -x ");
		printf("%s=%s\n", envi->key, envi->value);
		envi = envi->next;
	}
	g_exit_status = 0;
	if(ms->n_pipes > 0)
		ft_free_pipes(ms);
	ft_free_all(ms, YES);
	exit(0);
}

void	ft_export(t_minishell *ms)
{
	char	*key;
	char	*value;
	char	*equal_ptr;
	if(is_there_redirections(ms) == TRUE)
	{
		ft_export_red(ms);
	}
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
