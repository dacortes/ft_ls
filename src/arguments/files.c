/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:02:55 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/07 09:35:30 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"
#include "errors.h"
#include "arguments.h"
#include "print_values.h"

/**
 * get_size_files - Calculates the number of non-flag arguments in a list.
 * @args: A null-terminated array of strings representing the arguments.
 *
 * This function iterates through the provided array of arguments and counts
 * the number of elements that are not flags. Flags are determined by the
 * `is_flag` function, which returns `false` for non-flag arguments.
 *
 * Return: The count of non-flag arguments in the array.
 *         Returns -1 if the input array is NULL.
 */
int	get_size_files(char **args)
{
	int	iter;
	int	sizes;

	if (!args)
		return (-1);
	iter = 0;
	sizes = 0;
	while (args[iter])
	{
		if (is_flag(args[iter]) == false)
			sizes++;
		iter++;
	}
	return (sizes);
}

static short	add_array_files(char **src, struct dirent **dst)
{
	int	iter;
	int	add;

	if (!src || !dst)
		return (EXIT_FAILURE);
	add = 0;
	iter = 0;
	while (src[iter])
	{
		if (is_flag(src[iter]) == false)
		{
			dst[add] = protected_memory(ft_calloc(sizeof(struct dirent), 1), \
				"add_array_files");
			ft_strcpy(dst[add]->d_name, src[iter]);
			add++;
		}
		iter++;
	}
	return (EXIT_SUCCESS);
}

char	*create_full_path(const char *curr_root_dir, const char *curr_dir)
{
	char	*full_path;
	char	*tmp;
	int		len;

	if (!curr_root_dir || !*curr_root_dir)
		return (NULL);
	len = ft_strlen(curr_root_dir);
	if (curr_root_dir[len] != '/')
		tmp = protected_memory(ft_addend_char(curr_root_dir, '/'), \
			"create_full_path");
	else
		tmp = protected_memory(ft_strdup(curr_root_dir),  "create_full_path");
	full_path = protected_memory(ft_strjoin(tmp, curr_dir), "create_full_path");
	if (tmp)
		free(tmp);
	return (full_path);
}

void	loop_recursive_flag(t_flags flags, struct dirent **files, int sizes)
{
	int	iter;

	(void)sizes;
	iter = 0;
	while(files[iter])
	{
		exec_recursive_flag(flags, files[iter]->d_name);
		++iter;
	}
}

int	get_regular_files_number(struct dirent **files, int sizes)
{
	struct stat	st;
	int			count;
	int			iter;

	iter = 0;
	count = 0;
	while (iter < sizes)
	{
		if (lstat(files[iter]->d_name, &st) == -1)
		{
			error_msg(OPEN_DIR, 2, files[iter]->d_name, strerror(errno));
			++iter;
			continue;
		}
		if (!S_ISDIR(st.st_mode))
			++count;
		++iter;
	}
	return (count);
}

void	get_regular(t_flags flags, struct dirent **fls, int sizes, t_line **ln)
{
	struct stat	st;
	int			iter;
	int			add;

	iter = 0;
	add = 0;
	while (iter < sizes)
	{
		if (lstat(fls[iter]->d_name, &st) == -1)
			continue;
		if (!S_ISDIR(st.st_mode))
		{
			get_format(flags, fls[iter]->d_name, fls[iter]->d_name, \
				&(*ln)[add]);
			++add;
		}
		++iter;
	}
}

void	print_regular_files(t_flags flags, struct dirent **files, int sizes)
{
	t_line	*lines;
	int		file_count;

	if (flags.args == false)
		return ;
	file_count = get_regular_files_number(files, sizes);
	if (!file_count)
		return ;
	lines = protected_memory(ft_calloc(file_count + 1, sizeof(t_line)), \
	"print_regular_files");
	get_regular(flags, files, sizes, &lines);
	handle_line(flags, &lines, file_count);
	ft_printf("\n");
}

struct dirent	**is_file(t_flags flags, char **args, int sizes)
{
	struct dirent	**entries;

	if (!sizes || sizes < 0)
		return (NULL);
	entries = protected_memory(ft_calloc(sizes + 1, sizeof(struct dirent *)) \
		, "is_file");
	if (add_array_files(args, entries) == EXIT_FAILURE)
		return (NULL);
	sort_entries(entries, sizes, flags);
	print_regular_files(flags, entries, sizes);
	loop_recursive_flag(flags, entries, sizes);
	return (entries);
}
