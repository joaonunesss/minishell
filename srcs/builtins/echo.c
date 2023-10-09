/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:32:41 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/09 16:13:00 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_find_n(char **args)
{
	int		k;
	int 	i;
	int		newline_flag;

	k = 1;
	newline_flag = 1;
	while (args[k])
	{
		i = 0;
		while (args[k][i])
		{
			if (args[k][i] == '-' && args[k][i + 1] == 'n')
			{
				newline_flag = 0;
				break ;
			}
			i++;
		}
		k++;
	}
	return (newline_flag);
}

void	ft_echo(t_minishell *ms)
{
	int	i;
	int	newline_flag;

	i = 0;
	newline_flag = ft_find_n(ms->cmd_lst->args);
	if (newline_flag)
		i = 1;
	else
	{
		i = 2;
		while(ms->cmd_lst->args[i][0] == '-' && ms->cmd_lst->args[i][1] == 'n')
			i++;
	}
	while (ms->cmd_lst->args[i])
	{
		if (ms->cmd_lst->args[i][0] == '\0')
			i++;
		if (!ms->cmd_lst->args[i + 1] && ms->cmd_lst->args[i])
			printf("%s", ms->cmd_lst->args[i]);
		else if (ms->cmd_lst->args[i])
			printf("%s ", ms->cmd_lst->args[i]);
		i++;
	}
	if (newline_flag == 1)
		printf("\n");
	if (ms->n_pipes == 0)
		exit(0);
}
