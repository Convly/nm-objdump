/*
** nm64_sym.c for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/nm/src
**
** Made by jsx
** Login   <jsx@epitech.net>
**
** Started on  Sun Feb 26 17:21:48 2017 jsx
** Last update Sun Feb 26 22:30:51 2017 jsx
*/

#include "nm.h"

static char     is_undefined(Elf64_Sym *sym)
{
  if (sym->st_shndx == SHN_UNDEF)
    {
      if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
	return ('U');
      if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
	return ('u');
      if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
	return ('w');
    }
  if (sym->st_shndx == SHN_COMMON)
    return ('C');
  return (0);
}

static char     is_data(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  if ((shdr[sym->st_shndx].sh_type == SHT_PROGBITS
       && (shdr[sym->st_shndx].sh_flags & SHF_ALLOC))
      || (shdr[sym->st_shndx].sh_type == SHT_DYNAMIC))
    {
      if (shdr[sym->st_shndx].sh_flags & SHF_WRITE)
	{
	  if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
	    return ('D');
	  if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
	    return ('d');
	  if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
	    return ('W');
	}
      else
	{
	  if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
	    return ('R');
	  if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
	    return ('r');
	  if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
	    return ('W');
	}
    }
  return (0);
}

static char     is_exec_code(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  if (ELF64_ST_TYPE(sym->st_info) == STT_FUNC
      && shdr[sym->st_shndx].sh_type == SHT_PROGBITS
      && (shdr[sym->st_shndx].sh_flags & SHF_EXECINSTR)
      && (shdr[sym->st_shndx].sh_flags & SHF_ALLOC))
    {
      if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
	return ('T');
      if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
	return ('t');
      if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
	return ('W');
    }
  return (0);
}

static char     is_init_array(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  if ((ELF64_ST_TYPE(sym->st_info) == STT_OBJECT
       || ELF64_ST_TYPE(sym->st_info) == STT_NOTYPE)
      && (shdr[sym->st_shndx].sh_flags & SHF_WRITE)
      && (shdr[sym->st_shndx].sh_flags & SHF_ALLOC))
    {
      if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
	return ('T');
      if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
	return ('t');
      if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
	return ('W');
    }
  return ('?');
}

char            getType64(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
  char		ret;

  if ((ret = is_undefined(sym)) != 0)
    return (ret);
  if (sym->st_shndx == SHN_ABS)
    return ('A');
  if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT
      && ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    return ('V');
  if (shdr[sym->st_shndx].sh_type == SHT_NOBITS)
    {
      if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
	return ('B');
      if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
	return ('b');
      if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
	return ('W');
    }
  if ((ret = is_exec_code(sym, shdr)) != 0)
    return (ret);
  if ((ret = is_data(sym, shdr)) != 0)
    return (ret);
  ret = is_init_array(sym, shdr);
  return (ret);
}
