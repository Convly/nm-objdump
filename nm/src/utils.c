/*
** utils.c for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/nm/src
**
** Made by jsx
** Login   <jsx@epitech.net>
**
** Started on  Sun Feb 26 16:17:23 2017 jsx
** Last update Sun Feb 26 22:00:28 2017 jsx
*/

#include "nm.h"

void		*init(char* fn, int* fd, long* size)
{
  void		*data;

  if (access(fn, R_OK) == -1)
    return (pError(strdup("Permission denied"), fn));
  if (((*fd) = open(fn, O_RDONLY, 0)) == -1)
    return (pError(strdup("No such file"), fn));
  if (((*size) = lseek((*fd), 0, SEEK_END)) == -1)
    {
      fprintf(stderr, "error: lseek: %s\n", strerror(errno));
      return (NULL);
    }
  if ((data = mmap(NULL, (*size),
		   PROT_READ, MAP_SHARED, (*fd), 0))
      == MAP_FAILED && (*size) > 0)
    {
      close((*fd));
      fprintf(stderr, "%s: Warning: '%s' is not an ordinary file\n",
	      binaryName, fn);
      return (MAP_FAILED);
    }
  return (data);
}

char*		pError(char* errorMsg, char* fileName)
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
