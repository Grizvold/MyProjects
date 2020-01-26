#include <stdio.h>  /* printf          */
#include <stdlib.h> /* malloc,free     */
/******************************************************************************/
/* Name: Ruslan Gorbaty                                                       */
/* Reviewer: Doron Ben-Zaken.                                                 */
/* Group: FS767                                                               */
/* Description: Java2c implementation.                                        */
/******************************************************************************/
  
/******************************************************************************/
/*                          Typedefs Declaration                              */
/******************************************************************************/

typedef void (*(*vtable_t))();
typedef void (*method_t)();

static char g_toString_output[100];
static int g_animal_counter = 0;

enum FUNCTIONS{HASHCODE = 0, 
                TOSTRING,
                EQUALS,
                GETCLASS,
                SAYHELLO,
                GETNUMMASTERS};

typedef struct class
{
    char *className;
    struct class *super;
    size_t size;
    vtable_t vtable;
} class_t;

typedef struct 
{
    class_t *class;
} object_t;

typedef struct 
{
    object_t object_t;
    int num_legs;
    int num_masters;
    int ID;
} Animal_t;

typedef struct 
{
    Animal_t animal;
    int num_legs;
} Dog_t;

typedef struct
{
    Animal_t animal;
    char *colors;
    int num_masters;
} Cat_t;

typedef struct 
{
    Cat_t cat;
} LegendaryAnimal_t;


object_t *CreateInstance(class_t *class);
void foo(Animal_t *a);
/******************************************************************************/

/******************************************************************************/
/*                          Object Functions Declaration                      */
/******************************************************************************/

class_t *Object_ClassLoader();

size_t Object_hashCode(object_t *obj);
char *Object_toString(object_t *obj);
int Object_equals(object_t *obj1, object_t *obj2);
class_t *Object_getClass(object_t *obj);
/******************************************************************************/

/******************************************************************************/
/*                          Animal Functions Declaration                      */
/******************************************************************************/

class_t *Animal_ClassLoader(class_t *super);

void Animal_Static_Block_1();
void Animal_Static_Block_2();
void Animal_Anonymous_Block_1();
void Animal_Constructor_1(Animal_t *this);
void Animal_Constructor_2(Animal_t *this, int num_masters);
void Animal_sayHello(Animal_t *this);
void Animal_showCounter();
int Animal_getNumMasters(Animal_t *this);
char *Animal_toString(Animal_t * this);
/******************************************************************************/

/******************************************************************************/
/*                          Dog Functions Declaration                         */
/******************************************************************************/

class_t *Dog_ClassLoader(class_t *super);

void Dog_Static_Block_1();
void Dog_Anonymous_Block_1();
void Dog_Constructor(Dog_t *this);
void Dog_sayHello(Dog_t *this);
char *Dog_toString(Dog_t *this);
/******************************************************************************/

/******************************************************************************/
/*                          Cat Functions Declaration                         */
/******************************************************************************/

class_t *Cat_ClassLoader(class_t *super);

void Cat_Static_Block_1();
void Cat_Constructor_1(Cat_t *this);
void Cat_Constructor_2(Cat_t *this, char *colors);
char *Cat_toString(Cat_t *this);
/******************************************************************************/

/******************************************************************************/
/*                   LegendaryAnimal Functions Declaration                    */
/******************************************************************************/

class_t *LegendaryAnimal_ClassLoader(class_t *super);

void LegendaryAnimal_Static_Block_1();
void LegendaryAnimal_Constructor_1(LegendaryAnimal_t *this);
void LegendaryAnimal_sayHello(LegendaryAnimal_t *this);
char *LegendaryAnimal_toString(LegendaryAnimal_t *this);
/******************************************************************************/

/******************************************************************************/
/*                          Object Functions Definition                       */
/******************************************************************************/

void foo(Animal_t *a)
{
    printf("%s\n", ((char *(*)(Animal_t *))a->object_t.class->vtable[TOSTRING])(a));
}

object_t *CreateInstance(class_t *class)
{
    object_t *obj = NULL;
    obj = (object_t *)malloc(class->size);
    if(NULL == obj)
    {
        perror("Malloc in CreateInstance failed");
        return NULL;
    }

    obj->class = class;

    return obj;
}

class_t *Object_ClassLoader()
{
    class_t *object_class = NULL;
    method_t *object_functions = NULL;
    
    object_class = (class_t *)malloc(sizeof(class_t));
    if(NULL == object_class)
    {
        perror("Malloc in ObjectClassLoader class_t failed");
        return NULL;
    }

    object_functions = (method_t *)malloc(sizeof(method_t) * 4);
    if(NULL == object_functions)
    {
        free(object_class);
        perror("Malloc in ObjectClassLoader object_functions failed");
        return NULL;
    }

    object_functions[HASHCODE] = (method_t)Object_hashCode;
    object_functions[TOSTRING] = (method_t)Object_toString;
    object_functions[EQUALS] = (method_t)Object_equals;
    object_functions[GETCLASS] = (method_t)Object_getClass;

    object_class->className = "Object";
    object_class->size = sizeof(object_t);
    object_class->super = NULL;
    object_class->vtable = object_functions;

    return object_class;
}

size_t Object_hashCode(object_t *obj)
{
        size_t result = 17;
		size_t prime = 31;
		
		result = prime * result + (size_t)(obj);
		
		return result;
}

char *Object_toString(object_t *obj)
{
    sprintf(g_toString_output, "%s@%lu", obj->class->className, Object_hashCode(obj));

    return g_toString_output;
}

int Object_equals(object_t *obj1, object_t *obj2)
{
	return (obj1 == obj2);
}

class_t *Object_getClass(object_t *obj)
{
    return obj->class;
}
/******************************************************************************/

/******************************************************************************/
/*                          Animal Functions Definition                       */
/******************************************************************************/

class_t *Animal_ClassLoader(class_t *super)
{
    class_t *animal_class = NULL;
    method_t *animal_functions = NULL;

    animal_class = (class_t *)malloc(sizeof(class_t));
    if(NULL == animal_class)
    {
        perror("Malloc in ObjectClAnimal_ClassLoader animal_class failed");
        return NULL;
    }

    animal_functions = (method_t *)malloc(sizeof(method_t) * 6);
    if(NULL == animal_functions)
    {
        free(animal_class);
        perror("Malloc in ObjectClAnimal_ClassLoader animal_functions failed");
        return NULL;
    }

    animal_functions[HASHCODE] = (method_t)Object_hashCode;
    animal_functions[TOSTRING] = (method_t)Animal_toString;
    animal_functions[EQUALS] = (method_t)Object_equals;
    animal_functions[GETCLASS] = (method_t)Object_getClass;
    animal_functions[SAYHELLO] = (method_t)Animal_sayHello;
    animal_functions[GETNUMMASTERS] = (method_t)Animal_getNumMasters;

    animal_class->className = "Animal";
    animal_class->size = sizeof(Animal_t);
    animal_class->super = super;
    animal_class->vtable = animal_functions;

    Animal_Static_Block_1();
    Animal_Static_Block_2();

    return animal_class;
}

void Animal_Static_Block_1()
{
    printf("Static block Animal 1\n");
}

void Animal_Static_Block_2()
{
    printf("Static block Animal 2\n");
}

void Animal_Anonymous_Block_1()
{
    printf("Instance initialization block Animal\n");
}

void Animal_Constructor_1(Animal_t *this)
{
    Animal_Anonymous_Block_1();
    
    this->ID = 0;
    this->num_legs = 5;
    this->num_masters = 1;

    printf("Animal Ctor\n");
    this->ID = ++g_animal_counter;
    ((void (*)(Animal_t *))this->object_t.class->vtable[SAYHELLO])(this);
    Animal_showCounter();
    printf("%s\n", ((char *(*)(Animal_t *))this->object_t.class->vtable[TOSTRING])(this));
    printf("%s\n", Object_toString((object_t *)this));
}

void Animal_Constructor_2(Animal_t *this, int num_masters)
{
    Animal_Anonymous_Block_1();
    
    this->ID = 0;
    this->num_legs = 5;
    this->num_masters = 1;

    printf("Animal Ctor int\n");
    this->ID = ++g_animal_counter;
    this->num_masters = num_masters;
}

void Animal_sayHello(Animal_t *this)
{
    printf("Animal Hello!\n");
    printf("I have %d legs\n", this->num_legs);
}

void Animal_showCounter()
{
    printf("%d\n", g_animal_counter);
}

int Animal_getNumMasters(Animal_t *this)
{
    return this->num_masters;
}

char *Animal_toString(Animal_t * this)
{
    sprintf(g_toString_output, "Animal with ID: %d", this->ID);
    return g_toString_output;
}
/******************************************************************************/

/******************************************************************************/
/*                          Dog Functions Definition                          */
/******************************************************************************/

class_t *Dog_ClassLoader(class_t *super)
{
    class_t *dog_class = NULL;
    method_t *dog_functions = NULL;

    dog_class = (class_t *)malloc(sizeof(class_t));
    if(NULL == dog_class)
    {
        perror("Malloc in Dog_ClassLoader dog_class failed");
        return NULL;
    }

    dog_functions = (method_t *)malloc(sizeof(method_t) * 6);
    if(NULL == dog_functions)
    {
        free(dog_class);
        perror("Malloc in Dog_ClassLoader dog_functions failed");
        return NULL;
    }

    dog_class->className = "Dog";
    dog_class->size = sizeof(Dog_t);
    dog_class->super = super;
    dog_class->vtable = dog_functions;

    dog_functions[HASHCODE] = (method_t)Object_hashCode;
    dog_functions[TOSTRING] = (method_t)Dog_toString;
    dog_functions[EQUALS] = (method_t)Object_equals;
    dog_functions[GETCLASS] = (method_t)Object_getClass;
    dog_functions[SAYHELLO] = (method_t)Dog_sayHello;
    dog_functions[GETNUMMASTERS] = (method_t)Animal_getNumMasters;

    Dog_Static_Block_1();

    return dog_class;
}

void Dog_Static_Block_1()
{
    printf("Static block Dog\n");
}

void Dog_Anonymous_Block_1()
{
    printf("Instance initialization block Dog\n");
}

void Dog_Constructor(Dog_t *this)
{
    Animal_Constructor_2(&this->animal, 2);

    Dog_Anonymous_Block_1();
    this->num_legs = 4;
    printf("Dog Ctor\n");
}

void Dog_sayHello(Dog_t *this)
{
    printf("Dog Hello!\n");
    printf("I have %d legs\n", this->num_legs);
}

char *Dog_toString(Dog_t *this)
{
    sprintf(g_toString_output, "Dog with ID: %d", this->animal.ID);
    return g_toString_output;
}
/******************************************************************************/

/******************************************************************************/
/*                          Cat Functions Definition                          */
/******************************************************************************/

class_t *Cat_ClassLoader(class_t *super)
{
    class_t *cat_class = NULL;
    method_t *cat_functions = NULL;

    cat_class = (class_t *)malloc(sizeof(class_t));
    if(NULL == cat_class)
    {
        perror("Malloc in Cat_ClassLoader cat_class failed");
        return NULL;
    }

    cat_functions = (method_t *)malloc(sizeof(method_t) * 6);
    if(NULL == cat_functions)
    {
        free(cat_class);
        perror("Malloc in Cat_ClassLoader cat_functions failed");
        return NULL;
    }

    cat_class->className = "Cat";
    cat_class->size = sizeof(Cat_t);
    cat_class->super = super;
    cat_class->vtable = cat_functions;

    cat_functions[HASHCODE] = (method_t)Object_hashCode;
    cat_functions[TOSTRING] = (method_t)Cat_toString;
    cat_functions[EQUALS] = (method_t)Object_equals;
    cat_functions[GETCLASS] = (method_t)Object_getClass;
    cat_functions[SAYHELLO] = (method_t)Animal_sayHello;
    cat_functions[GETNUMMASTERS] = (method_t)Animal_getNumMasters;

    Cat_Static_Block_1();

    return cat_class;
}

void Cat_Static_Block_1()
{
    printf("Static block Cat\n");
}

void Cat_Constructor_1(Cat_t *this)
{
    Cat_Constructor_2(this, "black");
    printf("Cat Ctor\n");
    this->num_masters = 2;
}

void Cat_Constructor_2(Cat_t *this, char *colors)
{
    Animal_Constructor_1(&this->animal);
    this->colors = colors;
    this->num_masters = 5;
    printf("Cat Ctor with color: %s\n", this->colors);
}

char *Cat_toString(Cat_t *this)
{
    sprintf(g_toString_output, "Cat with ID: %d", this->animal.ID);
    return g_toString_output;
}
/******************************************************************************/

/******************************************************************************/
/*                     LegendaryAnimal Functions Definition                   */
/******************************************************************************/

class_t *LegendaryAnimal_ClassLoader(class_t *super)
{
    class_t *legendary_class = NULL;
    method_t *legendary_method = NULL;

    legendary_class = (class_t *)malloc(sizeof(class_t));
    if(NULL == legendary_class)
    {
        perror("Malloc in LegendaryAnimal_ClassLoader legendary_class failed");
        return NULL;
    }

    legendary_method = (method_t *)malloc(sizeof(method_t) * 6);
    if(NULL == legendary_method)
    {
        free(legendary_class);
        perror("Malloc in LegendaryAnimal_ClassLoader legendary_method failed");
        return NULL;
    }

    legendary_class->className = "LegendaryAnimal";
    legendary_class->size = sizeof(LegendaryAnimal_t);
    legendary_class->super = super;
    legendary_class->vtable = legendary_method;

    legendary_method[HASHCODE] = (method_t)Object_hashCode;
    legendary_method[EQUALS] = (method_t)Object_equals;
    legendary_method[GETCLASS] = (method_t)Object_getClass;
    legendary_method[SAYHELLO] = (method_t)LegendaryAnimal_sayHello;
    legendary_method[TOSTRING] = (method_t)LegendaryAnimal_toString;
    legendary_method[GETNUMMASTERS] = (method_t)Animal_getNumMasters;

    LegendaryAnimal_Static_Block_1();

    return legendary_class;
}

void LegendaryAnimal_Static_Block_1()
{
    printf("Static block Legendary Animal\n");
}
void LegendaryAnimal_Constructor_1(LegendaryAnimal_t *this)
{
    Cat_Constructor_1(&this->cat);
    printf("Legendary Ctor\n");
}

void LegendaryAnimal_sayHello(LegendaryAnimal_t *this)
{
    (void)this;
    printf("Legendary Hello!\n");
}

char *LegendaryAnimal_toString(LegendaryAnimal_t *this)
{
    sprintf(g_toString_output, "LegendaryAnimal with ID: %d", this->cat.animal.ID);
    return g_toString_output;
}
/******************************************************************************/

/******************************************************************************/
/*                              main function                                 */
/******************************************************************************/
int main()
{
    int i = 0;

    class_t *object_class = NULL;
    class_t *animal_class = NULL;
    class_t *dog_class = NULL;
    class_t *cat_class = NULL;
    class_t *legendary_class = NULL;

    Animal_t *animal = NULL;
    Dog_t *dog = NULL;
    Cat_t *cat = NULL;
    LegendaryAnimal_t *legendary_animal = NULL;

    Animal_t *Animal[5] = {NULL};

    object_class = Object_ClassLoader();

    animal_class = Animal_ClassLoader(object_class);
    animal = (Animal_t *)CreateInstance(animal_class);
    Animal_Constructor_1(animal);

    dog_class = Dog_ClassLoader(animal_class);
    dog = (Dog_t *)CreateInstance(dog_class);
    Dog_Constructor(dog);

    cat_class = Cat_ClassLoader(animal_class);
    cat = (Cat_t * )CreateInstance(cat_class);
    Cat_Constructor_1(cat);

    legendary_class = LegendaryAnimal_ClassLoader(cat_class);
    legendary_animal = (LegendaryAnimal_t *)CreateInstance(legendary_class);
    LegendaryAnimal_Constructor_1(legendary_animal);

    Animal_showCounter();

    printf("%d\n", animal->ID);
    printf("%d\n", dog->animal.ID);
    printf("%d\n", cat->animal.ID);
    printf("%d\n", legendary_animal->cat.animal.ID);

    Animal[0] = (Animal_t *)CreateInstance(dog_class);
    Dog_Constructor((Dog_t *)Animal[0]);
    Animal[1] = (Animal_t *)CreateInstance(cat_class);
    Cat_Constructor_1((Cat_t * )Animal[1]);
    Animal[2] = (Animal_t *)CreateInstance(cat_class);
    Cat_Constructor_2((Cat_t *)Animal[2], "white");
    Animal[3] = (Animal_t *)CreateInstance(legendary_class);
    LegendaryAnimal_Constructor_1((LegendaryAnimal_t * )Animal[3]);
    Animal[4] = (Animal_t *)CreateInstance(animal_class);
    Animal_Constructor_1((Animal_t *)Animal[4]);

    for (i = 0; i < 5; ++i)
    {
        ((void (*)(Animal_t *))Animal[i]->object_t.class->vtable[SAYHELLO])(Animal[i]);
        printf("%d\n", 
            ((int (*)(Animal_t *))Animal[i]->object_t.class->vtable[GETNUMMASTERS])(Animal[i]));
    }
    
    for (i = 0; i < 5; ++i)
    {
        foo(Animal[i]);
    }

    for(i = 0; i < 5; ++i)
    {
        free(Animal[i]);
    }

    free(legendary_class->vtable);
    free(legendary_class);
    free(legendary_animal);
    
    free(cat_class->vtable);
    free(cat_class);
    free(cat);

    free(dog_class->vtable);
    free(dog_class);
    free(dog);

    free(animal_class->vtable);
    free(animal_class);
    free(animal);

    free(object_class->vtable);
    free(object_class);

    return 0;
}
/******************************************************************************/
