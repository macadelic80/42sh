/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 23:37:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/06 22:26:27 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ast *newnode(t_token *item) 
{ 
	t_ast *temp =  (t_ast *)malloc(sizeof(t_ast)); 
	if (item)
	{
		temp->token = item;
	}
		else
		temp->token = NULL;
	temp->left = temp->right = NULL; 
	return temp;
}



void	build_tree_op(t_list *lexer, t_ast *root, e_op_type optype)
{
	t_list *save2;
	t_list *save1;
	t_token token;
	t_list *prev;

	save2 = NULL;
	save1 = NULL;
	prev = lexer;
	printf("============================\n");
	while(lexer)
	{
		token = *(t_token*)(lexer->content);
		printf("test: %s\n", token.content);
		if (token.op_type == optype)
		{
			save1 = prev;
			save2 = lexer->next;
		}
		prev = lexer;
		lexer = lexer->next;
	}
	printf("============================\n");
	prev = save1;
	save1 = save1->next;
	prev->next = NULL;
	if (save1)
	{
		root->left = newnode((t_token *)(save1->content));
		root->left->right = newnode((t_token *)(save2->content));
	}
}
int		is_in_lexer(t_list *lexer, e_op_type optype)
{
	t_token *token;
	while (lexer)
	{
		token = (t_token *)(lexer->content);
		if (token->op_type == optype)
			return (1);
		lexer = lexer->next;
	}
	return (0);
}

void inorder(t_ast *root) 
{ 
	if (root != NULL) 
	{ 
		inorder(root->left);
		if (root->token)
			printf("%s \n", root->token->content);
		inorder(root->right);
	} 
}

void ast (t_list *lexer, t_ast *root, e_op_type optype)
{
	if (is_in_lexer(lexer, optype))
		build_tree_op(lexer, root, optype);
	if (root->left)
		ast(lexer, root->left, optype);
}




/*
** Cherche si un erreur de syntax existing_token
** Renvoie une erreur si un TOKEN_REDIR est pas suivie d'un TOKEN_WORD ou
** si deux TOKEN_CTL_OPERATOR se suivent (pour l'instant)
*/

char		*check_syntax_errors(t_list *tokens)
{
  t_token *curr;
  t_token *next;

	if (tokens && ((t_token *)(tokens->content))->type == TOKEN_CTL_OPERATOR)
		return (((t_token *)(tokens->content))->content);
	while (tokens && tokens->next)
	{
		curr = (t_token *)(tokens->content);
		next = (t_token *)(tokens->next->content);
		if (curr->type == TOKEN_REDIR && next->type != TOKEN_WORD)
			return (next->content);
		if (curr->type == TOKEN_CTL_OPERATOR && next->type == TOKEN_CTL_OPERATOR)
			return (next->content);
		tokens = tokens->next;
	}
	return (NULL);
}


void  ft_parse(t_list *lexer)
{
	char *error;
	t_ast *root;

	error = check_syntax_errors(lexer);
	if (error)
	{
	ft_putstr_fd(ANSI_RED"21sh: parse error near'", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd("'", 2);
	}
	root = newnode(NULL);
	ast(lexer, root, SEMI);
	inorder(root);
}
