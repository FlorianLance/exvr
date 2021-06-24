/*******************************************************************************
** exvr-exp                                                                   **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

// system
using System;

// unity
using UnityEngine;

namespace Ex{

    public static class Maths{

        // base
        public static bool is_almost_equal(this double initialValue, double value) {
            return is_almost_equal(initialValue, value, 0.00001);
        }

        public static bool is_almost_equal(this double initialValue, double value, double maximumDifferenceAllowed) {
            // Handle comparisons of floating point values that may not be exactly the same
            return (Math.Abs(initialValue - value) < maximumDifferenceAllowed);
        }

        // geometry
        public static bool same_side(Vector3 p1, Vector3 p2, Vector3 a, Vector3 b) {
            Vector3 cp1 = Vector3.Cross(b - a, p1 - a);
            Vector3 cp2 = Vector3.Cross(b - a, p2 - a);
            if (Vector3.Dot(cp1, cp2) >= 0) {
                return true;
            }
            return false;
        }

        public static bool point_in_triangle(Vector3 p, Vector3 a, Vector3 b, Vector3 c) {
            if (same_side(p, a, b, c) && same_side(p, b, a, c) && same_side(p, c, a, b)) {
                return true;
            }
            return false;
        }
    }
}