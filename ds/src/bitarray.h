#ifndef __bit_array_h__
#define __bit_array_h__
#include <stddef.h> /* size_t */

typedef size_t bit_array_t;

bit_array_t BitArrCreate();

size_t BitArrCountOn(bit_array_t bit_arr);
size_t BitArrCountOff(bit_array_t bit_arr);

bit_array_t BitArrMirror(bit_array_t bit_arr);

int BitArrIsOn(bit_array_t bit_arr, int index);
int BitArrIsOff(bit_array_t bit_arr, int index);

bit_array_t BitArrSetAll(bit_array_t bit_arr);
bit_array_t BitArrResetAll(bit_array_t bit_arr);

char *BitArrToString(bit_array_t bit_arr, char *str);

bit_array_t BitArrFlip(bit_array_t bit_arr, int index);

bit_array_t BitArrSetOn(bit_array_t bit_arr, int index);
bit_array_t BitArrSetOff(bit_array_t bit_arr, int index);

bit_array_t BitArrRotR(bit_array_t bit_arr, size_t num_rotations);
bit_array_t BitArrRotL(bit_array_t bit_arr, size_t num_rotations);



#endif /* end of __bit_array_h__ */
