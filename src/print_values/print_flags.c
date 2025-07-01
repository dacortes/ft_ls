/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:13:24 by dacortes          #+#    #+#             */
/*   Updated: 2025/07/01 12:29:18 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_values.h"

/**
 * bool_to_text - Converts a boolean value to a color-coded string
 * representation.
 * 
 * @bool: An unsigned integer representing the boolean value.
 *        Expected values are 0 (false) or 1 (true).
 * 
 * Return: A pointer to a string containing the text "false" in red color
 *         if the input is 0, or "true" in blue color if the input is 1.
 *         The string includes ANSI escape codes for color formatting.
 * 
 * Note: The function assumes the terminal supports ANSI escape codes.
 */
char	*bool_to_text(unsigned int bool)
{
	if (bool == false)
		return ("\033[1;31mfalse\033[m");
	return ("\033[1;34mtrue\033[m");
}

/**
 * @brief Prints the values of the flags in a formatted manner.
 *
 * This function outputs the current state of the flags stored in the 
 * `t_flags` structure. Each flag is displayed with its corresponding 
 * boolean value converted to a textual representation using the 
 * `bool_to_text` function.
 *
 * @param flag A pointer to a `t_flags` structure containing the flags to print.
 *
 * The flags printed are:
 * - `l`: Long format
 * - `R`: Recursive
 * - `a`: All
 * - `r`: Reverse
 * - `t`: Time
 *
 * The output is color-coded with the flag header in orange and
 * the rest in default color.
 */
void	printf_value_flag(t_flags *flag)
{
	ft_printf("%sFLAGS\n%s", ORANGE, END);
	ft_printf("\tl = %s\n", bool_to_text(flag->long_format));
	ft_printf("\tR = %s\n", bool_to_text(flag->recursive));
	ft_printf("\ta = %s\n", bool_to_text(flag->all));
	ft_printf("\tr = %s\n", bool_to_text(flag->reverse));
	ft_printf("\tt = %s\n", bool_to_text(flag->time));
}

/**
 * @file print_flags.c
 * @brief Contains the implementation of functions for printing file arrays.
 *
 * @function print_array_files
 * @brief Prints the contents of an array of file names to the standard output.
 *
 * This function iterates through an array of file names and prints each file's
 * index and name. It also includes debug messages to indicate the function's
 * execution and warnings if the input is invalid.
 *
 * @param files A null-terminated array of strings representing file names.
 *              If the pointer is null or the array is empty,
 * 				a warning is printed.
 *
 * @return A short integer indicating success or failure:
 *         - `true` (non-zero): If the array is successfully processed.
 *         - `false` (zero): If the input pointer is null or invalid.
 *
 * @note The function uses color-coded output for better readability:
 *       - `BLUE` and `END` are used for formatting the debug and file
 * 			information.
 *       - `YELLOW` and `END` are used for formatting warning messages.
 *
 * @dependencies
 * - Requires the `ft_printf` function for formatted output.
 * - Assumes the presence of color macros (`BLUE`, `YELLOW`, `END`) for styling.
 */
short	print_array_files(char **files)
{
	int	iter;

	ft_printf("%sFunc print_array_files\n%s", BLUE, END);
	if (!files || !*files)
		return (fd_printf(2, WARNING_POINTER, YELLOW, END, \
		"print_array_files", "files"), false);
	iter = 0;
	while (files[++iter])
		ft_printf("%sindex%s [%d] -- %sname%s: *%s*\n", BLUE, END, iter \
			, BLUE, END, files[iter]);
	return (true);
}

/**
 * get_type_dir - Returns a string representation of a file type.
 * @type: The file type identifier (e.g., DT_DIR, DT_REG, etc.).
 *
 * This function takes a file type identifier as input and returns a
 * human-readable string describing the type of the file. The possible
 * file types and their corresponding strings are:
 * 
 * - DT_DIR: "directory"
 * - DT_REG: "regular file"
 * - DT_LNK: "symbolic link"
 * - DT_FIFO: "FIFO/pipe"
 * - DT_SOCK: "socket"
 * - DT_CHR: "character device"
 * - DT_BLK: "block device"
 * 
 * If the file type is not recognized, the function returns "unknown type".
 *
 * Return: A pointer to a string describing the file type.
 */
char	*get_type_dir(int type)
{
	if (type == DT_DIR)
		return ("directory");
	else if (type == DT_REG)
		return ("regular file");
	else if (type == DT_LNK)
		return ("symbolic link");
	else if (type == DT_FIFO)
		return ("FIFO/pipe");
	else if (type == DT_SOCK)
		return ("socket");
	else if (type == DT_CHR)
		return ("character device");
	else if (type == DT_BLK)
		return ("block device");
	else
		return ("unknown type");
}
