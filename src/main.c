#include "clear.h"
#include "errors.h"
#include "arguments.h"
#include "print_values.h"
#include "sort.h"


/*
	◦ write
	◦ opendir
	◦ readdir
	◦ closedir
	◦ stat
	◦ lstat
	◦ getpwuid
	◦ getgrgid
	◦ listxattr
	◦ getxattr
	◦ time
	◦ ctime
	◦ readlink
	◦ malloc
	◦ free
	◦ perror
	◦ strerror
	◦ exit
*/

// #include "libft.h"
// #include "ft_printf.h"
// #include <errno.h>
#include <pwd.h>
#include <string.h>
#include <sys/stat.h>

void	print_entries(struct dirent	**entries, int size)
{
	int	iter;

	if (!size || !entries || !*entries)
	{
		ft_printf(WARNING_POINTER, YELLOW, END, \
			"print_entries", "files");
		return ;
	}
	iter = 0;
	while(iter < size)
	{
		ft_printf("%sentires%s[%d] %s\n", BLUE, END, iter, entries[iter]->d_name);
		iter++;
	}
}

struct dirent	**curr_directory(t_flags flags, char *name, int *entry_count)
{
	struct dirent	**entries;
	DIR				*dir;

	(void)flags;
	dir = init_dir(name);
	if (!dir)
		return (NULL);
	entries = NULL;
	*entry_count = read_dir_entries(dir, &entries);
	sort_entries(entries, *entry_count, flags);
	if (flags.recursive == true)
		exec_recursive_flag(flags, entries[0]->d_name);
	closedir(dir);
	return (entries);
}

int main(int ac, char **av)
{
	struct dirent	**files;
	t_flags			flags;
	int				size_files;
	
	files = NULL;
	size_files = 0;
	if (has_flags(&flags, ac, &av[1]) == false && ac == 1)
	{
		flags.recursive = true;
		files = curr_directory(flags, "./", &size_files);
	}
	else
	{
		//hay que tener encuenta si son argumentos listados como parametro de entrada 
		//si es asi este debe mostrar primero los archivos regurares organizados por el tiempo
		size_files = get_size_files(&av[1]);
		files = is_file(flags, &av[1], size_files);
	}
	if (!files)
		return (0);
	print_entries(files, size_files);
	clear_entries(files, size_files, false);
	return (EXIT_SUCCESS);
}
