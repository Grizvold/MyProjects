#ifndef __WATCHDOG_H_OL767__
#define __WATCHDOG_H_OL767__

#include <stddef.h> /* size_t */

/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

typedef struct watchdog wd_t;
/******************************************************************************/

/******************************************************************************/
/*                          Watch_Dog Functions Declaration                   */
/******************************************************************************/

/*  -Make calling process immortal - automatically reboot the calling process 
        due to unrecoverable software errors.
    -Returns handler to watchdog struct. */
wd_t *MakeMeImmortal(char *path, char **argv, size_t frequency, size_t grace);

/*  -Stops immortal process from refreshing and restarting. */
void LetMeDie(wd_t *watchdog);
/******************************************************************************/

#endif /* __WATCHDOG_H_OL767__ */