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

typedef void (*method_t)();

static char g_toString_output[100];
static int g_animal_counter = 0;

enum FUNCTIONS{HASHCODE = 0, 
                TOSTRING,
                EQUALS,
                GETCLASS,
                SAYHELLO,
                GETNUMMASTERS,
                FINALIZE};

typedef struct class
{
    char *className;
    struct class *super;
    size_t size;
    method_t *vtable;
} class_t;

typedef struct 
{
    class_t *class;
} object_t;

typedef struct 
{
    object_t object;
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


class_t *object_class = NULL;
class_t *animal_class = NULL;
class_t *dog_class = NULL;
class_t *cat_class = NULL;
class_t *legendary_class = NULL;

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
void Object_finalize(object_t *this);
/******************************************************************************/

/******************************************************************************/
/*                          Animal Functions Declaration                      */
/******************************************************************************/

class_t *Animal_ClassLoader();

void Animal_Static_Block_1();
void Animal_Static_Block_2();
void Animal_Anonymous_Block_1();
void Animal_Constructor_1(Animal_t *this);
void Animal_Constructor_2(Animal_t *this, int num_masters);
void Animal_sayHello(Animal_t *this);
void Animal_showCounter();
int Animal_getNumMasters(Animal_t *this);
char *Animal_toString(Animal_t *this);
void Animal_finalize(Animal_t *this);
/******************************************************************************/

/******************************************************************************/
/*                          Dog Functions Declaration                         */
/******************************************************************************/

class_t *Dog_ClassLoader();

void Dog_Static_Block_1();
void Dog_Anonymous_Block_1();
void Dog_Constructor(Dog_t *this);
void Dog_sayHello(Dog_t *this);
char *Dog_toString(Dog_t *this);
void Dog_finalize(Dog_t *this);
/******************************************************************************/

/******************************************************************************/
/*                          Cat Functions Declaration                         */
/******************************************************************************/

class_t *Cat_ClassLoader();

void Cat_Static_Block_1();
void Cat_Constructor_1(Cat_t *this);
void Cat_Constructor_2(Cat_t *this, char *colors);
char *Cat_toString(Cat_t *this);
void Cat_finalize(Cat_t *this);
/******************************************************************************/

/******************************************************************************/
/*                   LegendaryAnimal Functions Declaration                    */
/******************************************************************************/

class_t *LegendaryAnimal_ClassLoader();

void LegendaryAnimal_Static_Block_1();
void LegendaryAnimal_Constructor_1(LegendaryAnimal_t *this);
void LegendaryAnimal_sayHello(LegendaryAnimal_t *this);
char *LegendaryAnimal_toString(LegendaryAnimal_t *this);
void LegendaryAnimal_finalize(LegendaryAnimal_t *this);
/******************************************************************************/

/******************************************************************************/
/*                                  VTables                                   */
/******************************************************************************/

method_t object_functions[] = {(method_t)Object_hashCode,
                                (method_t)Object_toString,
                                (method_t)Object_equals,
                                (method_t)Object_getClass,
                                (method_t)Object_finalize};

method_t animal_functions[] = {(method_t)Object_hashCode,
                                (method_t)Animal_toString,
                                (method_t)Object_equals,
                                (method_t)Object_getClass,
                                (method_t)Animal_sayHello,
                                (method_t)Animal_getNumMasters,
                                (method_t)Animal_finalize};


method_t dog_functions[] = {(method_t)Object_hashCode,
                                (method_t)Dog_toString,
                                (method_t)Object_equals,
                                (method_t)Object_getClass,
                                (method_t)Dog_sayHello,
                                (method_t)Animal_getNumMasters,
                                (method_t)Dog_finalize};

method_t cat_functions[] = {(method_t)Object_hashCode,
                                (method_t)Cat_toString,
                                (method_t)Object_equals,
                                (method_t)Object_getClass,
                                (method_t)Animal_sayHello,
                                (method_t)Animal_getNumMasters,
                                (method_t)Cat_finalize};

method_t legendary_functions[] = {(method_t)Object_hashCode,
                                (method_t)LegendaryAnimal_toString,
                                (method_t)Object_equals,
                                (method_t)Object_getClass,
                                (method_t)LegendaryAnimal_sayHello,
                                (method_t)Animal_getNumMasters,
                                (method_t)LegendaryAnimal_finalize};
/******************************************************************************/

/******************************************************************************/
/*                          Object Functions Definition                       */
/******************************************************************************/

void foo(Animal_t *a)
{
    printf("%s\n", ((char *(*)(Animal_t *))a->object.class->vtable[TOSTRING])(a));
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
    object_class = (class_t *)malloc(sizeof(class_t));
    if(NULL == object_class)
    {
        perror("Malloc in ObjectClassLoader class_t failed");
        return NULL;
    }

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

void Object_finalize(object_t *this)
{
    (void)this;
}
/******************************************************************************/

/******************************************************************************/
/*                          Animal Functions Definition                       */
/******************************************************************************/

class_t *Animal_ClassLoader()
{
    animal_class = (class_t *)malloc(sizeof(class_t));
    if(NULL == animal_class)
    {
        perror("Malloc in ObjectClAnimal_ClassLoader animal_class failed");
        return NULL;
    }

    animal_class->className = "Animal";
    animal_class->size = sizeof(Animal_t);
    animal_class->super = object_class;
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
    ((void (*)(Animal_t *))this->object.class->vtable[SAYHELLO])(this);
    Animal_showCounter();
    printf("%s\n", ((char *(*)(Animal_t *))this->object.class->vtable[TOSTRING])(this));
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

void Animal_finalize(Animal_t *this)
{
    printf("finalize Animal with ID: %d\n", this->ID);
    Object_finalize((object_t *)this);
}
/******************************************************************************/

/******************************************************************************/
/*                          Dog Functions Definition                          */
/******************************************************************************/

class_t *Dog_ClassLoader()
{
    dog_class = (class_t *)malloc(sizeof(class_t));
    if(NULL == dog_class)
    {
        perror("Malloc in Dog_ClassLoader dog_class failed");
        return NULL;
    }

    dog_class->className = "Dog";
    dog_class->size = sizeof(Dog_t);
    dog_class->super = animal_class;
    dog_class->vtable = dog_functions;

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

void Dog_finalize(Dog_t *this)
{
    printf("finalize Dog with ID: %d\n", this->animal.ID);
    Animal_finalize((Animal_t *)this);
}
/******************************************************************************/

/******************************************************************************/
/*                          Cat Functions Definition                          */
/******************************************************************************/

class_t *Cat_ClassLoader()
{
    cat_class = (class_t *)malloc(sizeof(class_t));
    if(NULL == cat_class)
    {
        perror("Malloc in Cat_ClassLoader cat_class failed");
        return NULL;
    }

    cat_class->className = "Cat";
    cat_class->size = sizeof(Cat_t);
    cat_class->super = animal_class;
    cat_class->vtable = cat_functions;

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

void Cat_finalize(Cat_t *this)
{
    printf("finalize Cat with ID: %d\n", this->animal.ID);
    Animal_finalize((Animal_t *)this);
}
/******************************************************************************/

/******************************************************************************/
/*                     LegendaryAnimal Functions Definition                   */
/******************************************************************************/

class_t *LegendaryAnimal_ClassLoader()
{
    legendary_class = (class_t *)malloc(sizeof(class_t));
    if(NULL == legendary_class)
    {
        perror("Malloc in LegendaryAnimal_ClassLoader legendary_class failed");
        return NULL;
    }

    legendary_class->className = "LegendaryAnimal";
    legendary_class->size = sizeof(LegendaryAnimal_t);
    legendary_class->super = cat_class;
    legendary_class->vtable = legendary_functions;

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

void LegendaryAnimal_finalize(LegendaryAnimal_t *this)
{
    printf("finalize LegendaryAnimal with ID: %d\n", this->cat.animal.ID);
    Cat_finalize((Cat_t *)this);
}
/******************************************************************************/

/******************************************************************************/
/*                              main function                                 */
/******************************************************************************/
int main()
{
    int i = 0;

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
        ((void (*)(Animal_t *))Animal[i]->object.class->vtable[SAYHELLO])(Animal[i]);
        printf("%d\n", 
            ((int (*)(Animal_t *))Animal[i]->object.class->vtable[GETNUMMASTERS])(Animal[i]));
    }
    
    for (i = 0; i < 5; ++i)
    {
        foo(Animal[i]);
    }

    printf("After gc\n");
    for(i = 4; i >= 0; --i)
    {
        ((void (*)(Animal_t *))Animal[i]->object.class->vtable[FINALIZE])(Animal[i]);
        free(Animal[i]);
    }
    
    ((void (*)(LegendaryAnimal_t *))legendary_animal->cat.animal.object.class->vtable[FINALIZE])(legendary_animal);
    ((void (*)(Cat_t *))cat->animal.object.class->vtable[FINALIZE])(cat);
    ((void (*)(Dog_t *))dog->animal.object.class->vtable[FINALIZE])(dog);
    ((void (*)(Animal_t *))animal->object.class->vtable[FINALIZE])(animal);

    free(object_class);
    free(animal);
    free(animal_class);
    free(dog);
    free(dog_class);
    free(cat);
    free(cat_class);
    free(legendary_animal);
    free(legendary_class);

    return 0;
}
/******************************************************************************/
