/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:23:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/01 17:20:26 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		enter_event(t_curs *curseur, char *command)
{
	command[curseur->x] = '\0';
	curseur->x = 0;
	ft_putchar('\n');
	handler(command);
	display_prompt_prefix();
	return (1);
}

int		backspace_event(t_curs *curseur, char *command)
{
	(void)command;
	if (curseur->x > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_put_termcaps);
		tputs(tgetstr("dc", NULL), 1, ft_put_termcaps);
		curseur->x--;
	}
	return (1);
}

int		ctrl_r_event(t_curs *curseur, char *command)
{
	(void)command;
	(void)curseur;
	ft_printf("ctrl_r\n");
	display_prompt_prefix();
	return (1);
}

int		tab_event(t_curs *curseur, char *command)
{
	(void)command;
	(void)curseur;
	ft_printf("tab\n");
	display_prompt_prefix();
	return (1);
}

int		home_event(t_curs *curseur, char *command)
{
	(void)command;
	(void)curseur;
	ft_printf("home\n");
	display_prompt_prefix();
	return (1);
}

int		end_event(t_curs *curseur, char *command)
{
	(void)command;
	(void)curseur;
	ft_printf("end\n");
	display_prompt_prefix();
	return (1);
}