/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_print_helper_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:41:29 by aerokhin          #+#    #+#             */
/*   Updated: 2025/05/31 16:15:07 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_our_env(t_our_env **our_env)
{
	t_our_env		*our_env_2;

	our_env_2 = *our_env;
	printf("\n~~our_env~~\n\n");
	while (our_env_2 != NULL)
	{
		printf("(var_name:value) %s%s \n", our_env_2->var_name, \
				our_env_2->value);
		our_env_2 = our_env_2->next;
	}
}
