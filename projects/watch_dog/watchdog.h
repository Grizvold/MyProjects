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

/*  -Make calling process immortal - automatically reboot hanged systems due to 
        unrecoverable software errors. */
wd_t *MakeMeImmortal(char *path, char **argv, size_t frequency, size_t grace);

/*  -*/
void LetMeDie(wd_t *watchdog);
/******************************************************************************/

#endif /* __WATCHDOG_H_OL767__ */