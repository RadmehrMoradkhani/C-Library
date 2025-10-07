/**
 * @file debounce.h
 * @author Radmehr
 * @brief Optimized, hardware-independent, multi-instance debounce library.
 * @version 1.0
 * @date 2025-10-07
 *
 * @details
 * This module provides a simple and efficient software debounce mechanism
 * that can handle multiple independent digital signals.
 * Each Debounce instance contains its own timing reference function
 * (provided by the user) to define how long a signal must remain stable
 * before it is accepted as valid.
 */

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct Debounce
 * @brief Holds the state and timing reference for one debounced signal.
 *
 * @var Debounce::prev_input
 *      Last raw input value (0 or 1).
 *
 * @var Debounce::stable_output
 *      Last confirmed stable (debounced) output.
 *
 * @var Debounce::time_ref
 *      Pointer to the user-defined timing function.
 *      The function should return 0 while the signal is unstable,
 *      and 1 once the configured offset/stability time has elapsed.
 */
typedef struct {
    uint8_t prev_input;
    uint8_t stable_output;
    uint8_t (*time_ref)(void);
} Debounce;

/**
 * @brief Initializes a Debounce instance.
 *
 * @param d Pointer to the Debounce instance.
 * @param time_ref Pointer to a user-defined timing function.
 *                 Can be NULL if not assigned yet.
 *
 * @note
 * This function must be called once before using debounce_update().
 */
void debounce_init(Debounce *d, uint8_t (*time_ref)(void));

/**
 * @brief Processes a single debounce step for the given input.
 *
 * @param d Pointer to the Debounce instance.
 * @param input Raw digital input (0 or 1).
 * @return uint8_t The debounced (stable) output.
 *
 * @details
 * - If the input changes, it stores the new value but waits until
 *   the timing function indicates stability.
 * - Once the time_ref() function returns 1, the new input is accepted
 *   as a stable output.
 */
uint8_t debounce_update(Debounce *d, uint8_t input);

#ifdef __cplusplus
}
#endif

#endif /* DEBOUNCE_H_ */
