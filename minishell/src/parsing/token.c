/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:21:07 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/03 21:24:51 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_data_ms *data, t_token *tokens, char *value,
t_token_type type)
{
	t_token	*token;
	t_token	*last_token;

	if (value && value[ft_strlen(value) - 1] == ' ')
		value[ft_strlen(value) - 1] = '\0';
	token = (t_token *)gc_malloc(data->mem_ps, sizeof(t_token));
	token->value = value;
	token->type = type;
	token->next = NULL;
	if (tokens == NULL)
		return (token);
	else
	{
		last_token = tokens;
		while (last_token->next != NULL)
			last_token = last_token->next;
		last_token->next = token;
		return (tokens);
	}
}

void	free_tokens(t_data_ms *data, t_token *tokens)
{
	t_token	*current_token;
	t_token	*next_token;

	current_token = tokens;
	while (current_token)
	{
		next_token = current_token->next;
		if (current_token->value)
			gc_free(data->mem_ps, current_token->value);
		gc_free(data->mem_ps, current_token);
		current_token = next_token;
	}
}
