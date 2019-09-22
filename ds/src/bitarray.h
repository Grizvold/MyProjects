#ifndef __bit_array_h__
#define __bit_array_h__
#include <stddef.h> /* size_t */
typedef size_t bit_array_t;

int BitArrIsOn(bit_array_t bit_arr, int index);
int BitArrIsOff(bit_array_t bit_arr, int index);

void BitArrSetOn(bit_array_t bit_arr, int index);
void BitArrSetOff(bit_array_t bit_arr, int index);

bit_array_t BitArrRotR(bit_array_t bit_arr, int num_rotations);
bit_array_t BitArrRotL(bit_array_t bit_arr, int num_rotations);
bit_array_t BitArrFlip(bit_array_t bit_arr, int index);

bit_array_t BitArrSetAll();
bit_array_t BitArrResetAll();

int BitArrCountOn(bit_array_t bit_arr);
int BitArrCountOff(bit_array_t bit_arr);

char *BitArrToString(bit_array_t bit_arr, char *str);

bit_array_t BitArrMirror(bit_array_t bit_arr);

bit_array_t BitArrCreate();




#endif /* end of __bit_array_h__ */
