/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:59:45 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/04 13:44:28 by dacortes         ###   ########.fr       */
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
		return (fd_printf(2, WARNING_POINTER, YELLOW, END, \
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

int	depth_loop(t_flags flags, t_stack *stack, struct dirent **files, \
	t_node *curr)
{
	char	*full_path;
	t_line	*ln;
	int		i;

	i = -1;
	full_path = NULL;
	ln = protected_memory(ft_calloc(sizeof(t_line), stack->count + 1), "dp_");
	while ((++i) < stack->count)
	{
		if (ignore_current_dir(flags, files, &i))
			continue ;
		if (default_directories(files[i]->d_name, files[i]->d_type))
		{
			has_flag_all(flags, curr->entry->d_name, files[i]->d_name, &ln[i]);
			++i;
			continue ;
		}
		full_path = create_full_path(curr->entry->d_name, files[i]->d_name);
		get_format(flags, full_path, files[i]->d_name, &ln[i]);
		if (flags.recursive == true)
			add_node_to_stack(stack, files, full_path, i);
		if (full_path)
			free(full_path);
	}
	return (handle_line(flags, &ln, stack->count), EXIT_SUCCESS);
}

short	loop_recursive(t_flags flags, t_stack *stack)
{
	struct dirent	**entries;
	t_node			*curr;
	DIR				*dir;
	struct stat		st;

	stack->count = 0;
	entries = NULL;
	while (stack->size > 0)
	{
		curr = copy_node(stack, true);
		if (select_state(flags, &curr, &st, &dir))
			continue ;
		stack->count = read_dir_entries(dir, &entries);
		sort_entries(entries, stack->count, flags);
		depth_loop(flags, stack, entries, curr);
		clear_entries(entries, stack->count, true);
		closedir(dir);
		free(curr->entry);
		free(curr);
		if (stack->size != 0)
			ft_printf("\n");
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
