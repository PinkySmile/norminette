//
// Created by andgel on 04/09/2020
//

#ifndef NORMINETTE_DEBUG_H
#define NORMINETTE_DEBUG_H

#ifndef NDEBUG
#define log_debug(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#else
#define log_debug(...) (void)(0)
#endif

#endif //NORMINETTE_DEBUG_H
