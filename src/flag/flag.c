/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:24:59 by dacortes          #+#    #+#             */
/*   Updated: 2025/05/14 14:53:09 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flag.h"
#include "errors.h"

/**
 * @brief Parses a string of flag characters and sets the corresponding fields
 *        in the t_flags structure to true.
 *
 * @param flags A pointer to a t_flags structure where the parsed flags will
 * be stored.
 * @param arg A string containing the flag characters to be parsed.
 * 
 * @return A short integer indicating whether any flags were successfully set.
 *         Returns true (non-zero) if at least one flag was set,
 *         otherwise false (zero).
 *
 * @note The function assumes that the characters in the `arg` string correspond
 *       to predefined flag constants (e.g., `long_format`, `recursive`, etc.).
 *       These constants must be defined elsewhere in the program.
 */
static short	put_flags(t_flags *flags, char *arg)
{
	int	iter;
	int	status;

	iter = 0;
	status = false;
	while (arg[iter])
	{
		if (arg[iter] == long_format)
			flags->long_format = true;
		else if (arg[iter] == recursive)
			flags->recursive = true;
		else if (arg[iter] == all)
			flags->all = true;
		else if (arg[iter] == reverse)
			flags->reverse = true;
		else if (arg[iter] == time)
			flags->time = true;
		status = true;
		iter++;
	}
	return (status);
}

/**
 * @brief Checks if the given argument is a valid flag.
 *
 * This function determines whether the provided argument string
 * consists of valid flags. A valid flag starts with a '-' character
 * followed by one or more of the following characters: 'l', 'R', 'a', 'r', 't'.
 *
 * @param arg The argument string to check.
 * @return Returns `true` (non-zero) if the argument is a valid flag,
 *         otherwise returns `false` (0).
 */
short	is_flag(char *arg)
{
	int	iter;

	iter = arg[0] == '-';
	while (arg[iter])
	{
		if (arg[iter] != 'l' || arg[iter] != 'R' || arg[iter] != 'a'
			|| arg[iter] != 'r' || arg[iter] != 't')
			return (false);
		iter++;
	}
	return (true);
}

/**
 * analyze_args - Analyzes command-line arguments and processes flags.
 *
 * @flags: Pointer to a t_flags structure where parsed flags will be stored.
 * @num_args: The number of command-line arguments.
 * @args: Array of strings representing the command-line arguments.
 *
 * This function iterates through the provided command-line arguments and checks
 * if they start with a '-' character, indicating a flag. If the argument is a
 * valid flag, it processes the flag and updates the flags structure. If an
 * invalid flag is encountered, the program exits with an error message.
 *
 * Return: A short integer indicating the status of flag processing:
 *         - true (non-zero) if at least one valid flag was processed.
 *         - false (zero) if no valid flags were processed.
 */
static short	analyze_args(t_flags *flags, int num_args, char **args)
{
	int	iter;
	int	status;

	iter = 0;
	status = false;
	while (iter < num_args)
	{
		if (args[iter] && args[iter][0] && args[iter][0] == '-')
		{
			if (is_flag(args[iter]) == false)
				exit(error_msg(INVALID, 2, args[iter]));
			status = put_flags(flags, args[iter]) || false;
		}
		iter++;
	}
	return (status);
}

/**
 * @brief Checks if any flags are present in the given arguments and
 * processes them.
 *
 * This function initializes the `flags` structure to zero, then analyzes
 * the provided arguments to determine if any flags are present.
 * If no arguments are provided or if the analysis fails, the 
 * function returns `false`.
 *
 * @param flags A pointer to a `t_flags` structure where the flags
 * will be stored.
 * @param num_args The number of arguments provided in the `args` array.
 * @param args An array of strings representing the command-line arguments.
 * @return `true` if flags are successfully analyzed and present,
 * otherwise `false`.
 */
short	has_flags(t_flags *flags, int num_args, char **args)
{
	ft_bzero(flags, sizeof(t_flags));
	if (num_args == 1)
		return (false);
	if (analyze_args(flags, num_args, args) == false)
		return (false);
	return (true);
}
