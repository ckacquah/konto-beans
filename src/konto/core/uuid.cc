#include "konto/core/uuid.h"

namespace Konto::UUID
{

uint64_t generate()
{
    return uniform_distribution(engine);
}

} // namespace Konto::UUID
