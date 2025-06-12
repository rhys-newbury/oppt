/** @file Action.hpp
 *
 * Defines the Action interface; currently this is the same as Point, so this is just a straight
 * typedef.
 */
#pragma once

#include "solvers/ABT/solver/abstract-problem/Point.hpp"

namespace abt {
    /** Currently Action has no requirements over and above Point, so this is just a typedef. */
    typedef Point Action;
} /* namespace abt */

