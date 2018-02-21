/*
** utils.c for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/objdump/src
**
** Made by jsx
** Login   <jsx@epitech.net>
**
** Started on  Sat Feb 25 12:05:07 2017 jsx
** Last update Sun Feb 26 18:41:29 2017 jsx
*/

#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include "objdump.h"

void		*init(char* fn, int* fd, long* size, char* binaryName)
{
  void	*data;

  if (access(fn, R_OK) == -1)
    return (pError(strdup("Permission denied"), fn, binaryName));
  if (((*fd) = open(fn, O_RDONLY, 0)) == -1)
    return (pError(strdup("No such file"), fn, binaryName));
  if (((*size) = lseek((*fd), 0, SEEK_END)) == -1)
    {
      fprintf(stderr, "error: lseek: %s\n", strerror(errno));
      return (NULL);
    }
  if ((data = mmap(NULL, (*size),
		     PROT_READ, MAP_SHARED, (*fd), 0)) == MAP_FAILED && (*size) > 0)
    {
      close((*fd));
      fprintf(stderr, "%s: Warning: '%s' is not an ordinary file\n",
	      binaryName, fn);
      return (MAP_FAILED);
    }
  return (data);
}

char*		pError(char* errorMsg, char* fileName, char* binaryName)
{
  fprintf(stderr, "%s: '%s': %s\n", binaryName, fileName, errorMsg);
  return (NULL);
}

int		truncateCheck(void *pos, void *end)
{
  if (pos > end)
    return (1);
  return (0);
}

int		getAddrSize(long int addr)
{
  long int	i;
  int		cc;

  i = 1;
  cc = 0;
  while (i < addr || cc < 4)
    {
      i *= 16;
      cc += 1;
    }
  return (cc);
}
