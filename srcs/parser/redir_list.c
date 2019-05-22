/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 01:22:04 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/15 06:46:38 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		create_redir(t_list **redirs, char **dest, size_t size,
														e_op_type redir_type)
{
	t_redir redir;
	t_list *node;

	redir.dest = dup_tab(dest, size);
	redir.op_type = redir_type;
	if (redir_type == OTHER_OP)
		redir.end_of_leaf = 1;
	else
		redir.end_of_leaf = 0;
	node = ft_lstnew((void *)&redir, sizeof(redir));
	if (!node)
		ft_exit("Failed to malloc a node for my redir list");
	ft_lstadd(redirs, node);
}

static t_list		*get_next_redir(t_list *lexer)
{
	t_list *save;
	t_token *curr;

	save = lexer;
	while(lexer)
	{
		curr = (t_token *)lexer->content;
		if (curr->type == TOKEN_REDIR)
			return (save);
		else if (curr->type == TOKEN_CTL_OPERATOR)
			save = lexer->next;
		lexer = lexer->next;
	}
	return (NULL);
}

static void		join_2(t_list *lexer)
{
	t_token *curr;
	t_token *next;
	t_list *tmp;
	char	**old;

	curr = (t_token *)lexer->content;
	next = (t_token *)lexer->next->content;
	curr->type = TOKEN_WORD;
	curr->redir = 1;
	tmp = lexer->next;
	lexer->next = tmp->next;
	old = curr->content;
	curr->content = join_2tab(curr->content, next->content, curr->size,
																	next->size);
	ft_splitdel(old);
	curr->size = curr->size + next->size;
	ft_lstdelone(&tmp, lex_delone);
}

void		join_all_redir(t_list *lexer)
{
	t_token *curr;
	t_token *next;

	while (lexer && lexer->next)
	{
		curr = (t_token *)lexer->content;
		next = (t_token *)lexer->next->content;
		if ((curr->type == TOKEN_WORD || curr->type == TOKEN_REDIR)
			&& (next->type == TOKEN_WORD || next->type == TOKEN_REDIR))
		{
			join_2(lexer);
			continue ;
		}
		lexer = lexer->next;
	}
}

t_list		*create_redir_list(t_list *lexer)
{
	t_list *redir;
	t_token *curr;
	t_token *next;
	char	**cmd;
	t_list	*prev;
	size_t	cmd_size;
	char	to_free;

	redir = NULL;
	prev = NULL;
	cmd = NULL;
	lexer = get_next_redir(lexer);
	to_free = 0;
	while (lexer)
	{
		curr = (t_token *)lexer->content;
		if (curr->type == TOKEN_WORD && (!prev || (prev
			&& ((t_token *)prev->content)->type != TOKEN_REDIR)))
			{
				if (!cmd)
				{
					cmd = curr->content;
					cmd_size = curr->size;
				}
				else
				{
					cmd = join_2tab(cmd, curr->content, cmd_size, curr->size);
					cmd_size += curr->size;
					to_free = 1;
				}
			}
		if (curr->type == TOKEN_REDIR)
		{
			next = (t_token *)lexer->next->content;
			create_redir(&redir, next->content, next->size, curr->op_type);
		}
		else if (curr->type == TOKEN_CTL_OPERATOR
			|| (curr->type != TOKEN_CTL_OPERATOR && !lexer->next))
		{
			create_redir(&redir, cmd, cmd_size, OTHER_OP);
			if (to_free && !(to_free = 0))
				ft_splitdel(cmd);
			cmd = NULL;
			lexer = get_next_redir(lexer);
			prev = NULL;
			continue ;
		}
		prev = lexer;
		lexer = lexer->next;
	}
	ft_lstrev(&redir);
	return (redir);
}
