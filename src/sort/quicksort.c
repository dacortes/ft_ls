/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:53:07 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/23 15:53:36 by dacortes         ###   ########.fr       */
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

/**
 * partition - Partitions an array of strings for quicksort.
 *
 * This function rearranges the elements of the array such that all elements
 * less than the pivot are placed before it, and all elements greater than
 * the pivot are placed after it. The pivot is chosen as the last element
 * in the array.
 *
 * @param arr: The array of strings to be partitioned.
 * @param low: The starting index of the portion of the array to partition.
 * @param high: The ending index of the portion of the array to partition.
 *
 * @return The index of the pivot element after partitioning.
 *
 * Note:
 * - The function uses `ft_strncmp` to compare strings.
 * - The `swap_ptr` function is used to swap elements in the array.
 * - The comparison assumes that `ft_strncmp` can handle a negative value
 *   for the length parameter to compare entire strings.
 */
int	partition(char **arr, int low, int high)
{
	char	*pivot;
	int		i;
	int		j;

	i = low - 1;
	j = low;
	pivot = arr[high];
	while (j < high)
	{
		if (ft_strncmp(arr[j], pivot, -1) < 0)
		{
			i++;
			swap_ptr((void **)&arr[i], (void **)&arr[j]);
		}
		j++;
	}
	swap_ptr((void **)&arr[i + 1], (void **)&arr[high]);
	return (i + 1);
}

/**
 * quicksort - Sorts an array of strings using the Quick Sort algorithm.
 * 
 * @arr: The array of strings to be sorted.
 * @low: The starting index of the portion of the array to be sorted.
 * @high: The ending index of the portion of the array to be sorted.
 * 
 * This function recursively sorts the array by partitioning it into two
 * subarrays around a pivot element. Elements less than the pivot are moved
 * to the left subarray, and elements greater than the pivot are moved to
 * the right subarray. The process is repeated for each subarray until the
 * entire array is sorted.
 */
void	quicksort(char **arr, int low, int high)
{
	int	index;

	if (low < high)
	{
		index = partition(arr, low, high);
		quicksort(arr, low, index - 1);
		quicksort(arr, index + 1, high);
	}
}
