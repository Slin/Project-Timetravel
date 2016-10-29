//
// Created by Matthias Bruns on 28/10/2016.
//

#include "Math.h"
#include <complex>

namespace TT {
    /// Returns the difference between the two vectors.
    sf::Vector2f Math::sub(sf::Vector2f a, sf::Vector2f b){
        return sf::Vector2f(a.x - b.x, a.y - b.y);
    }

    /// Returns the dot product between the two vectors.
    float Math::dot(sf::Vector2f a, sf::Vector2f b){
        // a.dot(b) = a.x * b.x + a.y * b.y;
        return a.x * b.x + a.y * b.y;
    }

    /// Returns the z component of the cross product of the two vectors augmented to 3D.
    float Math::cross(sf::Vector2f a, sf::Vector2f b){
        //a.cross(b) = a.x * b.y – a.y * b.x;
        return a.x * b.y - a.y * b.x;
    }

    /// Returns the length of the vector.
    float Math::length(sf::Vector2f a) {
        // a.length() = sqrt(a.x * a.x + a.y * a.y);
        return sqrtf(Math::squaredLength(a));
    }

    /// Returns the square of the length of the vector. Useful when you just want to compare two vectors to see which is longest, as this avoids computing square roots
    float Math::squaredLength(sf::Vector2f a) {
        // a.squaredLength() = a.x * a.x + a.y * a.y;
        return a.x * a.x + a.y * a.y;
    }

    /// Returns a vector pointing on the same direction, but with a length of 1.
    sf::Vector2f Math::unit(sf::Vector2f a) {
        // a.unit() = a / a.length();
        return a / Math::length(a);
    }

    /// Returns the vector rotated 90 degrees left. Useful for computing normals. (Assumes that y axis points up, otherwise this is turnRight)
    sf::Vector2f Math::turnLeft(sf::Vector2f a) {
        // a.turnLeft = Vector2f(-a.y, a.x);
        return sf::Vector2f(-a.y, a.x);
    }

    /// Returns the vector rotated 90 degrees right. Useful for computing normals. (Assumes that y axis points up, otherwise this is turnLeft)
    sf::Vector2f Math::turnRight(sf::Vector2f a) {
        // a.turnRight = Vector2f(a.y, -a.x);
        return sf::Vector2f(a.y, -a.x);
    }

    /// Rotates the vector by the specified angle. This is an extremely useful operation, though it is rarely found in Vector classes. Equivalent to multiplying by the 2×2 rotation matrix.
    sf::Vector2f Math::rotate(sf::Vector2f a, float angle) {
        // a.rotate(angle) =  Vector2f(a.x * cos(angle) – a.y * sin(angle), a.x * sin(angle) + a.y * cos(angle));
        return sf::Vector2f(a.x * cos(angle) - a.y * sin(angle), a.x * sin(angle) + a.y * cos(angle));
    }

    float Math::distance(sf::Vector2f a, sf::Vector2f b) {
        float length = Math::length(Math::sub(a, b));
        return length;
    }

    /// Returns the angle that the vector points to.
    static float angle(sf::Vector2f a) {
        // a.angle() = atan2(a.y, a.x);
        return atan2(a.y, a.x);
    }
}
