#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef DEBUG
#define debug_printf(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define debug_printf(fmt, ...) do {} while (0)
#endif

#endif
