/*
** EPITECH PROJECT, 2020
** wordtab
** File description:
** wordtab
*/

#ifndef WORDTAB_H_
# define WORDTAB_H_

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int wt_free_tab(char **tab);
int wt_utils(char *str, char **delims, int mode, int pos);
int wt_count_elems(char *str, char **delims);
char *wt_epur_str(char *str, char **delims, int free_str);
char **wordtab(char *str, char **delims);

#endif /* !WORDTAB_H_ */