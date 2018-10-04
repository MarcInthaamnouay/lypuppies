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
 * @param name char *
 * @param age uint8_t
 */
void puppyBark(char * name, uint8_t age);

/**
 * @brief get the median life remaining of the dog based on it's type
 * @param t Type
 * @return uint8_t
 */
uint8_t getDogLifeMedianExpectancy(Type t);

/**
 * @brief free Puppy desallocate the dog
 * @param dog Dog pointer
 */
uint8_t freePuppy(Dog * dog);

#endif /* dog_h */
