/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:12:18 by dacortes          #+#    #+#             */
/*   Updated: 2025/08/04 10:18:02 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear.h"
#include "errors.h"
#include "arguments.h"
#include "print_values.h"
#include "sort.h"
#include <pwd.h>
#include <string.h>
#include <sys/stat.h>

void print_entries(struct dirent **entries, int size)
{
	int iter;

	if (!size || !entries || !*entries)
	{
		fd_printf(2, WARNING_POINTER, YELLOW, END,
				  "print_entries", "files");
		return;
	}
	iter = 0;
	while (iter < size)
	{
		ft_printf("%sfiles%s[%d] %s\n", BLUE, END, iter, entries[iter]->d_name);
		iter++;
	}
}

struct dirent **curr_directory(t_flags flags, char *name, int *entry_count)
{
	struct dirent **entries;
	DIR *dir;

	dir = init_dir(name);
	if (!dir)
		return (NULL);
	entries = NULL;
	*entry_count = read_dir_entries(dir, &entries);
	sort_entries(entries, *entry_count, flags);
	exec_recursive_flag(flags, entries[0]->d_name);
	closedir(dir);
	return (entries);
}

int main(int ac, char **av)
{
	struct dirent **files;
	t_flags flags;
	int size_files;

	files = NULL;
	size_files = get_size_files(&av[1]);
	if (has_flags(&flags, ac, &av[1]) == false && !size_files)
		files = curr_directory(flags, "./", &size_files);
	else
	{
		if (size_files)
			files = is_file(flags, &av[1], size_files);
		else if (!size_files)
			files = curr_directory(flags, "./", &size_files);
	}
	if (!files)
		return (EXIT_SUCCESS);
	clear_entries(files, size_files, false);
	return (EXIT_SUCCESS);
}
