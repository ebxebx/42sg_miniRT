/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:01:10 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/19 17:07:54 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);

size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dest, const char *src, size_t dstsize);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *str, const char *to_find,
						size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(const char *src);
char				*ft_strndup(const char *src, size_t n);

int					ft_chrcnt(const char *str, char c);

int					ft_tolower(int c);
int					ft_toupper(int c);

int					ft_atoi(const char *str);
long				ft_atol(const char *str);
double				ft_atof(const char *str);
char				*ft_itoa(int n);

void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);

char				*ft_strjoin(const char *s1, const char *s2);
char				**ft_split(const char *s, char c);
char				*ft_substr(const char *s, unsigned int start, size_t len);
char				*ft_strtrim(const char *s1, const char *set);
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_strarr_len(char **arr);
void				ft_strarr_free(char **arr);

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int nbr, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstpop(t_list **lst);
t_list				*ft_lstpop_back(t_list **lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
int					ft_lstsize(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

size_t				ft_abs(int x);
int					ft_printf(const char *fmt, ...);
int					ft_dprintf(int fd, const char *fmt, ...);
int					ft_vprintf(const char *fmt, va_list *args);
int					ft_vdprintf(int fd, const char *fmt, va_list *args);

char				*get_next_line(int fd);

int					ft_min(int a, int b);
int					ft_max(int a, int b);
double				ft_minf(double a, double b);
double				ft_maxf(double a, double b);

#endif
