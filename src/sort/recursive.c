/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:59:45 by dacortes          #+#    #+#             */
/*   Updated: 2025/06/30 17:29:25 by dacortes         ###   ########.fr       */
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



void	has_flag_all(t_flags flags, char *curr_root_dir, char *curr_dir, t_line *add)
{
	char	*full_path;

	if (flags.all == true)
		return ;
	full_path = create_full_path(curr_root_dir, curr_dir);
	get_long_format(flags, full_path, curr_dir, add);
	if (full_path)
	{
		free(full_path);
		full_path = NULL;
	}
}

void	update_max_lengths(t_line *line, t_size *size)
{
	size_t	len;

	len = ft_strlen(line->num_links);
	if (len > size->max_links)
		size->max_links = len;
	len = ft_strlen(line->owner);
	if (len > size->max_owner)
		size->max_owner = len;
	len = ft_strlen(line->group);
	if (len > size->max_group)
		size->max_group = len;
	len = ft_strlen(line->bytes);
	if (len > size->max_bytes)
		size->max_bytes = len;
	len = ft_strlen(line->date);
	if (len > size->max_date)
		size->max_date = len;
	len = ft_strlen(line->name);
	if (len > size->max_name)
		size->max_name = len;
	size->max_line = size->max_links + size->max_owner + \
	size->max_group + size->max_bytes + size->max_date + size->max_name + 10;
}

short	clear_line(t_line *line)
{
	if (!line)
		return (false);
	free(line->permissions);
	free(line->num_links);
	free(line->owner);
	free(line->group);
	free(line->bytes);
	free(line->date);
	free(line->name);
	free(line->line);
	return (true);
}

void	fill_spaces_right(char *dest, char *str, size_t width)
{
	size_t	len = ft_strlen(str);
	size_t	i = 0;

	ft_strcpy(dest, str);
	i = len;
	while (i < width)
		dest[i++] = ' ';
	dest[i] = '\0';
}

void	fill_spaces_left(char *dest, char *str, size_t width)
{
	size_t	len = ft_strlen(str);
	size_t	padding;

	if (width > len)
		padding = width - len;
	else
		padding = 0;
	ft_memset(dest, ' ', padding);
	ft_strcpy(dest + padding, str);
}

void	add_permissions(char **cursor, char *permissions)
{
	ft_strcpy(*cursor, permissions);
	*cursor += ft_strlen(permissions);
	*(*cursor)++ = ' ';
}

void	add_links(char **cursor, char *num_links, size_t offset)
{
	fill_spaces_left(*cursor, num_links, offset);
	*cursor += offset;
	*(*cursor)++ = ' ';
}

void	add_owner(char **cursor, char *owner, size_t offset)
{
	fill_spaces_right(*cursor, owner, offset);
	*cursor += offset;
	*(*cursor)++ = ' ';
}

void	add_group(char **cursor, char *group, size_t offset)
{
	fill_spaces_right(*cursor, group, offset);
	*cursor += offset;
	*(*cursor)++ = ' ';
}

void	add_bytes(char **cursor, char *bytes, size_t offset)
{
	fill_spaces_left(*cursor, bytes, offset);
	*cursor += offset;
	*(*cursor)++ = ' ';
}

void	add_date(char **cursor, char *date)
{
	ft_strcpy(*cursor, date);
	*cursor += ft_strlen(date);
	*(*cursor)++ = ' ';
}

void	create_line(t_line *line, t_size size)
{
	size_t	offset;
	char	*cursor;

	if (!line || !size.max_line)
		return ;
	line->line = protected_memory(ft_calloc(size.max_line + 9, sizeof(char)), \
		"create_line");
	cursor = line->line;
	add_permissions(&cursor, line->permissions);
	offset = size.max_links;
	add_links(&cursor, line->num_links, offset);
	offset = size.max_owner;
	add_owner(&cursor, line->owner, offset);
	offset = size.max_group;
	add_group(&cursor, line->group, offset);
	offset = size.max_bytes;
	add_bytes(&cursor, line->bytes, offset);
	add_date(&cursor, line->date);
	ft_strcpy(cursor, line->name);
	print_line(line->line, size.max_line + 8);
}


void	foo(t_flags flags, t_line **line, int limit)
{
	t_size	size;
	int		iter;

	if (flags.long_format == false)
		return ;
	iter = 0;
	ft_bzero(&size, sizeof(size));
	while (iter < limit)
	{
		update_max_lengths(&(*line)[iter], &size);
		iter++;
	}
	iter = 0;
	while (iter < limit)
	{
		create_line(&(*line)[iter], size);
		if (clear_line(&(*line)[iter]) == false)
			exit(error_msg(MALLOC, 1, "foo", ""));
		iter++;
	}
}

int	depth_loop(t_flags flags, t_stack *stack, struct dirent **files, int count, t_node *curr)
{
	char			*full_path;
	t_line			*line;
	int				i;

	i = 0;
	full_path = NULL;
	line = protected_memory(ft_calloc(sizeof(t_line), count + 1), "depth_loop");
	while (i < count)
	{
		flags.long_format = true;// quitar esta linea	
		if (default_directories(files[i]->d_name, files[i]->d_type))
		{
			has_flag_all(flags, curr->entry->d_name, files[i]->d_name, &line[i]);
			++i;
			continue ;
		}
		full_path = create_full_path(curr->entry->d_name, files[i]->d_name);
		get_long_format(flags, full_path, files[i]->d_name, &line[i]);
		add_node_to_stack(stack, files, full_path, i);
		if (full_path)
			free(full_path);
		++i;
	}
	foo(flags, &line, count);
	free(line);
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
