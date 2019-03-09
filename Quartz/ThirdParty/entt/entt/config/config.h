#ifndef ENTT_CONFIG_CONFIG_H
#define ENTT_CONFIG_CONFIG_H


#ifndef ENTT_NOEXCEPT
#define ENTT_NOEXCEPT noexcept
#endif // ENTT_NOEXCEPT


#ifndef ENTT_HS_SUFFIX
#define ENTT_HS_SUFFIX _hs
#endif // ENTT_HS_SUFFIX


#ifndef ENTT_NO_ATOMIC
#include <atomic>
template<typename Type>
using maybe_atomic_t = std::atomic<Type>;
#else
template<typename Type>
using maybe_atomic_t = Type;
#endif // ENTT_USE_ATOMIC


#ifndef ENTT_HASH_TYPE
#include <cstdint>
#define ENTT_HASH_TYPE std::uint32_t
#endif


#endif // ENTT_CONFIG_CONFIG_H
