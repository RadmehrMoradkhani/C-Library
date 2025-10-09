/**
 * @file    edge_detector.c
 * @author  Radmehr Moradkhani
 * @version 1.0
 * @date    2025-10-09
 * @brief   Implementation of advanced edge detection library.
 * @license MIT
 *
 * @details
 * Provides functions for detecting transitions between
 * consecutive binary signal states (rising, falling, both).
 * This version includes internal counters and optional callback.
 */

#include "edge_detector.h"

/**
 * @brief Normalize any value to strictly 0 or 1.
 * @param x Raw input value.
 * @return 0 if x==0, otherwise 1.
 */
static inline uint8_t norm01(uint8_t x)
{
    return (x != 0u) ? 1u : 0u;
}

void edge_init(EdgeDetector *det, uint8_t initial_state)
{
    if (!det) return;
    det->prev = norm01(initial_state);
    det->rise_count = 0u;
    det->fall_count = 0u;
    det->on_edge = 0; /* No callback by default */
}

/**
 * @brief Safely calls user callback if assigned.
 */
static inline void _edge_invoke_callback(EdgeDetector *det, EdgeType type)
{
    if (det && det->on_edge)
        det->on_edge(type);
}

EdgeType edge_update(EdgeDetector *det, uint8_t input)
{
    if (!det) return EDGE_NONE;

    uint8_t current = norm01(input);
    EdgeType detected = EDGE_NONE;

    if ((det->prev == 0u) && (current == 1u)) {
        detected = EDGE_RISING;
        det->rise_count++;
        _edge_invoke_callback(det, EDGE_RISING);
    }
    else if ((det->prev == 1u) && (current == 0u)) {
        detected = EDGE_FALLING;
        det->fall_count++;
        _edge_invoke_callback(det, EDGE_FALLING);
    }

    det->prev = current;
    return detected;
}

uint8_t edge_both(EdgeDetector *det, uint8_t input)
{
    if (!det) return 0u;

    EdgeType type = edge_update(det, input);
    return (type != EDGE_NONE) ? 1u : 0u;
}

void edge_reset(EdgeDetector *det)
{
    if (!det) return;
    det->rise_count = 0u;
    det->fall_count = 0u;
}

uint32_t edge_get_rise_count(const EdgeDetector *det)
{
    if (!det) return 0u;
    return det->rise_count;
}

uint32_t edge_get_fall_count(const EdgeDetector *det)
{
    if (!det) return 0u;
    return det->fall_count;
}
