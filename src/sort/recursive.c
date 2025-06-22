/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:59:45 by dacortes          #+#    #+#             */
/*   Updated: 2025/06/22 12:38:29 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"
#include "clear.h"
#include "errors.h"
#include "print_values.h"

int	add_node_to_stack(t_stack *stack, struct dirent **files, char *path, int i)
{
	t_node	*add;

	if (!files || !*files)
		return  (fd_printf(2, WARNING_POINTER, YELLOW, END, \
		"add_node_to_stack", "files"), EXIT_FAILURE);
	add = NULL;
	if (files[i]->d_type == DT_DIR)
	{
		add = ft_calloc(1, sizeof(t_node));
		if (!add)
			exit(error_msg(MALLOC, 1, "loop_recursive", ""));
		add->entry = protected_memory(ft_calloc(1, sizeof(struct dirent) \
		+ ft_strlen(path) + 1), "add_node_to_stack");
		ft_strcpy(add->entry->d_name, path);
		push_stack(stack, add);
	}
	return (EXIT_SUCCESS);
}

int	depth_loop(t_flags flags, t_stack *stack, struct dirent **files, int count, t_node *curr)
{
	char	*full_path;
	int		i;

	i = 0;
	full_path = NULL;
	while (i < count)
	{
		if (default_directories(files[i]->d_name, files[i]->d_type))
		{
			++i;
			continue ;
		}
		full_path = create_full_path(curr->entry->d_name, files[i]->d_name);
		add_node_to_stack(stack, files, full_path, i);
		ft_printf("---> %s\n", files[i]->d_name);
		flags.long_format = true;
		get_long_format(flags, full_path);
		if (full_path)
			free(full_path);
		++i;
	}
	return (EXIT_SUCCESS);
}

short	loop_recursive(t_flags flags, t_stack *stack)
{
	struct dirent	**entries;
	t_node			*curr;
	DIR				*dir;
	int				entry_count;

	entry_count = 0;
	entries = NULL;
	while (stack->size > 0)
	{
		curr = copy_node(stack, true);
		ft_printf("Exploring: %s\n", curr->entry->d_name);
		dir = init_dir(curr->entry->d_name);
		if (!dir)
			continue ;
		entry_count = read_dir_entries(dir, &entries);
		sort_entries(entries, entry_count, flags);
		depth_loop(flags, stack, entries, entry_count, curr);
		clear_entries(entries, entry_count, true);
		closedir(dir);
		free(curr->entry);
		free(curr);
	}
	if (entries)
		free(entries);
	return (true);
}

short	exec_recursive_flag(t_flags flags, char *start_dir)
{
	t_stack	stack;
	t_node	*root;

	if (!start_dir)
		return (false);
	ft_bzero(&stack, sizeof(t_stack));
	root = ft_calloc(1, sizeof(t_node));
	if (!root)
		exit(error_msg(MALLOC, 1, "exec_recursive_flag", ""));
	root->entry = ft_calloc(1, sizeof(struct dirent) \
		+ ft_strlen(start_dir) + 1);
	if (!root)
		exit(error_msg(MALLOC, 1, "exec_recursive_flag", ""));
	ft_strcpy(root->entry->d_name, start_dir);
	push_stack(&stack, root);
	loop_recursive(flags, &stack);
	clear_stack(&stack);
	return (stack.status);
}
