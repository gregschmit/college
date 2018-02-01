/*
 * homework4.h
 *
 *  Created on: Feb 8, 2017
 *      Author: zzhang
 */

#ifndef HOMEWORK5_H_
#define HOMEWORK5_H_

#include <stdint.h>

// Convert the endian type of a memory word, written in C
extern void convert1(uint32_t *pWord);

// Convert the endian type of a memory word, written in assembly, no REV instruction
extern void convert2(uint32_t *pWord);

// Convert the endian type of a memory word, written in assembly, using REV instruction
extern void convert3(uint32_t *pWord);

#endif /* HOMEWORK5_H_ */
