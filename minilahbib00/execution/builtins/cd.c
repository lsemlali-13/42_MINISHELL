#include "../../Includes/minishell.h"

void	ex_cd(char **sp, t_envp *my_env)
{
	char	cwd[256];
	char	old_cwd[256];
	int		k;

	k = 0;
	if (sp[1] == NULL)
		chdir(getenv("HOME"));
	else {
		if (!getcwd(old_cwd, sizeof(old_cwd)))
		{
			if (sp[1] && sp[1][0] == '.' && ft_strlen(sp[1]) == 1) {
				my_env->env = ft_add2env(my_env->env, "PWD+=/.");
				my_env->env = ft_add2env(my_env->env, ft_strjoin("OLDPWD=", my_env->PWD));
				my_env->PWD = ft_strjoin(my_env->PWD, "/.");
				printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
				k++;
			}
		}
		if (chdir(sp[1]) == 0 && k == 0){
			getcwd(cwd, sizeof(cwd));
			printf("----->  %s\n", cwd);
			my_env->env = ft_add2env(my_env->env, ft_strjoin("PWD=", cwd));
			my_env->PWD = ft_strdup(cwd);
			my_env->env = ft_add2env(my_env->env, ft_strjoin("OLDPWD=", old_cwd));
		}
		else if (k == 0)
			printf("minishell: cd: %s: No such file or directory\n", sp[1]);
	}
	r = 0;
}