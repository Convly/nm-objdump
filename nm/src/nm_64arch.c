/*
** nm_64arch.c for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/nm/src
**
** Made by jsx
** Login   <jsx@epitech.net>
**
** Started on  Sun Feb 26 16:17:01 2017 jsx
** Last update Sun Feb 26 22:01:19 2017 jsx
*/

#include "nm.h"

static int		check_elf_format(Elf64_Ehdr *elf,
					 char *path)
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

static int		dumpSymbol64(Elf64_Sym *symTab,
				     long int size,
				     Elf64_Shdr *shdr,
				     unsigned char *strtab)
{
  int		       	i;
  Elf64_Sym		symbol;
  char			charSymbol;

  i = 0;
  while (i < size)
    {
      symbol = symTab[i];
      if (symbol.st_info != STT_FILE && symbol.st_name != 0)
	{
	  charSymbol = getType64(&symbol, shdr);
	  if ((unsigned int)symbol.st_value == 0
	      && (charSymbol == 'w'
		  || charSymbol == 'U'))
	    printf("                 ");
	  else
	    printf("%016x ", (unsigned int)symbol.st_value);
	  printf("%c ", getType64(&symbol, shdr));
	  printf("%s\n", &strtab[symbol.st_name]);
	}
      i += 1;
    }
  return (0);
}

static int		printSymbols64(Elf64_Ehdr *elf,
				       Elf64_Shdr *shdr,
				       void* data,
				       char* filename)
{
  int			i;
  Elf64_Sym		*symTab;
  unsigned char*	strtab;
  long int		size;
  int			finded;

  i = finded = -1;
  while (++i < elf->e_shnum)
    {
      if (shdr[i].sh_type == SHT_SYMTAB)
	{
	  strtab = data + shdr[shdr[i].sh_link].sh_offset;
	  symTab = (Elf64_Sym *)((char *)elf + shdr[i].sh_offset);
	  size = shdr[i].sh_size / shdr[i].sh_entsize;
	  i = elf->e_shnum;
	  finded = 0;
	}
    }
  if (!finded)
    {
      if (nbArg > 2)
	printf("\n%s:\n", filename);
      return (dumpSymbol64(symTab, size, shdr, strtab));
    }
  return (-1);
}

void			nm_64arch(void *data,
				  char *filename,
				  long size)
{
  Elf64_Ehdr		*elf;
  Elf64_Shdr		*shdr;
  int			tc;

  elf = (Elf64_Ehdr*)data;
  if (check_elf_format(elf, filename) == -1)
    return ;
  shdr = (Elf64_Shdr*)((char*)data + elf->e_shoff);
  if ((tc = sectTruncateCheck64(elf, shdr, size)))
    {
      fprintf(stderr, "%s: %s: %s\n", binaryName, filename,
	      (tc == -1)? "File truncated": "File format not recognized");
      return ;
    }
  if (printSymbols64(elf, shdr, data, filename) == -1)
    printf("%s: %s: %s\n", binaryName, filename, "no symbols");
}
