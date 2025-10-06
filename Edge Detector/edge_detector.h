/*
 * File:    edge_detector.h
 * Brief:   Edge detection library (rising / falling / both) with per-signal state.
 * Author:  Radmehr Moradkhani
 * License: MIT
 */

#ifndef EDGE_DETECTOR_H
#define EDGE_DETECTOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/* Opaque-ish state holder for one digital signal */
typedef struct {
    uint8_t prev;   /* previous normalized state (0 or 1) */
} EdgeDetector;

/* Initialize or re-initialize detector state.
 * initial_state is treated as boolean: 0 -> 0, otherwise -> 1.
 */
void edge_init(EdgeDetector *det, uint8_t initial_state);

/* Detect a rising edge: returns 1 if transition 0 -> 1 occurred, otherwise 0. */
uint8_t edge_rise(EdgeDetector *det, uint8_t in);

/* Detect a falling edge: returns 1 if transition 1 -> 0 occurred, otherwise 0. */
uint8_t edge_fall(EdgeDetector *det, uint8_t in);

/* Detect any edge: returns 1 if state changed (0 <-> 1), otherwise 0. */
uint8_t edge_both(EdgeDetector *det, uint8_t in);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* EDGE_DETECTOR_H */
