/**
 * @file debounce.c
 * @brief Implementation of an optimized, multi-instance debounce algorithm.
 */

#include "debounce.h"

/**
 * @brief Initializes a Debounce instance.
 *
 * @param d Pointer to the Debounce structure.
 * @param time_ref Pointer to the user-defined time reference function.
 */
void debounce_init(Debounce *d, uint8_t (*time_ref)(void))
{
    if (!d) return;
    d->prev_input    = 0;
    d->stable_output = 0;
    d->time_ref      = time_ref;
}

/**
 * @brief Updates the debounce logic for a single digital signal.
 *
 * @param d Pointer to the Debounce instance.
 * @param input Raw digital input (0 or 1).
 * @return uint8_t The debounced output (stable signal).
 *
 * @note
 * The user’s time_ref() function defines how long the signal must remain
 * stable before being accepted. It should return 1 when the configured
 * offset time has elapsed.
 */
uint8_t debounce_update(Debounce *d, uint8_t input)
{
    if (!d) return 0;

    input = (input != 0); // Normalize input to 0 or 1

    // If input value has changed, store but do not confirm yet
    if (input != d->prev_input) {
        d->prev_input = input;
        if (d->time_ref) d->time_ref(); // User may reset timer inside
        return d->stable_output;
    }

    // If input remains stable, check if enough time has passed
    if (d->time_ref && d->time_ref()) {
        d->stable_output = input;
    }

    return d->stable_output;
}
