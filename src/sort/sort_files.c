/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:53:19 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/24 13:15:16 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

int	compare_by_name(const void *a, const void *b)
{
	struct dirent	*entry1;
	struct dirent	*entry2;

	entry1 = (struct dirent *)a;
	entry2 = (struct dirent *)b;
	return (ft_strncmp(entry1->d_name, entry2->d_name, -1));
}

int	compare_by_time(const void *a, const void *b)
{
	struct dirent	*entry1;
	struct dirent	*entry2;
	struct stat		stat1;
	struct stat		stat2;

	entry1 = (struct dirent *)a;
	entry2 = (struct dirent *)b;
	if (stat(entry1->d_name, &stat1) == ERROR ||
		stat(entry2->d_name, &stat2) == ERROR)
		return (0);
	if (stat1.st_mtime > stat2.st_mtime)
		return (-1);
	else if (stat1.st_mtime < stat2.st_mtime)
		return (1);
	return (0);
}

int	partition_entries(struct dirent **arr, int low, int high, t_flags flags)
{
	struct dirent	*pivot;
	int				cmp;
	int				i;
	int				j;

	i = low -1;
	j = low;
	pivot = arr[high];
	while (j < high)
	{
		if (flags.time)
			cmp = compare_by_time((void *)arr[j], (void *)pivot);
		else
			cmp = compare_by_name((void *)arr[j], (void *)pivot);
		if (flags.reverse)
			cmp = -cmp;
		if (cmp < 0)
		{
			i++;
			swap_ptr((void **)&arr[i], (void **)&arr[j]);
		}
		j++;
	}
	swap_ptr((void **)&arr[i + 1], (void **)&arr[high]);
	return (i + 1);
}

void	quicksort_entries(struct dirent **src, int low, int high, t_flags flags)
{
	int	pivot_index;

	if (low < high)
	{
		pivot_index = partition_entries(src, low, high, flags);
		quicksort_entries(src, low, pivot_index - 1, flags);
		quicksort_entries(src, pivot_index + 1, high, flags);
	}
}

void	sort_entries(struct dirent **entries, int count, t_flags flags)
{
	if (!entries || count <= 1)
		return ;
	quicksort_entries(entries, 0, count - 1, flags);
}

void	sort_files(char **files, int size)
{
	if (!files || size <= 0 || size == 1)
		return ;
	quicksort(files, 0, size - 1);
}
