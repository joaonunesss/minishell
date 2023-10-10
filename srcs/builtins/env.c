/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:33:11 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/10 18:24:58 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_exit_status;

void	ft_env(t_minishell *ms)
{
	t_env	*envi;
	
	envi = ms->env_lst;
	// if(is_there_redirections(ms) == TRUE)
	// {
	// 	while (envi)
	// 	{
	// 		printf("%s=%s\n", envi->key, envi->value);
	// 		envi = envi->next;
	// 	}
	// 	g_exit_status = 0;
	// 	if(ms->n_pipes > 0)
	// 		ft_free_pipes(ms);
	// 	ft_free_all(ms, YES);
	// 	exit(0);
	// }		
	while (envi)
	{
		printf("%s=%s\n", envi->key, envi->value);
		envi = envi->next;
	}
	g_exit_status = 0;
	if(ms->n_pipes > 0)
		ft_free_pipes(ms);
	ft_free_all(ms, YES);
	exit(0);
}
