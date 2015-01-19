#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef NDEBUG
#define debug_printf(...) do{ fprintf( stderr, __VA_ARGS__ ); } while(0)
#else
#define debug_printf(...) do{ } while (0)
#endif

#endif
