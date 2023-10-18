/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:51:17 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/18 15:48:19 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_parser(t_minishell *ms, char *input);
int		ft_quote_checker(char *input);

/*
	When building a shell, the first step is parsing the input.
	Our parser has four main steps:
	1) Lexical analysis: The input is split into tokens (tokenizer).
	2) Syntax analysis: The tokens are checked for syntax errors (syntax checker)
	3) Expansion: the tokens are scanned for special characters and expanded
	   (expander).
	4) Command Table Construction: The tokens are converted into a command table (command_table_creator).
	Note: we also implemented here a quote checker, which will see if the input has any unclosed quotes (as the subject requires).
*/

int	ft_parser(t_minishell *ms, char *input)
{
	if (ft_quote_checker(input) == ERROR_FOUND)
		return (EXIT_FAILURE);
	ft_tokenizer(ms, input);
	if (ft_syntax_checker(ms, ms->token_lst) == ERROR_FOUND)
		return (EXIT_FAILURE);
	ft_expander(ms, ms->token_lst);
	if (ft_command_table_creator(ms) == EXIT_NO_CMD)
		return (EXIT_NO_CMD);
	if (ms->file_error == YES)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// int		ft_quote_checker(char *input)
// {
// 	int i;
// 	int closed_quote;

// 	i = 0;
// 	closed_quote = YES;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'' || input[i] == '\"')
// 		{
// 			if (closed_quote == YES)
// 				closed_quote = NO;
// 			else if (closed_quote == NO)
// 				closed_quote = YES;
// 		}
// 		i++;
// 	}
// 	if (closed_quote == NO)
// 		return (printf("%s\n", E_QUOTES) && EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

// int		ft_quote_checker(char *input)
// {
// 	int i;
// 	int closed_quote;

// 	i = 0;
// 	closed_quote = YES;
// 	while (input[i])
// 	{
// 		// printf("%c\n", input[i]);
// 		if (input[i] == '\'')
// 		{
// 			while(input[i])
// 			{
// 				// printf("input \'[%i] %c\n", i, input[i]);
// 				if (input[i] == '\'')
// 				{
// 					if (closed_quote == YES)
// 						closed_quote = NO;
// 					else if (closed_quote == NO)
// 					{
// 						closed_quote = YES;
// 						break ;
// 					}
// 				}
// 				i++;
// 			}
// 		}
// 		else if (input[i] == '\"')
// 		{
// 			while(input[i])
// 			{
// 				// printf("input \"[%i] %c\n", i, input[i]);
// 				if (input[i] ==  '\"')
// 				{
// 					if (closed_quote == YES)
// 						closed_quote = NO;
// 					else if (closed_quote == NO)
// 					{
// 						closed_quote = YES;
// 						break ;
// 					}
// 				}
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// 	// printf("close %i\n", closed_quote);
// 	if (closed_quote == NO)
// 		return (printf("%s\n", E_QUOTES) && EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

int		ft_quote_checker(char *input)
{
	int i;
	int closed_quote;
	int closed_dquote;
	int flag;

	i = 0;
	flag = 0;
	closed_quote = YES;
	closed_dquote = YES;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			flag = 1;
			while(input[i])
			{
				if (input[i] == '\'')
				{
					if (closed_quote == YES)
						closed_quote = NO;
					else if (closed_quote == NO)
					{
						closed_quote = YES;
						break;
					}
				}
				i++;
			}
		}
		else if(input[i] == '\"')
		{
			flag = 1;
			while(input[i])
			{
				if(input[i] == '\"')
				{
					if (closed_dquote == YES)
						closed_dquote = NO;
					else if (closed_dquote == NO)
					{
						closed_dquote = YES;
						break;
					}
				}
				i++;
			}
		}
		i++;
	}
	if (closed_quote == NO || closed_dquote == NO)
		return (printf("%s\n", E_QUOTES) && EXIT_FAILURE);
	if (flag == 0)
		return (2);
	return (EXIT_SUCCESS);
}