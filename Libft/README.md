# Libft

This repository contains my implementation of **Libft**, a personal library of standard C functions and custom utility functions, developed as part of the [42](https://www.42.fr/) curriculum.

![Score: 125%](https://img.shields.io/badge/Score-125%25-green?style=flat&logo=42)
![License: MIT](https://img.shields.io/badge/License-MIT-blue)
![C](https://img.shields.io/badge/language-C-blue)
![Stars](https://img.shields.io/github/stars/yoyoazs/42-projects?style=social)
![Platform](https://img.shields.io/badge/Platform-Linux-blue)

I completed this project with a score of **125%**, as I successfully implemented all mandatory functions as well as additional bonus features.

In this version of **Libft**, I have implemented all mandatory functions required by the curriculum, along with a few bonus features that I created for personal use.

## Mandatory Functions

The library includes the following mandatory functions:

### Memory Functions
- [`ft_memset`](src/memory/ft_memset.c)
- [`ft_bzero`](src/memory/ft_bzero.c)
- [`ft_memcpy`](src/memory/ft_memcpy.c)
- [`ft_memmove`](src/memory/ft_memmove.c)
- [`ft_memchr`](src/memory/ft_memchr.c)
- [`ft_memcmp`](src/memory/ft_memcmp.c)
- [`ft_calloc`](src/memory/ft_calloc.c)

### String Functions
- [`ft_strlen`](src/string/ft_strlen.c)
- [`ft_strdup`](src/string/ft_strdup.c)
- [`ft_strlcpy`](src/string/ft_strncpy.c)
- [`ft_strlcat`](src/string/ft_strlcat.c)
- [`ft_strchr`](src/search/ft_strchr.c)
- [`ft_strrchr`](src/search/ft_strrchr.c)
- [`ft_strnstr`](src/search/ft_strnstr.c)
- [`ft_strncmp`](src/search/ft_strncmp.c)
- [`ft_split`](src/string/ft_split.c)
- [`ft_strjoin`](src/string/ft_strjoin.c)
- [`ft_substr`](src/string/ft_substr.c)
- [`ft_strtrim`](src/string/ft_strtrim.c)

### Write Functions
- [`ft_putchar_fd`](src/write/ft_putchar_fd.c)
- [`ft_putendl_fd`](src/write/ft_putendl_fd.c)
- [`ft_putnbr_fd`](src/write/ft_putnbr_fd.c)
- [`ft_putstr_fd`](src/write/ft_putstr_fd.c)

### Character Functions
- [`ft_isalpha`](src/types/ft_isalpha.c)
- [`ft_isdigit`](src/types/ft_isdigit.c)
- [`ft_isalnum`](src/types/ft_isalnum.c)
- [`ft_isascii`](src/types/ft_isascii.c)
- [`ft_isprint`](src/types/ft_isprint.c)
- [`ft_toupper`](src/string/ft_toupper.c)
- [`ft_tolower`](src/string/ft_tolower.c)

### Conversion Functions
- [`ft_itoa`](src/convert/ft_itoa.c)
- [`ft_atoi`](src/convert/ft_atoi.c)

### Utility Function
- [`ft_striteri`](src/ft_striteri.c)
- [`ft_strmapi`](src/ft_strmapi.c)

### Bonus Part (List function)
- [`ft_lstnew`](src/list/ft_lstnew.c)
- [`ft_lstadd_front`](src/list/ft_lstadd_front.c)
- [`ft_lstsize`](src/list/ft_lstsize.c)
- [`ft_lstlast`](src/list/ft_lstlast.c)
- [`ft_lstadd_back`](src/list/ft_lstadd_back.c)
- [`ft_lstdelone`](src/list/ft_lstdelone.c)
- [`ft_lstclear`](src/list/ft_lstclear.c)
- [`ft_lstiter`](src/list/ft_lstiter.c)
- [`ft_lstmap`](src/list/ft_lstmap.c)

## Personal Enhancements

In addition to the mandatory functions required by the 42 curriculum, I have implemented several personal enhancements to extend the functionality of this library. These features are not part of the curriculum but provide additional utility:

- **Garbage Collector (GC)**: A custom memory management system that tracks and frees dynamically allocated memory to prevent memory leaks.
- **`ft_strcpy`**: A custom implementation of `strcpy`.
- **`ft_strcmp`**: A custom implementation of `strcmp`.
- **`ft_uitoa`**: Converts an unsigned integer to a string representation.
- **`ft_hexlen`**: Returns the length of a number in hexadecimal format.
- **`ft_ptrlen`**: Returns the length of a pointer when formatted as a string.
- **`ft_ulen`**: Returns the length of an unsigned integer when represented as a string.
- **`ft_strtoupper`**: Converts all characters in a string to uppercase.
- **`ft_rand`**: A simple random number generator function for testing purposes.

These enhancements provide extra features that I personally find useful for various projects.
## License

This repository is a personal collection of my work from 42. It is not meant for commercial use. All code is available under the [LICENSE](../LICENSE).