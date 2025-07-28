/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_env_expanders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:39:03 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/26 16:13:52 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	expand_var_value(t_main_env **main_env, t_env_var *env_var, char *temp)
{
	env_var->var_name = ft_strjoin(temp, "=");
	free(temp);
	if (!env_var->var_name)
		return (1);
	env_var->value = get_env_value(main_env, env_var->var_name);
	env_var->fl = 0;
	if (!env_var->value)
		env_var->fl = -1;
	return (0);
}

int	expand_question_sign(t_main_env **main_env, char *str, \
						size_t *var_len, t_env_var *env_var)
{
	*var_len = 2;
	(void)str;
	env_var->var_name = ft_strdup("$?");
	if (!(env_var->var_name))
		return (1);
	env_var->value = ft_itoa((*main_env)->exit_status);
	if (!(env_var->value))
	{
		free(env_var->var_name);
		return (1);
	}
	env_var->rest = NULL;
	env_var->fl = 0;
	return (0);
}

char	*expand_env_var(t_main_env **main_env, char *str, size_t *i, int flag)
{
	t_env_var	*env_var;
	size_t		var_len;
	char		*temp;

	var_len = 0;
	env_var = get_var_info_substr(main_env, str, *i, &var_len);
	if (env_var)
	{
		if (env_var->value)
			temp = ft_strdup(env_var->value);
		else
			temp = ft_strdup("");
		*i = *i + var_len - 1;
		free_env_var(env_var);
	}
	else
		temp = ft_strdup("$");
	(*i) += (*i < ft_strlen(str));
	return (temp);
}

char	*expand_text(t_main_env **main_env, char *str, size_t *i, int flag)
{
	char	*temp;

	if (str[(*i)] == '\'' && (flag == 0 || flag == -1))
		temp = handle_single_quotes(main_env, str, i, flag);
	else if (str[(*i)] == '"' && (flag == 0 || flag == -1))
		temp = handle_double_quotes(main_env, str, i, flag);
	else if (str[(*i)] == '$' && flag != -1)
		temp = expand_env_var(main_env, str, i, flag);
	else
		temp = copy_substr(str, i, 0);
	return (temp);
}

char	*copy_substr(char *str, size_t *i, size_t step)
{
	char	*result;
	size_t	start;

	start = (*i);
	(*i) += step;
	skip_till_specchars(str, i);
	result = ft_substr(str, start, (*i) - start);
	return (result);
}
