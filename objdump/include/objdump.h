/*
** objdump.h for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/objdump/include
**
** Made by jsx
** Login   <jsx@epitech.net>
**
** Started on  Wed Feb 22 12:30:48 2017 jsx
** Last update Sun Feb 26 18:29:30 2017 jsx
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
#include "flags.h"

void		*init(char* filename, int* fd, long* size, char*);
char*		pError(char*, char*, char*);
int		truncateCheck(void *, void *);
int		getAddrSize(long int);
void		objdump_32arch(void*, char*, long, char*);
uint32_t	exprFlags32(Elf32_Ehdr*, Elf32_Shdr*);
void		affFlags32(Elf32_Ehdr*, Elf32_Shdr*);
int		checkSection32(Elf32_Shdr*, int);
int		sectTruncateCheck32(Elf32_Ehdr *elf,
				    Elf32_Shdr *shdr,
				    long size);
void		objdump_64arch(void*, char*, long, char*);
uint32_t	exprFlags64(Elf64_Ehdr*, Elf64_Shdr*);
void		affFlags64(Elf64_Ehdr*, Elf64_Shdr*);
int		checkSection64(Elf64_Shdr*, int);
int		sectTruncateCheck64(Elf64_Ehdr*, Elf64_Shdr*, long);

#endif /* end of include guard: OBJDUMP_H_ */
