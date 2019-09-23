#ifndef __bit_array_h__
#define __bit_array_h__
#include <stddef.h> /* size_t */

typedef size_t bit_arr_t;

/* count bits that are set to '1' or '0' */
size_t BitArrCountOn(bit_arr_t bit_arr);
size_t BitArrCountOff(bit_arr_t bit_arr);

/* perform "bit reversal" on our value */
bit_arr_t BitArrMirror(bit_arr_t bit_arr);

/* check spesific bit value, if '1' or '0' */
int BitArrIsOn(bit_arr_t bit_arr, int index);
int BitArrIsOff(bit_arr_t bit_arr, int index);

/* set all elements in bit_arr to '1' */
bit_arr_t BitArrSetAll(bit_arr_t bit_arr);
/* set all elements in bit_arr to '0' */
bit_arr_t BitArrResetAll(bit_arr_t bit_arr);

/* put elements in bit_arr into string */
char *BitArrToString(bit_arr_t bit_arr, char *str);

/* flip the value of element in spesific position */
bit_arr_t BitArrFlip(bit_arr_t bit_arr, int index);

/* set the value of element in spesific position to '1' or '0' */
bit_arr_t BitArrSetOn(bit_arr_t bit_arr, int index);
bit_arr_t BitArrSetOff(bit_arr_t bit_arr, int index);

/* set the value of element in spesific position to val */
bit_arr_t BitArrSet(bit_arr_t bit_arr, int index, int val);

/* rotate right/left our array */
bit_arr_t BitArrRotR(bit_arr_t bit_arr, size_t num_rotations);
bit_arr_t BitArrRotL(bit_arr_t bit_arr, size_t num_rotations);

size_t BitArrCountOnLUT(bit_arr_t bit_arr);

#endif /* end of __bit_array_h__ */
