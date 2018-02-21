/*
** nm64_utils.c for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/nm/src
**
** Made by jsx
** Login   <jsx@epitech.net>
**
** Started on  Sun Feb 26 16:17:15 2017 jsx
** Last update Sun Feb 26 17:56:13 2017 jsx
*/

#include "nm.h"

int		getSectionByName64(Elf64_Ehdr *elf,
				   Elf64_Shdr *shdr,
				   char* sectName,
				   char* strtab)
{
  int		returnValue;
  int		i;

  returnValue = -1;
  i = 0;
  while (i < elf->e_shnum)
    {
      if (!strcmp(&strtab[shdr[i].sh_name], sectName))
	returnValue = i;
      i += 1;
    }
  return (returnValue);
}

int		checkSection64(Elf64_Shdr *shdr, int i)
{
  return (shdr[i].sh_type != SHT_NOBITS
	  && shdr[i].sh_name
	  && shdr[i].sh_size > 0
	  && shdr->sh_flags != SHF_INFO_LINK
	  && (shdr[i].sh_addr || (!shdr[i].sh_addr
				  && shdr[i].sh_type != SHT_STRTAB
				  && shdr[i].sh_type != SHT_RELA
				  && shdr[i].sh_type != SHT_REL
				  && shdr[i].sh_type != SHT_SYMTAB)));
}

int		sectTruncateCheck64(Elf64_Ehdr *elf,
				    Elf64_Shdr *shdr,
				    long size)
{
  size_t	i;

  i = 0;
  if ((elf->e_shnum * elf->e_shentsize +
       elf->e_shoff) > (unsigned long)size)
    {
      return (-1);
    }
  while (i < elf->e_shnum)
    {
      if (checkSection64(shdr, i))
	{
	  if ((shdr[i].sh_size +
	       shdr[i].sh_offset) >
	      (unsigned long)size) {
	    return (-2);
	  }
	}
      i += 1;
    }
  return (0);
}
