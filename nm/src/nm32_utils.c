/*
** nm32_utils.c for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/nm/src
**
** Made by jsx
** Login   <jsx@epitech.net>
**
** Started on  Sun Feb 26 16:17:04 2017 jsx
** Last update Sun Feb 26 17:40:33 2017 jsx
*/

#include "nm.h"

int		checkSection32(Elf32_Shdr *shdr, int i)
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

int		sectTruncateCheck32(Elf32_Ehdr *elf,
				    Elf32_Shdr *shdr,
				    long size)
{
  size_t i;

  i = 0;
  if ((elf->e_shnum * elf->e_shentsize +
       elf->e_shoff) > (unsigned long)size)
    {
      return (-1);
    }
  while (i < elf->e_shnum)
    {
      if (checkSection32(shdr, i))
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
