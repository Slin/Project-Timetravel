//
// Created by Matthias Bruns on 29/10/2016.
//

#ifndef TIMETRAVEL_MATH_H
#define TIMETRAVEL_MATH_H

#include <SFML/System/Vector2.hpp>

namespace TT
{
    class Math
    {
    public:
        /// Returns the dot product between the two vectors.
        static float dot(sf::Vector2f a, sf::Vector2f b);

        /// Returns the z component of the cross product of the two vectors augmented to 3D.
        static float cross(sf::Vector2f a, sf::Vector2f b);

        /// Returns the length of the vector.
        static float length(sf::Vector2f a);

        /// Returns the square of the length of the vector. Useful when you just want to compare two vectors to see which is longest, as this avoids computing square roots
        static float squaredLength(sf::Vector2f a);

        /// Returns a vector pointing on the same direction, but with a length of 1.
        static sf::Vector2f unit(sf::Vector2f a);

        /// Returns the vector rotated 90 degrees left. Useful for computing normals. (Assumes that y axis points up, otherwise this is turnRight)
        static sf::Vector2f turnLeft(sf::Vector2f a);

        /// Returns the vector rotated 90 degrees right. Useful for computing normals. (Assumes that y axis points up, otherwise this is turnLeft)
        static sf::Vector2f turnRight(sf::Vector2f a);

        /// Rotates the vector by the specified angle. This is an extremely useful operation, though it is rarely found in Vector classes. Equivalent to multiplying by the 2×2 rotation matrix.
        static sf::Vector2f rotate(sf::Vector2f a, float angle);

        /// Returns the angle that the vector points to.
        static float angle(sf::Vector2f a);

    private:
        Math(){}
    };
}

#endif //TIMETRAVEL_MATH_H
