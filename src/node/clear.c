/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:17:10 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/21 09:44:56 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

short	clear_stack(t_stack *stack)
{
	if (!stack || !stack->size || !stack->top)
		return (EXIT_FAILURE);
	while (stack->size)
		pop_stack(stack);
	return (EXIT_SUCCESS);
}
