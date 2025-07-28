/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_env_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:37:44 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/26 16:17:01 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env_var	*init_env_var(void)
{
	t_env_var	*env_var;

	env_var = malloc(sizeof(t_env_var));
	if (!env_var)
		return (NULL);
	env_var->var_name = NULL;
	env_var->value = NULL;
	env_var->rest = NULL;
	env_var->fl = 0;
	return (env_var);
}

void	free_env_var(t_env_var *env_var)
{
	if (env_var)
	{
		if (env_var->var_name)
		{
			free(env_var->var_name);
			env_var->var_name = NULL;
		}
		if (env_var->value)
		{
			free(env_var->value);
			env_var->value = NULL;
		}
		if (env_var->rest)
		{
			free(env_var->rest);
			env_var->rest = NULL;
		}
		free(env_var);
	}
}

t_env_var	*get_var_info_substr(t_main_env **main_env, char *str, \
								size_t i, size_t *var_len)
{
	t_env_var	*env_var;
	char		*tmp;

	env_var = init_env_var();
	if (!(env_var))
		return (NULL);
	if (!str[i++])
		return (free(env_var), NULL);
	if (str[i] == '{')
	{
		if (handle_curly_var(str, i, var_len, &tmp))
			return (free(env_var), NULL);
	}
	else if (str[i] == '?')
	{
		if (expand_question_sign(main_env, str, var_len, env_var))
			return (free(env_var), NULL);
		return (env_var);
	}
	else if (handle_var_name(str, i, var_len, &tmp))
		return (free(env_var), NULL);
	if (expand_var_value(main_env, env_var, tmp))
		return (free(env_var), NULL);
	return (env_var);
}

char	*replace_vars(t_main_env **main_env, char *src, int flag, int chng_tld)
{
	char		*result;
	char		*temp;
	size_t		i;
	char		*input;

	(void)chng_tld;
	if (!src)
		return (NULL);
	input = src;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (input[i] != '\0' && i < ft_strlen(input))
	{
		temp = expand_text(main_env, input, &i, flag);
		if (!temp)
			return (free(result), NULL);
		result = join_and_free(&result, &temp);
		if (!result)
			return (NULL);
	}
	return (result);
}
