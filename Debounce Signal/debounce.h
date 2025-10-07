/**
 * @file debounce.h
 * @author Radmehr
 * @brief Hardware-independent, multi-instance software debounce library (v1.1)
 * @version 1.1
 * @date 2025-10-07
 *
 * @details
 * This version improves startup behavior, adds safe fallback for null time references,
 * and ensures clean timing control separation between the debounce logic
 * and user-defined timing mechanisms.
 */

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct Debounce
 * @brief Represents one independent debounced signal instance.
 *
 * @var Debounce::prev_input
 *      Last observed raw input (0 or 1).
 *
 * @var Debounce::stable_output
 *      Last confirmed stable (debounced) output value.
 *
 * @var Debounce::time_ref
 *      Pointer to the user-defined timing function.
 *      Returns 0 while waiting and 1 when the configured offset time has elapsed.
 */
typedef struct {
    uint8_t prev_input;
    uint8_t stable_output;
    uint8_t (*time_ref)(void);
} Debounce;

/**
 * @brief Initializes a Debounce instance and synchronizes it with the initial input.
 *
 * @param d Pointer to the Debounce structure.
 * @param time_ref Pointer to the user's time reference function.
 * @param initial_input The current raw input signal (0 or 1) for synchronization.
 */
void debounce_init(Debounce *d, uint8_t (*time_ref)(void), uint8_t initial_input);

/**
 * @brief Processes a single debounce step for a digital input.
 *
 * @param d Pointer to the Debounce instance.
 * @param input Raw digital signal (0 or 1).
 * @return uint8_t Debounced (stable) signal.
 *
 * @details
 * - If the input changes, the module starts waiting for the stable period.
 * - The stable period is defined by the user's time_ref() function.
 * - If no time_ref() is provided (NULL), changes are accepted immediately.
 */
uint8_t debounce_update(Debounce *d, uint8_t input);

#ifdef __cplusplus
}
#endif

#endif /* DEBOUNCE_H_ */
