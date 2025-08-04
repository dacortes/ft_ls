/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:11:32 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/04 10:22:48 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/******************************************************************************/
/*                            STRUCTURES                                      */
/******************************************************************************/

#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "libft.h"
#include "errors.h"
#include "global.h"
#include "ft_printf.h"

typedef struct s_node			t_node;
typedef struct s_stack			t_stack;

struct s_node
{
	struct dirent	*entry;
	t_node			*next;
	t_node			*prev;
};

struct s_stack
{
	int		size;
	int		status;
	int		count;
	t_node	*top;
	t_node	*bot;
};

/*	clear.c	*/
short	clear_stack(t_stack *stack);
/*	handler_data.c	*/
void	copy_struct_dirent(struct dirent *origin, struct dirent **copy);
short	init_struct_dirent(t_node **node, DIR *dir, char *file);
short	default_directories(char *name_file, unsigned char type);
// int		is_directory(t_node **node, char *path);
/*	handler_nodes.c	*/
short	pop_stack(t_stack *stack);
short	push_stack(t_stack *stack, t_node *new);
t_node	*copy_node(t_stack *stack, short do_free);
