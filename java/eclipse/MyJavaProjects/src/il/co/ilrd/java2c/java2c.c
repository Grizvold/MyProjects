#include <stdio.h>  /* printf          */
#include <stdlib.h> /* malloc,free     */
/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Gabriel Yamin.                                                   */
/* Group: FS767                                                               */
/* Description: Java2c implementation.                                        */
/******************************************************************************/
  
/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/
static const char *SET_RED_COLOR = "\033[0;31m";
static const char *SET_BLUE_COLOR = "\033[0;34m";
static const char *SET_GREEN_COLOR = "\033[0;32m";
static const char *RESET_COLOR = "\033[0m";

typedef void (*(*vtable_t))();
typedef void (*method_t)();

static char g_toString_output[100];
static int g_counter = 0;

typedef struct 
{
    char *className;
    class_t *super;
    size_t size;
    vtable_t vtable;
} class_t;

typedef struct 
{
    class_t *class;
} object_t;

enum {HASHCODE = 0, 
        TOSTRING,
        EQUALS,
        GETCLASS};

method_t object_static_blocks[] = {StaticBlocks};
method_t object_anonymous_blocks[] = {AnonymousBlocks};
method_t object_build_in_methods[] = {(method_t)hashCode, 
                                        (method_t)toString, 
                                        (method_t)equals, 
                                        (method_t)getClass};
/******************************************************************************/

/******************************************************************************/
/*                          Java2C Functions Declaration                      */
/******************************************************************************/
size_t hashCode(object_t *obj);
char *toString(object_t *obj);
int equals(object_t *obj1, object_t *obj2);
class_t *getClass(object_t *obj);

void AnonymousBlocks();
void StaticBlocks();
/******************************************************************************/

/******************************************************************************/
/*                          Java2C Functions Definition                       */
/******************************************************************************/
size_t hashCode(object_t *obj)
{
        size_t result = 17;
		size_t prime = 31;
		
		result = prime * result + (size_t)(obj);
		
		return result;
}

char *toString(object_t *obj)
{
    sprintf(g_toString_output, "%s@%lu", obj->class->className, hashCode(obj));

    return g_toString_output;
}

int equals(object_t *obj1, object_t *obj2)
{
	return (obj1 == obj2);
}

class_t *getClass(object_t *obj)
{
    return obj->class;
}


class_t *ClassLoader()
{
    
}

object_t *CreateInstance(class_t *class)
{
    object_t *obj = NULL;
    obj = (object_t *)malloc(class->size);

    obj->class = class;

    return obj;
}

void AnonymousBlocks()
{
    printf("Anonymous block initialization\n");
}

void StaticBlocks()
{
    printf("Static block initialization\n");
}
/******************************************************************************/



/******************************************************************************/
/*                              main function                                 */
/******************************************************************************/
int main(int argc, char* argv[])
{


    return 0;
}
/******************************************************************************/
