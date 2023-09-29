/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:33:31 by ataboada          #+#    #+#             */
/*   Updated: 2023/09/29 16:38:28 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_exit(t_minishell *ms, t_cmd *cmd_ptr)
// {
// 	(void)ms;
// 	printf("executing %s\n", cmd_ptr->cmd);
// }

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
	int	status;

	if (ms->cmd_lst->args[1] && ((ft_atoi(ms->cmd_lst->args[1])) || (ms->cmd_lst->args[1][0] == '0' && !ms->cmd_lst->args[1][1])))
		status = ft_atoi(ms->cmd_lst->args[1]);
	else
		status = 0;
	if (ms->cmd_lst->args[1] == NULL)
	{
		printf("exit\n");
		exit(status);
	}
	else if (ms->cmd_lst->args[2] != NULL)
	{
		printf("exit: too many arguments\n");
		status = 1;
		return ;
	}
	if (ms->cmd_lst->args[1] != NULL && ft_isnum(ms->cmd_lst->args[1]))
	{
		printf("exit: ");
		printf("%s", ms->cmd_lst->args[1]);
		printf(": numeric argument required\n");
		status = 2;
	}
	// ft_freebeforeexit(ms);
	exit(status);
}
