/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:02:07 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/12 15:15:16 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_cmd_has_redir(t_cmd *cmd);
int		ft_count_pipes(t_cmd *cmd_lst);
void	ft_set_cmd_index(t_minishell *ms);

int	ft_cmd_has_redir(t_cmd *cmd)
{
	if (cmd->file_in)
		return (YES);
	if (cmd->file_tr)
		return (YES);
	if (cmd->heredoc[0])
		return (YES);
	if (cmd->file_ap)
		return (YES);
	return (NO);
}

int	ft_count_pipes(t_cmd *cmd_lst)
{
	int		n_cmds;
	int		n_pipes;
	t_cmd	*curr;

	n_cmds = 0;
	curr = cmd_lst;
	while (curr)
	{
		n_cmds++;
		curr = curr->next;
	}
	if (n_cmds < 2)
		n_pipes = 0;
	else
		n_pipes = n_cmds - 1;
	return (n_pipes);
}

void	ft_set_cmd_index(t_minishell *ms)
{
	int		i;
	t_cmd	*curr;

	i = 0;
	curr = ms->cmd_lst;
	while (curr)
	{
		curr->index = i;
		i++;
		curr = curr->next;
	}
}

// Retrieves the exit status of the child processes.

// void	get_exit_status(t_minishell *ms)
// {
// 	int		i;
// 	pid_t	pid;
// 	int		status;

// 	i = 0;
// 	status = 0;
// 	while (i < ms->n_cmd)
// 	{
// 		signal(SIGINT, &handler_sigint);
// 		pid = waitpid(ms->pid[i++], &status, 0);
// 		if (pid < 0)
// 			continue ;
// 		if (WIFEXITED(status))
// 			g_exit = WEXITSTATUS(status);
// 		else if (WIFSIGNALED(status))
// 			g_exit = 128 + WTERMSIG(status);
// 	}
// }
