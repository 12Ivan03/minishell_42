/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:16:25 by aerokhin          #+#    #+#             */
/*   Updated: 2025/05/23 18:25:46 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef enum e_tokens
{
	WORD,
	STRING,
	COMMAND,
	PROGRAM,
	REDIRECTION_INPUT,
	REDIRECTION_OUTPUT,
	REDIRECTION_HERE_DOC,
	REDIRECTION_APPEND,
	PIPE,
	ENV_VARIABLE,
	OPTIONS
}	t_tokens;

#endif
