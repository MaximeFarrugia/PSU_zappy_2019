/*
** EPITECH PROJECT, 2018
** get_next_line
** File description:
** get_next_line
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# ifndef READ_SIZE
#  define READ_SIZE (1)
# endif /* !READ_SIZE */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void *x_memset(int c, size_t nmemb, size_t size);
char *my_realloc(char *ptr, size_t size);
int my_strlen(char *str);
int gnl_reread(int *is, int fd, char *buff, char **str);
char *get_next_line(int fd);

#endif /* !GET_NEXT_LINE_H_ */
