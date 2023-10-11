/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:33:31 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/11 15:17:11 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_isnum(char *arg)
{
	int i;

	i = 0;
	while(arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return(1);
		i++;
	}
	return(0);
}

void	ft_exit(t_minishell *ms)
{
	if(is_there_redirections(ms) == TRUE)
	{
		printf("exit\n");
		g_exit_status = 0;
		exit(g_exit_status);
	}
	if (ms->cmd_lst->args[1] && ((ft_atoi(ms->cmd_lst->args[1])) || (ms->cmd_lst->args[1][0] == '0' && !ms->cmd_lst->args[1][1])))
		g_exit_status = ft_atoi(ms->cmd_lst->args[1]);
	else
		g_exit_status = 0;
	if(ms->n_pipes != 0)
		exit(g_exit_status);
	if (ms->cmd_lst->args[1] == NULL)
	{
		printf("exit\n");
		if(ms->n_pipes > 0)
			ft_free_pipes(ms);
		ft_free_all(ms, YES);
		exit(g_exit_status);
	}
	if (ms->cmd_lst->args[1] != NULL && ft_isnum(ms->cmd_lst->args[1]))
	{
		printf("minishel: exit: %s: numeric argument required\n", ms->cmd_lst->args[1]);
		g_exit_status = 2;
		return ;
	}
	else if (ms->cmd_lst->args[2] != NULL)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	ft_free_all(ms, YES);
	exit(g_exit_status);
}
