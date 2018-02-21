/*
** nm_32arch.c for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/nm/src
**
** Made by jsx
** Login   <jsx@epitech.net>
**
** Started on  Sun Feb 26 21:00:38 2017 jsx
** Last update Sun Feb 26 22:02:09 2017 jsx
*/

#include "nm.h"

static int		check_elf_format(Elf32_Ehdr *elf, char *path)
{
  if (elf->e_ident[EI_MAG0] != ELFMAG0
      || elf->e_ident[EI_MAG1] != ELFMAG1
      || elf->e_ident[EI_MAG2] != ELFMAG2
      || elf->e_ident[EI_MAG3] != ELFMAG3
      || (elf->e_type != ET_EXEC
	  && elf->e_type != ET_REL
	  && elf->e_type != ET_DYN))
    {
      fprintf(stderr, "%s: %s: File format not recognized\n",
	      binaryName, path);
      return (-1);
    }
  return (1);
}

static int		dumpSymbol32(Elf32_Sym *symTab,
				     long int size, Elf32_Shdr *shdr,
				     unsigned char *strtab)
{
  int			i;
  Elf32_Sym		symbol;
  char			charSymbol;

  i = 0;
  while (i < size)
    {
      symbol = symTab[i];
      if (symbol.st_info != STT_FILE && symbol.st_name != 0)
	{
	  charSymbol = getType32(&symbol, shdr);
	  if ((unsigned int)symbol.st_value == 0
	      && (charSymbol == 'w'
		  || charSymbol == 'U'))
	    printf("         ");
	  else
	    printf("%08x ", (unsigned int)symbol.st_value);
	  printf("%c ", getType32(&symbol, shdr));
	  printf("%s\n", &strtab[symbol.st_name]);
	}
      i += 1;
    }
  return (0);
}

static int		printSymbols32(Elf32_Ehdr *elf,
				       Elf32_Shdr *shdr,
				       void* data,
				       char* filename)
{
  int			i;
  Elf32_Sym		*symTab;
  unsigned char*	strtab;
  long int		size;
  int			finded;

  i = finded = -1;
  while (++i < elf->e_shnum)
    {
      if (shdr[i].sh_type == SHT_SYMTAB)
	{
	  strtab = data + shdr[shdr[i].sh_link].sh_offset;
	  symTab = (Elf32_Sym *)((char *)elf + shdr[i].sh_offset);
	  size = shdr[i].sh_size / shdr[i].sh_entsize;
	  i = elf->e_shnum;
	  finded = 0;
	}
    }
  if (!finded)
    {
      if (nbArg > 2)
	printf("\n%s:\n", filename);
      return (dumpSymbol32(symTab, size, shdr, strtab));
    }
  return (-1);
}

void			nm_32arch(void *data, char *filename,
				  long size)
{
  Elf32_Ehdr		*elf;
  Elf32_Shdr		*shdr;
  int			tc;

  elf = (Elf32_Ehdr*)data;
  if (check_elf_format(elf, filename) == -1)
    return ;
  shdr = (Elf32_Shdr*)((char*)data + elf->e_shoff);
  if ((tc = sectTruncateCheck32(elf, shdr, size)))
    {
      fprintf(stderr, "%s: %s: %s\n", binaryName, filename,
	      (tc == -1)? "File truncated": "File format not recognized");
      return ;
    }
  if (printSymbols32(elf, shdr, data, filename) == -1)
    printf("%s: %s: %s\n", binaryName, filename, "no symbols");
}
