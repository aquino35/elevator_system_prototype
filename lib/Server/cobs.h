
/* 
 *  This script dedicated for the COBS method of encoding/decoding messages.
 *  Source: https://github.com/jacquesf/COBS-Consistent-Overhead-Byte-Stuffing
 *  Copyright 2011, Jacques Fortier. All rights reserved.
 *
 */

#ifndef COBS_H
#define COBS_H

#include <stdint.h>
#include <stddef.h>

size_t cobs_encode(const uint8_t * input, size_t length, uint8_t * output);
size_t cobs_decode(const uint8_t * input, size_t length, uint8_t * output);

#endif