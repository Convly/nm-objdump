/*
** objdump64_utils.c for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/objdump/src
**
** Made by jsx
** Login   <jsx@epitech.net>
**
** Started on  Sat Feb 25 16:14:30 2017 jsx
** Last update Sun Feb 26 14:32:07 2017 jsx
*/

#include "objdump.h"

uint32_t		exprFlags64(Elf64_Ehdr *elf, Elf64_Shdr *shdr)
{
  uint32_t		flags;
  int			symFlag;
  int			i;

  flags = symFlag = i = 0;
  if (elf->e_type == ET_REL)
    flags |= HAS_RELOC;
  if (elf->e_type == ET_EXEC)
    flags |= EXEC_P;
  while (i < elf->e_shnum)
    {
      if (shdr[i].sh_type != SHT_SYMTAB || shdr[i].sh_type != SHT_DYNAMIC)
	symFlag = 1;
      i += 1;
    }
  if (symFlag == 1)
    flags |= HAS_SYMS;
  if (elf->e_type == ET_DYN)
    flags |= DYNAMIC;
  if (elf->e_phnum != 0)
    flags |= D_PAGED;
  return (flags);
}

void			affFlags64(Elf64_Ehdr *elf, Elf64_Shdr *shdr)
{
  int		 	disp;
  int			symFlag;
  int			i;

  disp = symFlag = i = 0;
  if (elf->e_type == ET_REL)
    disp += printf("HAS_RELOC");
  if (elf->e_type == ET_EXEC)
    disp += printf((disp)? ", EXEC_P": "EXEC_P");
  while (i < elf->e_shnum)
    {
      if (shdr[i].sh_type != SHT_SYMTAB || shdr[i].sh_type != SHT_DYNAMIC)
	symFlag = 1;
      i += 1;
    }
  if (symFlag == 1)
    disp += printf((disp)? ", HAS_SYMS": "HAS_SYMS");
  if (elf->e_type == ET_DYN)
    disp += printf((disp)? ", DYNAMIC": "DYNAMIC");
  if (elf->e_phnum != 0)
    disp += printf((disp)? ", D_PAGED": "D_PAGED");
  printf("\n");
}

int			checkSection64(Elf64_Shdr *shdr, int i)
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

int			sectTruncateCheck64(Elf64_Ehdr *elf,
					    Elf64_Shdr *shdr,
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
