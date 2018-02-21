/*
** objdump_32arch.c for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/objdump/src
**
** Made by jsx
** Login   <jsx@epitech.net>
**
** Started on  Sat Feb 25 11:19:49 2017 jsx
** Last update Sun Feb 26 18:33:20 2017 jsx
*/

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "objdump.h"

static int		check_elf_format(Elf32_Ehdr *elf,
					 char *path, char* binaryName)
{
  if (elf->e_ident[EI_MAG0] != ELFMAG0
      || elf->e_ident[EI_MAG1] != ELFMAG1
      || elf->e_ident[EI_MAG2] != ELFMAG2
      || elf->e_ident[EI_MAG3] != ELFMAG3
      || (elf->e_type != ET_EXEC && elf->e_type
	  != ET_REL && elf->e_type != ET_DYN))
    {
      fprintf(stderr, "%s: %s: File format not recognized\n",
	      binaryName, path);
      return (-1);
    }
  return (1);
}

static void		print_ascii(unsigned int j,
				    unsigned int *z,
				    unsigned char *w,
				    char *t)
{
  int			x;

  x = j;
  while (x % 16 != 0)
    {
      if (x % 4 == 0 && x % 16)
	printf(" ");
      printf("  ");
      ++x;
    }
  printf("  ");
  while (*z < j)
    {
      if (isprint(w[*z]))
	printf("%c", t[*z]);
      else
	printf(".");
      (*z)++;
    }
  while ((*z)++ % 16 != 0)
    printf(" ");
  *z = j;
  printf("\n");
}

static void		print_sect(char *strtab,
				   Elf32_Ehdr *elf,
				   Elf32_Shdr *shdr,
				   int i)
{
  unsigned char		*w;
  unsigned int		j;
  int			addr;
  unsigned int		z;

  addr = shdr[i].sh_addr;
  printf("Contents of section %s:\n", &strtab[shdr[i].sh_name]);
  w = (unsigned char*)((char*)elf + shdr[i].sh_offset);
  j = 0;
  z = 0;
  while (j < shdr[i].sh_size)
    {
      if (j % 16 == 0)
	printf(" %0*x ", getAddrSize((long int)(shdr[i].sh_addr
						+ shdr[i].sh_size)), addr);
      printf("%02x", w[j++]);
      if (j % 4 == 0 && j % 16 && j < shdr[i].sh_size)
	printf(" ");
      if (j % 16 == 0)
	addr += 16;
      if (j % 16 == 0 || j >= shdr[i].sh_size)
	print_ascii(j, &z, w, (char*)w);
    }
}

static void		print_section32(char *tab,
					Elf32_Ehdr *elf,
					Elf32_Shdr *shdr)
{
  int			i;

  i = 0;
  while (i < elf->e_shnum)
    {
      if (checkSection32(shdr, i))
	print_sect(tab, elf, shdr, i);
      i += 1;
    }
}

void			objdump_32arch(void *data, char *filename,
				       long size, char* binaryName)
{
  Elf32_Ehdr		*elf;
  Elf32_Shdr		*shdr;
  char			*strtab;
  int			tc;

  elf = (Elf32_Ehdr*)data;
  if (check_elf_format(elf, filename, binaryName) == -1)
    return ;
  shdr = (Elf32_Shdr*)((char*)data + elf->e_shoff);
  if ((tc = sectTruncateCheck32(elf, shdr, size)))
    {
      fprintf(stderr, "%s: %s: %s\n", binaryName, filename,
	      (tc == -1)? "File truncated": "File format not recognized");
      return ;
    }
  strtab = (char*)((char*)data + shdr[elf->e_shstrndx].sh_offset);
  printf("\n%s:%5cfile format elf32-i386\n", filename, ' ');
  printf("architecture: i386, flags 0x%.8x:\n", exprFlags32(elf, shdr));
  affFlags32(elf, shdr);
  printf("start address 0x%08x\n\n", elf->e_entry);
  print_section32(strtab, elf, shdr);
}
