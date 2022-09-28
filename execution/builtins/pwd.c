/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:19:03 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/28 15:54:22 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ex_pwd(char **sp, t_envp *my_env, int out)
{
	char	*pwd;

	if (sp[1])
	{
		printf("pwd: too many arguments\n");
		my_env->status = 1;
	}
	else
	{
		pwd = getcwd(NULL, sizeof(my_env->pwd));
		if (!pwd)
			pwd = my_env->pwd;
		putstr_fd(pwd, out);
		write(out, "\n", 1);
		my_env->status = 0;
	}
}
