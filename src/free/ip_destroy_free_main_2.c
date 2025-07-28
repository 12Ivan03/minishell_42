/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ip_destroy_free_main_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:58:05 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/16 14:57:05 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_re_in(t_re_input **input)
{
	if (!input || !*input)
		return ;
	ft_free((void **)&(*input)->file_name);
	ft_free((void **)input);
}

void	free_re_out(t_re_output **output)
{
	if (!output || !*output)
		return ;
	ft_free((void **)&(*output)->file_name);
	ft_free((void **)output);
}

void	free_re_app(t_re_append **append)
{
	if (!append || !*append)
		return ;
	ft_free((void **)&(*append)->file_name);
	ft_free((void **)append);
}

void	free_re_here(t_re_here **here)
{
	if (!here || !*here)
		return ;
	ft_free((void **)&(*here)->stop_word);
	ft_free((void **)&(*here)->file_name);
	ft_free((void **)here);
}
