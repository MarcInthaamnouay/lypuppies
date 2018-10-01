//
//  dog.c
//  lypuppies
//
//  Created by Marc Intha on 01/10/2018.
//  Copyright © 2018 Marc Intha. All rights reserved.
//

#include <stdlib.h>
#include "util.h"
#include "dog.h"

Dog * generateUniquePuppy(char * name, Type t) {
    if (!name) {
        return NULL;
    }
    
    char * alias = malloc(sizeof(char) * 5);
    // generate the alias
    generateRandomName(alias, 5);
    // create the dog
    Dog * dog = malloc(sizeof(Dog));
    
    if (dog == NULL) {
        return NULL;
    }
    
    dog->age = 1;
    dog->name = name;
    dog->type = t;
    dog->alias = alias;
    
    return dog;
}

void puppyBark(Dog * dog) {
    if (dog == NULL) {
        printf("Wouaf Wouaf I don't have a name !");
    }
    
    printf("Wouaf Wouaf I am %s and I am %i", dog->name, dog->age);
}

uint8_t getDogLifeMedianExpectancy(Dog * dog) {
    if (dog == NULL) {
        return 0;
    }
    
    switch (dog->type) {
        case chihuaha:
            return 15;
        case chienLoup:
            return 14;
        default:
            return 14;
    }
}


uint8_t freePuppy(Dog * dog) {
    if (dog == NULL) {
        return 0;
    }
    
    dog = NULL;
    free(dog);
    return 1;
}
