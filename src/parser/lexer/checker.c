/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumouss <aoumouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:51:39 by aoumouss          #+#    #+#             */
/*   Updated: 2022/06/30 15:29:57 by aoumouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipe(t_list **tokens, char *line, int *index)
{
	int			i;
	t_token		*token;

	i = *index;
	if (line[i] == '|' && line[i + 1] != '|')
	{
		token = create_token(LEX_PIPE, ft_strdup("|"));
		ft_lstadd_back(tokens, ft_lstnew(token));
		*index = *index + 1;
	}
}

void	check_redir(t_list **tokens, char *line, int *index)
{
	t_token		*token;

	if (line[*index] == '>' || line[*index] == '<')
	{
		if (line[*index] == '>' && line[*index + 1] == '>')
		{
			token = create_token(LEX_REDIR, ft_strdup(">>"));
			*index = *index + 2;
			return (ft_lstadd_back(tokens, ft_lstnew(token)));
		}
		if (line[*index] == '<' && line[*index + 1] == '<')
		{
			token = create_token(LEX_REDIR, ft_strdup("<<"));
			*index = *index + 2;
			return (ft_lstadd_back(tokens, ft_lstnew(token)));
		}
		if (line[*index] == '>' && line[*index + 1] != '>')
			token = create_token(LEX_REDIR, ft_strdup(">"));
		else if (line[*index] == '<' && line[*index + 1] != '<')
			token = create_token(LEX_REDIR, ft_strdup("<"));
		ft_lstadd_back(tokens, ft_lstnew(token));
		*index = *index + 1;
	}
}

void	check_word(t_list **tokens, char *line, int *index)
{
	t_token		*token;
	int			i;
	int			word_len;

	i = *index;
	word_len = 0;
	while (!is_spicial(line[i]) && !ft_isspace(line[i]) && line[i])
	{
		i++;
		word_len++;
	}
	if (!word_len)
		return ;
	token = create_token(LEX_WORD, ft_substr(line, *index, word_len));
	ft_lstadd_back(tokens, ft_lstnew(token));
	*index = *index + word_len;
}

void	check_and_or(t_list **tokens, char *line, int *index)
{
	t_token		*token;

	if (line[*index] == '&' && line[*index + 1] == '&')
	{
		token = create_token(LEX_AND, ft_strdup("&&"));
		ft_lstadd_back(tokens, ft_lstnew(token));
		*index = *index + 2;
	}
	else if (line[*index] == '|' && line[*index + 1] == '|')
	{
		token = create_token(LEX_OR, ft_strdup("||"));
		ft_lstadd_back(tokens, ft_lstnew(token));
		*index = *index + 2;
	}
}

void	check_parentheses(t_list **tokens, char *line, int *index)
{
	t_token	*token;
	int		i;

	i = *index;
	if (line[i] == '(')
	{
		token = create_token(OPEN_PARENTHESIS, ft_strdup("("));
		ft_lstadd_back(tokens, ft_lstnew(token));
		*index = *index + 1;
	}
	else if (line[i] == ')')
	{
		token = create_token(CLOSE_PARENTHESIS, ft_strdup(")"));
		ft_lstadd_back(tokens, ft_lstnew(token));
		*index = *index + 1;
	}
}
