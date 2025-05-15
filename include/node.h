/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:11:32 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/15 12:07:37 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/******************************************************************************/
/*                            STRUCTURES                                      */
/******************************************************************************/

#include <stdlib.h>
#include <dirent.h>

typedef struct s_node			t_node;
typedef struct s_stack			t_stack;

struct s_node
{
	int		data;
	t_node	*next;
	t_node	*prev;
};

struct s_stack
{
	int		size;
	t_node	*top;
	t_node	*bot;
};

short	pop_stack(t_stack *stack);
short	push_stack(t_stack *stack, t_node *new);