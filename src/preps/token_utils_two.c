/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:37:59 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/26 17:02:08 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*re_in_function(t_main_env **main_env, t_list_words **list_words)
{
	t_re_input	*re_input;

	re_input = (t_re_input *)malloc(sizeof(t_re_input));
	if (!re_input)
		return (NULL);
	if ((*list_words) != NULL && (*list_words)->next != NULL && \
								(*list_words)->next->word != NULL)
		re_input->file_name = ft_strdup((*list_words)->next->word);
	else
		re_input->file_name = ft_strdup("");
	if (re_input->file_name == NULL)
		return (error_handler_null(main_env, -10, "re_in_", "function"));
	(*list_words) = (*list_words)->next;
	return ((void *)re_input);
}

void	*re_out_function(t_main_env **main_env, t_list_words **list_words)
{
	t_re_output	*re_output;

	re_output = (t_re_output *)malloc(sizeof(t_re_output));
	if (!re_output)
		return (NULL);
	if ((*list_words) != NULL && (*list_words)->next != NULL && \
								(*list_words)->next->word != NULL)
		re_output->file_name = ft_strdup((*list_words)->next->word);
	else
		re_output->file_name = ft_strdup("");
	if (re_output->file_name == NULL)
		return (error_handler_null(main_env, -10, "re_out_", "function"));
	(*list_words) = (*list_words)->next;
	return ((void *)re_output);
}

void	re_here_helper_function(t_main_env **main_env, \
								t_re_here **re_here, \
								t_list_words **list_words)
{
	if (ft_strchr((*list_words)->next->word, '\'') || \
		ft_strchr((*list_words)->next->word, '"'))
	{
		(*re_here)->stop_word = \
				replace_vars(main_env, (*list_words)->next->word, -1, 2);
		(*re_here)->variable = 1;
	}
	else
	{
		(*re_here)->stop_word = ft_strdup((*list_words)->next->word);
		if ((*re_here)->stop_word == NULL)
			return ;
	}
}

void	*re_here_function(t_main_env **main_env, t_list_words **list_words)
{
	t_re_here	*re_here;

	re_here = (t_re_here *)malloc(sizeof(t_re_here));
	if (!re_here)
		return (NULL);
	re_here->variable = 0;
	re_here->tab = 0;
	re_here->file_name = NULL;
	re_here->stop_word = NULL;
	if ((*list_words) != NULL && (*list_words)->next != NULL)
	{
		re_here->tab = ((*list_words)->word[2] == '-');
		if ((*list_words)->next->word != NULL)
		{
			re_here_helper_function(main_env, &re_here, list_words);
			if (re_here->stop_word == NULL)
				return (error_handler_null(main_env, -10, "re_", "function"));
		}
	}
	(*list_words) = (*list_words)->next;
	return ((void *)re_here);
}

void	*re_app_function(t_main_env **main_env, t_list_words **list_words)
{
	t_re_append	*re_append;

	re_append = (t_re_append *)malloc(sizeof(t_re_append));
	if (!re_append)
		return (NULL);
	if ((*list_words) != NULL && (*list_words)->next != NULL && \
								(*list_words)->next->word != NULL)
		re_append->file_name = ft_strdup((*list_words)->next->word);
	else
		re_append->file_name = ft_strdup("");
	if (re_append->file_name == NULL)
		return (error_handler_null(main_env, -10, "re_app_", "function"));
	(*list_words) = (*list_words)->next;
	return ((void *)re_append);
}

// void	*env_function(t_main_env **main_env, char *str)
// {
// 	t_env_var	*env_var;
// 	t_our_env	*our_env;
// 	char *temp;
// 	our_env = (*main_env)->our_env;
// 	env_var = (t_env_var *)malloc(sizeof(t_env_var));
// 	if (!env_var)
// 		return (NULL);
// 	env_var->var_name = ft_substr(str, 1, ft_strlen(str) - 1);
// 	if (!env_var->var_name)
// 		return (NULL);
// 	env_var->value = ft_strdup("");
// 	if (!env_var->value)
// 		return (NULL);
// 	while (our_env->next != NULL && our_env->next->var_name != NULL)
// 	{
// 		if (ft_strncmp(str + 1, our_env->var_name, ft_strlen(str) - 1) == 0)
// 		{
// 			temp = ft_strjoin(env_var->value, our_env->value);
// 			free(env_var->value);
// 			if (temp == NULL)
// 				return (error_handler_null(main_env, -10, "env_", "function"));
// 			if (temp != NULL)
// 				env_var->value = temp;
// 		}
// 		our_env = our_env->next;
// 	}
// 	env_var->fl = 0;
// 	return ((void *)env_var);
// }
