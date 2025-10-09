/**
 * @file    edge_detector.h
 * @author  Radmehr Moradkhani
 * @version 1.0
 * @date    2025-10-09
 * @brief   Advanced and documented edge detection library.
 * @license MIT
 *
 * @details
 * This library provides fast and hardware-independent detection
 * of signal transitions (rising, falling, or both).  
 * Each signal uses its own EdgeDetector structure to store state.
 *
 * Typical usage:
 * @code
 * EdgeDetector sig;
 * edge_init(&sig, 0);
 * while (1) {
 *     uint8_t input = read_pin();
 *     EdgeType e = edge_update(&sig, input);
 *     if (e == EDGE_RISING) { ... }
 * }
 * @endcode
 */

#ifndef EDGE_DETECTOR_H
#define EDGE_DETECTOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum EdgeType
 * @brief Enumerates detected edge types.
 */
typedef enum {
    EDGE_NONE = 0,   /**< No edge detected */
    EDGE_RISING,     /**< 0 → 1 transition */
    EDGE_FALLING,    /**< 1 → 0 transition */
    EDGE_BOTH        /**< Any change (0 ↔ 1) */
} EdgeType;

/**
 * @struct EdgeDetector
 * @brief Maintains state and statistics for one binary signal.
 *
 * @var EdgeDetector::prev
 *      Previous normalized input (0 or 1).
 * @var EdgeDetector::rise_count
 *      Total number of rising edges detected.
 * @var EdgeDetector::fall_count
 *      Total number of falling edges detected.
 * @var EdgeDetector::on_edge
 *      Optional user callback triggered on edge events.
 */
typedef struct {
    uint8_t prev;           /**< Previous normalized input (0 or 1). */
    uint32_t rise_count;    /**< Counter for rising edges. */
    uint32_t fall_count;    /**< Counter for falling edges. */
    void (*on_edge)(EdgeType type); /**< Optional callback function pointer. */
} EdgeDetector;

/**
 * @brief Initializes or re-initializes the detector.
 * @param det Pointer to the EdgeDetector instance.
 * @param initial_state Initial signal state (0 or 1).
 * @note Must be called before using `edge_update()`.
 */
void edge_init(EdgeDetector *det, uint8_t initial_state);

/**
 * @brief Updates detector state and returns detected edge type.
 * @param det Pointer to the EdgeDetector instance.
 * @param input Current signal value (0 or 1).
 * @return EdgeType: EDGE_NONE, EDGE_RISING, or EDGE_FALLING.
 *
 * @details
 * - Detects transitions between consecutive samples.
 * - Automatically increments internal counters.
 * - Triggers callback (`on_edge`) if assigned.
 * - Thread-safe under single access per instance.
 */
EdgeType edge_update(EdgeDetector *det, uint8_t input);

/**
 * @brief Checks for any edge (rising or falling).
 * @param det Pointer to the EdgeDetector instance.
 * @param input Current signal (0 or 1).
 * @return 1 if the signal changed, otherwise 0.
 * @note Internally calls `edge_update()`.
 */
uint8_t edge_both(EdgeDetector *det, uint8_t input);

/**
 * @brief Resets internal counters (rising/falling).
 * @param det Pointer to the EdgeDetector instance.
 */
void edge_reset(EdgeDetector *det);

/**
 * @brief Retrieves rising edge count.
 * @param det Pointer to the EdgeDetector instance.
 * @return Number of rising edges detected.
 */
uint32_t edge_get_rise_count(const EdgeDetector *det);

/**
 * @brief Retrieves falling edge count.
 * @param det Pointer to the EdgeDetector instance.
 * @return Number of falling edges detected.
 */
uint32_t edge_get_fall_count(const EdgeDetector *det);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* EDGE_DETECTOR_H */
