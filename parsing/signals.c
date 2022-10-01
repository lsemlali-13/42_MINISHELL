/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:44:16 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/01 23:02:25 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_ctrl_c(int sig)
{
	(void)sig;
	if (g_sts->ginp == -1)
		write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
}

void	signal_ctrl_c_heredoc(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("\0", 0);
	g_sts->ginp = SIGHEREDOC;
	g_sts->ginp = dup(0);
	g_sts->status = 1;
	close(0);
}

void	signal_quit(int sig)
{
	(void)sig;
	printf("Quit: 3\n");
	rl_replace_line("\0", 0);
}

void	signal_(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("\0", 0);
}

void	handle_signals(int sig)
{
	if (sig == SIGINT)
		signal(SIGINT, signal_ctrl_c);
	else if (sig == SIGQUIT_INCHILD)
		signal(3, signal_quit);
	else if (sig == SIGINT_)
		signal(SIGINT, signal_);
	else if (sig == SIGQUIT)
		signal(SIGQUIT, SIG_IGN);
	else if (sig == SIGHEREDOC)
		signal(SIGINT, signal_ctrl_c_heredoc);
}
