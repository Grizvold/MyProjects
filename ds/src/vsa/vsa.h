#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h>  /* size_t */

/***************************** VSA typedefs ***********************************/
typedef struct vsa vsa_t;
/******************************************************************************/

/**************** ************* VSA Functionality  *****************************/
vsa_t *VSAInit(void *buffer, size_t buff_size);

void *VSAAlloc(vsa_t *vsa, size_t n_bytes);

void VSAFree(void *block_data);

size_t VSAMaxFreeBlock(const vsa_t *vsa);
/******************************************************************************/

#endif /*__VSA_H__*/

