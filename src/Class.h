
#ifndef CLASS_HEADER
#define CLASS_HEADER




/**
 * Common class methods
 */
typedef struct
{
    /**
    * Allocates a new instance and returns it
    *
    * @param className - the name of the class to allocate
    * @param blockSize - the size of the class to allocate
    *
    * @return - the allocated instance, or NULL if allocation failed
    */
    void * (* constructor)(char const * const className, unsigned int blockSize);

    /**
    * Deletes the instance and sets it to NULL
    *
    * @param this - pointer to the instance to destructor
    */
    void (* destructor)(void ** this);

} ClassMethods;




/**
 * Class methods table
 */
extern ClassMethods const * const Class;




#endif /* CLASS_HEADER */
