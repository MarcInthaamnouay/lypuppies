//
//  main.c
//  lypuppies
//
//  Created by Marc Intha on 01/10/2018.
//  Copyright © 2018 Marc Intha. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "dog.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    Dog * dog = generateUniquePuppy("Haaa", chihuaha);
    puppyBark(dog);
    uint8_t age = getDogLifeMedianExpectancy(dog);
    printf("This dog expectancy life should be %i \n", age);
    return 0;
}


