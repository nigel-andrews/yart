#include "sampler.h"

#include "utils/misc.h"

glm::vec2 sampler::sample2D(const glm::vec2& discrete_coords) const
{
    return { discrete_coords.x + utils::randf<-0.5f, 0.5f>(),
             discrete_coords.y + utils::randf<-0.5f, 0.5f>() };
}
