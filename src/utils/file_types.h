/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** file_types.h
*/

#ifndef NORMINETTE_FILE_TYPES_H
#define NORMINETTE_FILE_TYPES_H


#include <sys/stat.h>
#include <stdbool.h>

bool is_type(const char *path, unsigned type);

#ifndef _WIN32
#define is_sock(path)    is_type(path, S_IFSOCK)
#define is_symlink(path) is_type(path, S_IFLNK)
#endif
#define is_reg_file(path)is_type(path, S_IFREG)
#define is_blk_dev(path) is_type(path, S_IFBLK)
#define is_dir(path)     is_type(path, S_IFDIR)
#define is_chr_dev(path) is_type(path, S_IFCHR)
#define is_fifo(path)    is_type(path, S_IFIFO)


#endif //NORMINETTE_FILE_TYPES_H
