#ifndef __LOL_COROUTINES_H
#define __LOL_COROUTINES_H

__M_BEGIN_DECLS

CORE_LIBSPEC extern int cr_fn_update;
CORE_LIBSPEC extern int cr_fn_title_screen;
CORE_LIBSPEC extern int cr_fn_play_game;
CORE_LIBSPEC extern int cr_reentry;
CORE_LIBSPEC extern int cr_throw;

__M_END_DECLS

#define cr_begin()                     \
  static int cr_state = 0;             \
  /*{ FILE *fx_fp = fopen("d:/tmp/cr_log.txt", "a"); fprintf(fx_fp, "cr_begin %s:%s:%d %d %d\n", __FILE__, __func__, __LINE__, cr_state, cr_reentry); fclose(fx_fp);}*/ \
  if (cr_reentry == 0) { \
    cr_state = 0; \
  }              \
                                       \
  switch (cr_state) { \
    case 0: \
      break \

#define cr_reenter(x) \
    case x: \
      goto cr_label_ ## x

#define cr_reenter_end() \
  }

#define cr_before(x)                       \
  do                                   \
  {                                    \
    /*{ FILE *fx_fp = fopen("d:/tmp/cr_log.txt", "a"); fprintf(fx_fp, "cr_before(%d) %s:%s:%d %d %d\n", x, __FILE__, __func__, __LINE__, cr_state, cr_reentry); fclose(fx_fp);}*/ \
    cr_state = x;                      \
    cr_label_ ## x:;                   \
    /*if (cr_reentry) cr_state = 0;*/      \
  } while(0)                           

#define cr_after(...) \
  do \
  { \
    if (cr_throw) return __VA_ARGS__; \
  } while(0)

#define cr_delay(x)                       \
  do                                   \
  {                                    \
    /*{ FILE *fx_fp = fopen("d:/tmp/cr_log.txt", "a"); fprintf(fx_fp, "cr_delay(%d) %s:%s:%d %d %d\n", x, __FILE__, __func__, __LINE__, cr_state, cr_reentry); fclose(fx_fp);}*/ \
    if (cr_reentry == 0) { \
      cr_reentry = 1; \
      /*longjmp(main_game_loop_env, x + 1);*/ \
      cr_throw = x + 1; \
    } else { \
      cr_reentry = 0; \
    } \
  } while(0)


#endif /* __LOL_COROUTINES_H */
