/**
 * @file debounce.c
 * @brief Implementation of a robust, multi-instance debounce algorithm (v1.1)
 */

#include "debounce.h"

void debounce_init(Debounce *d, uint8_t (*time_ref)(void), uint8_t initial_input)
{
    if (!d) return;
    d->prev_input    = (initial_input != 0);
    d->stable_output = d->prev_input;
    d->time_ref      = time_ref;
}

/**
 * @brief Internal helper: checks time_ref safely.
 * If time_ref is NULL, always returns 1 (immediate acceptance).
 */
static inline uint8_t _debounce_time_ready(Debounce *d)
{
    if (!d->time_ref) return 1;
    return d->time_ref();
}

uint8_t debounce_update(Debounce *d, uint8_t input)
{
    if (!d) return 0;
    input = (input != 0); // Normalize input to 0/1

    // Detect change in input
    if (input != d->prev_input) {
        d->prev_input = input;
        // If a time function exists, user can reset timer externally here
        _debounce_time_ready(d); // harmless call for user-defined reset handling
        return d->stable_output; // Not yet confirmed
    }

    // Input unchanged → check timing
    if (_debounce_time_ready(d)) {
        d->stable_output = input;
    }

    return d->stable_output;
}
