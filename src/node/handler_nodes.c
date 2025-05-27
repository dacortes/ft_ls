/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:15:44 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/27 09:55:58 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

short	pop_stack(t_stack *stack)
{
	t_node	*temp;

	if (!stack || !stack->top)
		return (EXIT_FAILURE);
	temp = stack->top;
	stack->top = temp->next;
	if (!stack->top)
		stack->bot = NULL;
	else
	{
		stack->top->prev = NULL;
		stack->bot = stack->top;
		while (stack->bot->next)
			stack->bot = stack->bot->next;
	}
	if (temp->entry)
		free(temp->entry);
	free(temp);
	stack->size--;
	return (EXIT_SUCCESS);
}

short	push_stack(t_stack *stack, t_node *new)
{
	if (!new)
		return (EXIT_FAILURE);
	if (stack->size == 0)
	{
		stack->top = new;
		stack->bot = new;
		stack->bot->prev = NULL;
	}
	else
	{
		new->next = stack->top;
		stack->top->prev = new;
		stack->top = new;
	}
	stack->size++;
	return (EXIT_SUCCESS);
}

t_node	*copy_node(t_stack *stack, short do_free)
{
	t_node	*copy;

	if (!stack || !stack->top)
		return (ft_printf(WARNING_POINTER, YELLOW, END, \
			"copy_node", "stack"), NULL);
	copy = protected_memory(ft_calloc(1, sizeof(t_node)), "copy_node");
	copy_struct_dirent(stack->top->entry, &copy->entry);
	if (do_free == true)
		pop_stack(stack);
	return (copy);
}
