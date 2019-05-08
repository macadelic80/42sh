/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/08 02:43:47 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, sigint_handler);
		ft_printf("\n");
		display_prompt_prefix();
		exit(0);
	}
}

void	sigwinch_handler(int sig)
{
	if (sig == SIGWINCH)
	{
		ft_printf("redimensionnement: {%d, %d}", tgetnum("co"), tgetnum("li"));
		signal(SIGWINCH, sigwinch_handler);
		ft_printf("\n");
		display_prompt_prefix();
	}
}
