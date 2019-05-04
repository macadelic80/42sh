/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:57:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/05 01:50:38 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** les 5 premiers sont des TOKEN_CTL_OPERATOR
** cad des token de d'operateur de controle
** les 10 suivant sont des TOKEN_REDIR cad des token de d'operateur de redirection
** OTHER_OP c'est tout ce qui n'est pas un TOKEN_REDIR ou un TOKEN_CTL_OPERATOR
*/
typedef enum
{
	SEMI,
	DBL_SEMI,
	PIPE,
	DBL_PIPE,
	AND,
	DBL_AND,
	LESS,
	DBL_LESS,
	GREAT,
	DBL_GREAT,
	LESS_AND,
	GREAT_AND,
	LESS_GREAT,
	DBL_LESS_DASH,
	DBL_GREAT_DASH,
	CLOBBER,
	OTHER_OP,
} e_op_type;

typedef enum
{
	TOKEN_EAT,
	TOKEN_DQ,
	TOKEN_SQ,
	TOKEN_CTL_OPERATOR,
	TOKEN_NEG,
	TOKEN_OP_ARITHM,
	TOKEN_OP_BRA,
	TOKEN_CL_BRA,
	TOKEN_OP_PAR,
	TOKEN_CL_PAR,
	TOKEN_REDIR,
	TOKEN_ASS_WORD,
	TOKEN_OP_CMD,
	TOKEN_OP_CURLY,
	TOKEN_CL_CURLY,
	TOKEN_EQUAL,
	TOKEN_WORD,
	TOKEN_FOR,
	TOKEN_WHILE,
	TOKEN_NULL
} e_token_type;

typedef struct		s_token
{
	char			*content;
	char			is_op;
	e_op_type		op_type;
	size_t			len;
	e_token_type	type;
}					t_token;

typedef struct		s_oplist
{
	char			*op;
	size_t			len;
	e_token_type	type;
	e_op_type		op_type;
}					t_oplist;

int			build_lexer(char *input, t_list **lexer);
void 		print_lexer(t_list *lexer);
void 	lex_delone(void *data, size_t size);
void  lex_del_list(t_list **lexer);
