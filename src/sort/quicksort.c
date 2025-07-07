/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:53:07 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/07 11:27:41 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/**
 * swap_ptr - Swaps the values of two pointers.
 * @a: A pointer to the first pointer to be swapped.
 * @b: A pointer to the second pointer to be swapped.
 *
 * This function exchanges the values of the two pointers
 * passed as arguments. It is useful for swapping pointers
 * in sorting algorithms or other pointer manipulation tasks.
 */
void	swap_ptr(void **a, void **b)
{
	void	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	compare_by_name(const void *a, const void *b)
{
	struct dirent	*entry1;
	struct dirent	*entry2;

	entry1 = (struct dirent *)a;
	entry2 = (struct dirent *)b;
	return (ft_strncmp(entry1->d_name, entry2->d_name, -1));
}

// #include <time.h>

int	compare_by_time(const void *a, const void *b)
{
	struct dirent	*entry1;
	struct dirent	*entry2;
	struct stat		stat1;
	struct stat		stat2;

	entry1 = (struct dirent *)a;
	entry2 = (struct dirent *)b;
	if (stat(entry1->d_name, &stat1) == ERROR)
		return (0);
	if (stat(entry2->d_name, &stat2) == ERROR)
		return (0);
	if (S_ISREG(stat1.st_mode) && !S_ISREG(stat2.st_mode))
		return (-1);
	if (!S_ISREG(stat1.st_mode) && S_ISREG(stat2.st_mode))
		return (1);
	if (stat1.st_ctime > stat2.st_ctime)
		return (-1);
	else if (stat1.st_ctime < stat2.st_ctime)
		return (1);
	return (dirs_same_time(stat1, stat2, entry1->d_name, entry2->d_name));
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
		if (flags.reverse == false)
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
