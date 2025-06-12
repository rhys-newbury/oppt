/** @file Observation.hpp
 *
 * Defines the Observation interface; currently this is the same as Point, so this is just a
 * straight typedef.
 */
#pragma once

#include "solvers/ABT/solver/abstract-problem/Point.hpp"

namespace abt {
    /** Currently Observation has no requirements over and above Point,
     * so this is just a typedef.
     */
    typedef Point Observation;
} /* namespace abt */

