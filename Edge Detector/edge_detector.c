/*
 * File:    edge_detector.c
 * Brief:   Implementation of edge detection library.
 * License: MIT
 */

#include "edge_detector.h"

static inline uint8_t norm01(uint8_t x)
{
    return (x != 0u) ? 1u : 0u;
}

void edge_init(EdgeDetector *det, uint8_t initial_state) {
    if (!det) return;
    det->prev = norm01(initial_state);
}

uint8_t edge_rise(EdgeDetector *det, uint8_t in) {
    if (!det) return 0u;
    uint8_t current  = norm01(in);
    uint8_t detected = (uint8_t)(current && (det->prev == 0u));
    det->prev = current;
    return detected;
}

uint8_t edge_fall(EdgeDetector *det, uint8_t in) {
    if (!det) return 0u;
    uint8_t current  = norm01(in);
    uint8_t detected = (uint8_t)((det->prev == 1u) && (current == 0u));
    det->prev = current;
    return detected;
}

uint8_t edge_both(EdgeDetector *det, uint8_t in) {
    if (!det) return 0u;
    uint8_t current  = norm01(in);
    uint8_t detected = (uint8_t)(current != det->prev);
    det->prev = current;
    return detected;
}
