//
//  dog.h
//  lypuppies
//
//  Created by Marc Intha on 01/10/2018.
//  Copyright © 2018 Marc Intha. All rights reserved.
//

#ifndef dog_h
#define dog_h

#include <stdio.h>

/**
 * @brief enum which define the type of dog that we're supporting
 */
typedef enum Type {
    chihuaha,
    dogWolf
} Type;

/**
 * @brief structure of the dog
 */
typedef struct Dog {
    char * name;
    char * alias;
    Type type;
    uint8_t age;
} Dog;

/**
 * @brief generate Unique Puppy generate a puppy based on it's type
 * @param name char array name of the puppy
 * @param t Type of the dog
 * @return return an Unique Puppy
 */
Dog * generateUniquePuppy(char * name, Type t);

/**
 * @brief a puppy will bark something
 */
void puppyBark(Dog * dog);

/**
 * @brief get the median life remaining of the dog based on it's type
 * @param dog pointer Dog
 */
uint8_t getDogLifeMedianExpectancy(Dog * dog);

/**
 * @brief free Puppy desallocate the dog
 * @param dog Dog pointer
 */
uint8_t freePuppy(Dog * dog);

#endif /* dog_h */
