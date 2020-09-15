/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** files.h
*/

#ifndef NORMINETTE_FILES_H
#define NORMINETTE_FILES_H


#include <stddef.h>
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

size_t get_file_size(const char *path);
#ifdef _WIN32
const char *get_file_name(const char *path);
#else
#define get_file_name(path) strrchr(path, '/')
#endif

#endif //NORMINETTE_FILES_H
