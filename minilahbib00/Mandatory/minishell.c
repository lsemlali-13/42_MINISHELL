/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/20 10:34:45 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "readline/history.h"
#include <string.h>
#include <ctype.h>

int	ft_isvalid(int c)
{
	if ((c <= 'z' && c >= 'a') || (c >= 'A' && c <= 'Z') || c == '_'
	|| (c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}


char* ft_replace(char* s, char* old, char* new)
{
	char*	result;
	int 	i;
	int		count;

    count = 0;
    i = 0;
    while (s[i] != '\0')
    {
        if (ft_strnstr(&s[i], old, ft_strlen(&s[i])) == &s[i])
        {
            count++;
            i += ft_strlen(old) - 1;
        }
        i++;
    }
    result = (char*)malloc(i + count * (ft_strlen(new) - ft_strlen(old)) + 1);
    i = 0;
    while (*s)
    {
        if (ft_strnstr(s, old, ft_strlen(s)) == s)
        {
            strcpy(&result[i], new);
            i += ft_strlen(new);
            s += ft_strlen(old);
        }
        else
            result[i++] = *s++;
    }
    result[i] = '\0';
    return result;
}

int ft_getidx(t_exp *exp, char *s, char *env[])
{
    int i;

    i = 0;
    while (i < arr_size(env))
    {
        if (ft_strncmp(exp[i].var, s, (ft_strlen(s) + 1)) == 0)
            return (i);
        i++;
    }
    return (-1);
}

char *ft_exp(char *s, t_exp *exp, char *env[])
{
    int i;
    char *str;
    char *ss;
    int k;

    i = 0;
    k = 0;
    str = NULL;
    while (s[i])
    {
        k = 0;
        if (s[i] == '$')
        {
			while (s[i] == '$')
				i++;
            while (s[i] && ft_isvalid(s[i]))
            {
                i++;
                k++;
            }
            k++;
			if (k > 1) {
				str = ft_cpy(&s[i - k], k);
				k = ft_getidx(exp, str, env);
				if (k > -1) {
					s = ft_replace(s, str, exp[k].value);
					i += ft_strlen(exp[k].value) - ft_strlen(str);
				}
				else {
					s = ft_replace(s, str, "\0");
					i -= ft_strlen(str);
				}
			}
        }
        i++;
    }
    return (s);
}

void	fill_env(char *env[], t_envp *my_env)
{
	int i;

	i = 0;
	while (env[i])
	{
		my_env->env[i] = ft_cpy(env[i], ft_strlen(env[i]));
		i++;
	}
	my_env->env[i] = 0;
}


void	print_a(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void ft_getVar(char *env[], t_exp **exp)
{
    int i;
    int j;
    int k;

    k = 0;
    j = 0;
    i = 0;
    while (env[i])
    {
        while (env[i][j] != '=')
            j++;
        (*exp)[k].var = ft_cpy(env[i], j++);
        (*exp)[k].value = ft_cpy(&env[i][j], ft_strlen(&env[i][j]));
        j = 0;
        i++;
        k++;
    }
}

int	sea_rrch(char *s, int a)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == a)
			return (1);
		i++;
	}
	return (0);
}

int	ft_countt(char *s, int a)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] == a)
			count++;
		i++;
	}
	return (count);
}

void free_arr(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
}

size_t d_strlen(char** s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


void	fill_export(char *env[], t_envp *my_env)
{
	int i;

	i = 0;
	while (env[i])
	{
		my_env->export[i] = ft_strjoin("declare -x ", env[i]);
		i++;
	}
	my_env->env[i] = 0;
}

t_command*	get_data(t_command* command, char** cmd, int infile, int outfile)
{
	t_command	*tmp;

//	command->cmd = malloc((ft_d_strlen(cmd) + 1) * sizeof(char*));
	tmp = ft_lstnew(cmd, infile, outfile);

	ft_addfront(&command, tmp);

	return (command);
}

int	main(int ac, char *av[], char *env[])
{
	t_command*	command;
	char		**s;
	int 		k, j;
	t_envp		*my_env;

	my_env = malloc(sizeof (my_env));
	my_env->env = malloc((arr_size(env) + 1) * sizeof (char*));
	my_env->export = malloc((arr_size(env) + 1) * sizeof (char*));
	fill_env(env, my_env);
	fill_export(env, my_env);

//	k = open("makefile", O_RDONLY);
//	j = open("hell", O_RDWR | O_CREAT | O_TRUNC, 0600);
	command = malloc(sizeof (t_command));
	command = NULL;
	s = malloc(4 * sizeof(char*));
	s[0] = ft_strdup("exit");
//	s[1] = ft_strdup("PATH");
//	s[2] = ft_strdup("USER");
	s[1] = NULL;
	command = get_data(command ,s, 0, -1);
	s[0] = ft_strdup("fg");
//	s[1] = ft_strdup("-e");
	s[1] = NULL;
	command = get_data(command, s, 0, -1);
	s[0] = ft_strdup("awk");
	s[1] = ft_strdup("{print $1}");
	s[2] = NULL;
	command = get_data(command , s, 0, -1);
	s[0] = ft_strdup("wc");
	s[1] = ft_strdup("-l");
	s[2] = NULL;
	command = get_data(command , s, 0, -1);

//	s[0] = ft_strdup("cat");
//	s[1] = ft_strdup("-e");
//	s[2] = NULL;
//	command = get_data(s, 0, 1);]
//	int z = 0;
//
//	while (command)
//	{
//		command = command->next;
//	}
t_command *nn;

nn = command;
	pipes(0, command, my_env);
	pipes(0, nn->next, my_env);
//	print_arr(my_env->export);
	//print_a(my_env->env);
//	print_arr(my_env->env);

	//exp = malloc(sizeof(t_exp) * env_size(env));
    //ft_getVar(env, &exp);
//	while(1)
//	{
		//buf = readline("\033[0;33m minishell > \033[0m");
		//if (buf[0] == 0)
			//continue ;
        //add_history(buf);
        //buf = ft_exp(buf, exp, env);
		//k = ft_countt(buf, '|');
		//command->cmd = ft_split(buf, '|');
//		free(buf);
//	}
	return (0);
}
