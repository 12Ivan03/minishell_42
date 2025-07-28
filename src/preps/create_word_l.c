/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_word_l.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:26:43 by ipavlov           #+#    #+#             */
/*   Updated: 2025/06/03 15:42:06 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_list_words	*create_note_word(char *str, int space_before)
{
	t_list_words	*words_list;

	words_list = (t_list_words *)malloc(sizeof(t_list_words));
	if (words_list == NULL)
		return (NULL);
	words_list->word = str;
	words_list->space_before = space_before;
	words_list->next = NULL;
	words_list->prev = NULL;
	return (words_list);
}

int	link_t_word(t_list_words **list_words, char *word, int space_before)
{
	t_list_words	*note;
	t_list_words	*last_note;

	note = create_note_word(word, space_before);
	if (note == NULL)
		return (1);
	if (*list_words == NULL)
	{
		*list_words = note;
		return (0);
	}
	last_note = *list_words;
	while (last_note->next != NULL)
		last_note = last_note->next;
	last_note->next = note;
	note->prev = last_note;
	return (0);
}
