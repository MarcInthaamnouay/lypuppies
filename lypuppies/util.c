//
//  util.c
//  lypuppies
//
//  Created by Marc Intha on 01/10/2018.
//  Copyright © 2018 Marc Intha. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "dog.h"
#include "util.h"

void generateRandomName(char * s, uint8_t len) {
    const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    printf("%lu", sizeof(alphanum));
    for (uint8_t i = 0; i < len; i++) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    s[len] = 0;
}

Type getTypeFromStr(char * t) {
    if (strcasecmp(t, "chienLoup")) {
        return chienLoup;
    }
    
    return chihuaha;
}

char * getStrTypeFromType(Type t) {
    switch (t) {
        case chihuaha:
            return "chihuahua";
            break;
        case chienLoup:
            return "chienLoup";
            break;
        default:
            return "chienLoup";
    }
}
