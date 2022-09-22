/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tac.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/22 15:50:15 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// print All data of linked list 
void	print_node(t_command *lst, t_envp* my_env)
{
	t_command*	list;
	int			i;

	if (lst == NULL)
		return;
	list = lst;
	(void)my_env;
	printf("\033[0;31m|--__---### All Data of Linked List Structre ###---__--|\033[0m\n");
	while (list != NULL)
	{
		i = 0;
		printf("COMMAND: ");
		while (list->cmd[i])
		{
			printf("[%s]=%d  ", list->cmd[i], list->splite[i]);
			i++;
		}
		printf(", INfile: %d, OUTfile: %d", list->infile, list->outfile);
		printf("\n");
		list = list->next;
	}
}

void	free_list(t_command* list)
{
	int	i;

	i = 0;
	while (list->cmd[i]){
		free(list->cmd[i]);
		i++;
	}
	free(list->cmd);
	free(list);
}

int		check_syntax_error(char *src, t_envp* my_env, int *i); /// ajoute ou part tac.h
char*	here_doc(char* src, int stop, t_envp* my_env);   /// ajoute ou part tac.h

void	tac_compile(char* src, t_envp* my_env)
{
	t_lexer*	lexer;
	t_token*	token;
	t_command*	list;
	int			i;

	i = 0;
	if (check_syntax_error(src, my_env, &i) == -1){
		src = here_doc(src, i, my_env);
		return;
	}
	else
		src = here_doc(src, ft_strlen(src), my_env);
	if (!src)
		return;
	lexer = init_lexer(src);
	lexer->not_expand = 0;
	lexer_skip_whitespace(lexer);
	lexer->my_env = my_env;
	token = lexer_next_token(lexer);
	list = (t_command*)malloc(sizeof(t_command));
	list = NULL;
	while(token->type != TOKEN_EOF)
	{
//		printf("\033[0;32m|---__LEXER__---###\033[0m %s \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(token));
		list = parser(lexer, token, list);
		token = lexer_next_token(lexer);
	}

	// lexer free ms not just here
	free(lexer);
	free(token);

	// printf("\033[0;34m                     ---------------------\n                     | LINKED_LIST FINAL |\n                     ---------------------\n\033[0m");
	// print_node(list, my_env);
	if (list)
	{	
		execution(list, my_env);
		free_list(list);
	}
}
