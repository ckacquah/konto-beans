#ifndef __KONTO_CORE_UUID_H__
#define __KONTO_CORE_UUID_H__

#include <random>

namespace Konto::UUID
{

static std::random_device random_device;
static std::mt19937_64 engine(random_device());
static std::uniform_int_distribution<uint64_t> uniform_distribution;

uint64_t generate();

} // namespace Konto::UUID

#endif // __KONTO_CORE_UUID_H__
