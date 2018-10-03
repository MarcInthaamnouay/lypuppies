//
//  util.h
//  lypuppies
//
//  Created by Marc Intha on 01/10/2018.
//  Copyright © 2018 Marc Intha. All rights reserved.
//

#ifndef util_h
#define util_h

#include <stdio.h>
#include "dog.h"

/**
 * @brief Generate Random Name
 * @param s char
 * @param len uint8_t
 */
void generateRandomName(char * s, uint8_t len);

/**
 * @brief Get Type From String
 * @param type char
 * @return t Type
 */
Type getTypeFromStr(char * type);

/**
 * @brief get Str Type From Type
 * @param t Type
 * @return char
 */
char * getStrTypeFromType(Type t);

#endif /* util_h */
