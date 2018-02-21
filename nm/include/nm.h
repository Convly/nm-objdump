/*
** objdump.h for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/nm/include
**
** Made by jsx
** Login   <jsx@epitech.net>
**
** Started on  Sun Feb 26 16:02:37 2017 jsx
** Last update Sun Feb 26 21:44:26 2017 jsx
*/

#ifndef OBJDUMP_H_
# define OBJDUMP_H_

#include <stdio.h>
#include <elf.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

void		*init(char* filename, int* fd, long* size);
char*		pError(char*, char*);
int		truncateCheck(void *, void *);
void		nm_32arch(void *, char *, long);
int		checkSection32(Elf32_Shdr*, int);
int		sectTruncateCheck32(Elf32_Ehdr*, Elf32_Shdr*, long);
int		getSectionByName32(Elf32_Ehdr*, Elf64_Shdr*, char*,
				   char*);
char		getType32(Elf32_Sym*, Elf32_Shdr*);
void		nm_64arch(void *, char *, long);
int		checkSection64(Elf64_Shdr*, int);
int		sectTruncateCheck64(Elf64_Ehdr*, Elf64_Shdr*, long);
int		getSectionByName64(Elf64_Ehdr*, Elf64_Shdr*, char*,
				   char*);
char		getType64(Elf64_Sym*, Elf64_Shdr*);

extern char*	binaryName;
extern int	nbArg;

#endif /* end of include guard: OBJDUMP_H_ */
