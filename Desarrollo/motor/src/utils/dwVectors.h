#include "GraphicsEngine.h"

namespace dwu
{
    /// \brief Returns the normalized vector of v
    dwe::vec2f normalizeVector(const dwe::vec2f v);

    /// \brief Returns the angle in degrees of 2 normalized vectors
    float calculateDegrees(const dwe::vec2f normalizedVector1, const dwe::vec2f normalizedVector2);
}
