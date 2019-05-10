/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 06:45:33 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/10 09:02:22 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	remove_escape(char **str, int *start)
{
	char *tmp;
	char is_newline;

	is_newline = (*str)[*start + 1] == '\n';
	tmp = *str;
	*str = ft_strnew(ft_strlen(*str) - (1 - is_newline));
	ft_strncpy(*str, tmp, *start);
	ft_strcpy(*str + *start, tmp + *start + 1 + is_newline);
	free(tmp);
	(*start) += !is_newline;
}

static void remove_chunk(char **str, int start, int end)
{
	char *tmp;

	tmp = *str;
	*str = ft_strnew(ft_strlen(*str) - 2);
	ft_strncpy(*str, tmp, start);
	ft_strncpy((*str) + start, tmp + start + 1, end - start - 1);
	ft_strcpy((*str) + end - 1, tmp + end + 1);
	free(tmp);
}

static int	is_special_char(char c)
{
	return (c == '$' || c == '\\' || c == '"' || c == '`' || c == '\n');
}

static void	remove_double(char **str, int *i)
{
	int start;

	start = *i;
	(*i)++;
	while ((*str)[*i] && (*str)[*i] != '"')
	{
		if ((*str)[*i] == '\\' && is_special_char((*str)[*i + 1]))
			remove_escape(str, i);
		else
			(*i)++;
	}
	remove_chunk(str, start, *i);
	(*i)--;
}

static void	remove_single(char **str, int *i)
{
	int start;

	start = *i;
	(*i)++;
	while ((*str)[*i] && (*str)[*i] != '\'')
		(*i)++;
	remove_chunk(str, start, *i);
	(*i)--;
}

void 		remove_quote(char **str)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && (*str)[i + 1])
			remove_escape(str, &i);
		else if ((*str)[i] == '\'')
			remove_single(str, &i);
		else if ((*str)[i] == '"')
			remove_double(str, &i);
		else
			i++;
	}
}

void 	redir_delone(void *data, size_t size)
{
	t_redir *redir;

	(void)size;
  if (data)
  {
    redir = ((t_redir *)(data));
    free(redir->dest);
	free(data);
  }
}