#include "GraphicsEngine.h"

namespace dwu
{
    /// \brief Returns the normalized vector of v
    dwe::vec2f normalizeVector(const dwe::vec2f v);

    /// \brief Returns the angle in degrees of 2 normalized vectors
    float calculateDegrees(const dwe::vec2f normalizedVector1, const dwe::vec2f normalizedVector2);

    /// \brief Returns the squared distance between 2 positions
    float calculateSquaredDistance(const dwe::vec2f position1, const dwe::vec2f position2);

    /// \brief Returns the euclidean distance between 2 positions
    float calculateDistance(const dwe::vec2f position1, const dwe::vec2f position2);

    /// \brief Returns the angle in degrees of a normalized vector relative
    float calculateAngleYAxis(const dwe::vec2f normalizedVector);

}
