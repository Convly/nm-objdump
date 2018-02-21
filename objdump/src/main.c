/*
** main.c for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/objdump/src
**
** Made by jsx
** Login   <jsx@epitech.net>
**
** Started on  Wed Feb 22 12:30:02 2017 jsx
** Last update Sun Feb 26 13:32:51 2017 jsx
*/

#include "objdump.h"

void			objdump(char *binaryName, char *filename)
{
  void			*data;
  Elf64_Ehdr		*elf;
  int			fd;
  long			size;

  if ((data = init(filename, &fd, &size, binaryName)) == NULL
      || data == MAP_FAILED)
    return ;
  elf = (Elf64_Ehdr*)data;
  (elf->e_ident[EI_CLASS] == ELFCLASS32)?
    objdump_32arch(data, filename, size, binaryName):
    objdump_64arch(data, filename, size, binaryName);
  close(fd);
  if (munmap(data, size) == -1)
    fprintf(stderr, "error: munmap: %s\n", strerror(errno));
}

int			main(int argc, char **argv)
{
  int	       		i;

  if (argc > 1)
    {
      i = 1;
      while (i < argc)
	{
	  objdump(argv[0], argv[i]);
	  i += 1;
	}
    }
  else
    objdump(argv[0], strdup("./a.out"));
  return (0);
}
