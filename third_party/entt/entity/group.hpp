#ifndef ENTT_ENTITY_GROUP_HPP
#define ENTT_ENTITY_GROUP_HPP


#include <cassert>
#include <tuple>
#include <utility>
#include <algorithm>
#include <type_traits>
#include "../config/config.h"
#include "../core/type_traits.hpp"
#include "sparse_set.hpp"


namespace entt {


/**
 * @brief Forward declaration of the registry class.
 */
template<typename>
class registry;


/**
 * @brief Alias for lists of observed components.
 * @tparam Type List of types.
 */
template<typename... Type>
struct get_t: type_list<Type...> {};


/**
 * @brief Variable template for lists of observed components.
 * @tparam Type List of types.
 */
template<typename... Type>
constexpr get_t<Type...> get{};


/**
 * @brief Group.
 *
 * Primary template isn't defined on purpose. All the specializations give a
 * compile-time error, but for a few reasonable cases.
 */
template<typename...>
class group;


/**
 * @brief Detached group.
 *
 * A detached group returns all the entities and only the entities that have at
 * least the given components. Moreover, it's guaranteed that the entity list is
 * tightly packed in memory for fast iterations.<br/>
 * In general, detached groups don't stay true to the order of any set of
 * components unless users explicitly sort them.
 *
 * @b Important
 *
 * Iterators aren't invalidated if:
 *
 * * New instances of the given components are created and assigned to entities.
 * * The entity currently pointed is modified (as an example, if one of the
 *   given components is removed from the entity to which the iterator points).
 *
 * In all the other cases, modifying the pools of the given components in any
 * way invalidates all the iterators and using them results in undefined
 * behavior.
 *
 * @note
 * Groups share references to the underlying data structures of the registry
 * that generated them. Therefore any change to the entities and to the
 * components made by means of the registry are immediately reflected by all the
 * groups.<br/>
 * Moreover, sorting a detached group affects all the other groups of the same
 * type (it means that users don't have to call `sort` on each group to sort all
 * of them because they share the set of entities).
 *
 * @warning
 * Lifetime of a group must overcome the one of the registry that generated it.
 * In any other case, attempting to use a group results in undefined behavior.
 *
 * @tparam Entity A valid entity type (see entt_traits for more details).
 * @tparam Get Types of components iterated by the group.
 */
template<typename Entity, typename... Get>
class group<Entity, get_t<Get...>> {
    static_assert(sizeof...(Get));

    /*! @brief A registry is allowed to create groups. */
    friend class registry<Entity>;

    template<typename Component>
    using pool_type = std::conditional_t<std::is_const_v<Component>, const sparse_set<Entity, std::remove_const_t<Component>>, sparse_set<Entity, Component>>;

    // we could use pool_type<Get> *..., but vs complains about it and refuses to compile for unknown reasons (likely a bug)
    group(sparse_set<Entity> *handler, sparse_set<Entity, std::remove_const_t<Get>> *... pools) ENTT_NOEXCEPT
        : handler{handler},
          pools{pools...}
    {}

public:
    /*! @brief Underlying entity identifier. */
    using entity_type = typename sparse_set<Entity>::entity_type;
    /*! @brief Unsigned integer type. */
    using size_type = typename sparse_set<Entity>::size_type;
    /*! @brief Input iterator type. */
    using iterator_type = typename sparse_set<Entity>::iterator_type;

    /*! @brief Default copy constructor. */
    group(const group &) = default;
    /*! @brief Default move constructor. */
    group(group &&) = default;

    /*! @brief Default copy assignment operator. @return This group. */
    group & operator=(const group &) = default;
    /*! @brief Default move assignment operator. @return This group. */
    group & operator=(group &&) = default;

    /**
     * @brief Returns the number of entities that have the given components.
     * @return Number of entities that have the given components.
     */
    size_type size() const ENTT_NOEXCEPT {
        return handler->size();
    }

    /**
     * @brief Checks whether the group is empty.
     * @return True if the group is empty, false otherwise.
     */
    bool empty() const ENTT_NOEXCEPT {
        return handler->empty();
    }

    /**
     * @brief Direct access to the list of entities.
     *
     * The returned pointer is such that range `[data(), data() + size()]` is
     * always a valid range, even if the container is empty.
     *
     * @note
     * There are no guarantees on the order of the entities. Use `begin` and
     * `end` if you want to iterate the group in the expected order.
     *
     * @return A pointer to the array of entities.
     */
    const entity_type * data() const ENTT_NOEXCEPT {
        return handler->data();
    }

    /**
     * @brief Returns an iterator to the first entity that has the given
     * components.
     *
     * The returned iterator points to the first entity that has the given
     * components. If the group is empty, the returned iterator will be equal to
     * `end()`.
     *
     * @note
     * Input iterators stay true to the order imposed to the underlying data
     * structures.
     *
     * @return An iterator to the first entity that has the given components.
     */
    iterator_type begin() const ENTT_NOEXCEPT {
        return handler->begin();
    }

    /**
     * @brief Returns an iterator that is past the last entity that has the
     * given components.
     *
     * The returned iterator points to the entity following the last entity that
     * has the given components. Attempting to dereference the returned iterator
     * results in undefined behavior.
     *
     * @note
     * Input iterators stay true to the order imposed to the underlying data
     * structures.
     *
     * @return An iterator to the entity following the last entity that has the
     * given components.
     */
    iterator_type end() const ENTT_NOEXCEPT {
        return handler->end();
    }

    /**
     * @brief Finds an entity.
     * @param entity A valid entity identifier.
     * @return An iterator to the given entity if it's found, past the end
     * iterator otherwise.
     */
    iterator_type find(const entity_type entity) const ENTT_NOEXCEPT {
        const auto it = handler->find(entity);
        return it != end() && *it == entity ? it : end();
    }

    /**
     * @brief Returns the identifier that occupies the given position.
     * @param pos Position of the element to return.
     * @return The identifier that occupies the given position.
     */
    entity_type operator[](const size_type pos) const ENTT_NOEXCEPT {
        return begin()[pos];
    }

    /**
     * @brief Checks if a group contains an entity.
     * @param entity A valid entity identifier.
     * @return True if the group contains the given entity, false otherwise.
     */
    bool contains(const entity_type entity) const ENTT_NOEXCEPT {
        return find(entity) != end();
    }

    /**
     * @brief Returns the components assigned to the given entity.
     *
     * Prefer this function instead of `registry::get` during iterations. It has
     * far better performance than its companion function.
     *
     * @warning
     * Attempting to use an invalid component type results in a compilation
     * error. Attempting to use an entity that doesn't belong to the group
     * results in undefined behavior.<br/>
     * An assertion will abort the execution at runtime in debug mode if the
     * group doesn't contain the given entity.
     *
     * @tparam Component Types of components to get.
     * @param entity A valid entity identifier.
     * @return The components assigned to the entity.
     */
    template<typename... Component>
    std::conditional_t<sizeof...(Component) == 1, std::tuple_element_t<0, std::tuple<Component &...>>, std::tuple<Component &...>>
    get([[maybe_unused]] const entity_type entity) const ENTT_NOEXCEPT {
        assert(contains(entity));

        if constexpr(sizeof...(Component) == 1) {
            static_assert(std::disjunction_v<std::is_same<Component..., Get>..., std::is_same<std::remove_const_t<Component>..., Get>...>);
            return (std::get<pool_type<Component> *>(pools)->get(entity), ...);
        } else {
            return std::tuple<Component &...>{get<Component>(entity)...};
        }
    }

    /**
     * @brief Iterates entities and components and applies the given function
     * object to them.
     *
     * The function object is invoked for each entity. It is provided with the
     * entity itself and a set of references to all its components. The
     * _constness_ of the components is as requested.<br/>
     * The signature of the function must be equivalent to one of the following
     * forms:
     *
     * @code{.cpp}
     * void(const entity_type, Get &...);
     * void(Get &...);
     * @endcode
     *
     * @tparam Func Type of the function object to invoke.
     * @param func A valid function object.
     */
    template<typename Func>
    inline void each(Func func) const {
        if constexpr(std::is_invocable_v<Func, std::add_lvalue_reference_t<Get>...>) {
            std::for_each(handler->begin(), handler->end(), [func = std::move(func), this](const auto entity) mutable {
                func(std::get<pool_type<Get> *>(pools)->get(entity)...);
            });
        } else {
            std::for_each(handler->begin(), handler->end(), [func = std::move(func), this](const auto entity) mutable {
                func(entity, std::get<pool_type<Get> *>(pools)->get(entity)...);
            });
        }
    }

    /**
     * @brief Sort the shared pool of entities according to the given component.
     *
     * Detached groups of the same type share with the registry a pool of
     * entities with  its own order that doesn't depend on the order of any pool
     * of components. Users can order the underlying data structure so that it
     * respects the order of the pool of the given component.
     *
     * @note
     * The shared pool of entities and thus its order is affected by the changes
     * to each and every pool that it tracks. Therefore changes to those pools
     * can quickly ruin the order imposed to the pool of entities shared between
     * the detached groups.
     *
     * @tparam Component Type of component to use to impose the order.
     */
    template<typename Component>
    void sort() const {
        handler->respect(*std::get<pool_type<Component> *>(pools));
    }

private:
    sparse_set<entity_type> *handler;
    const std::tuple<pool_type<Get> *...> pools;
};


/**
 * @brief Owning group.
 *
 * Owning groups return all the entities and only the entities that have at
 * least the given components. Moreover:
 *
 * * It's guaranteed that the entity list is tightly packed in memory for fast
 *   iterations.
 * * It's guaranteed that the lists of owned components are tightly packed in
 *   memory for even faster iterations and to allow direct access.
 * * They stay true to the order of the owned components and all the owned
 *   components have the same order in memory.
 *
 * The more types of components are owned by a group, the faster it is to
 * iterate them.
 *
 * @b Important
 *
 * Iterators aren't invalidated if:
 *
 * * New instances of the given components are created and assigned to entities.
 * * The entity currently pointed is modified (as an example, if one of the
 *   given components is removed from the entity to which the iterator points).
 *
 * In all the other cases, modifying the pools of the given components in any
 * way invalidates all the iterators and using them results in undefined
 * behavior.
 *
 * @note
 * Groups share references to the underlying data structures of the registry
 * that generated them. Therefore any change to the entities and to the
 * components made by means of the registry are immediately reflected by all the
 * groups.
 *
 * @warning
 * Lifetime of a group must overcome the one of the registry that generated it.
 * In any other case, attempting to use a group results in undefined behavior.
 *
 * @tparam Entity A valid entity type (see entt_traits for more details).
 * @tparam Get Types of components observed by the group.
 * @tparam Owned Types of components owned by the group.
 */
template<typename Entity, typename... Get, typename... Owned>
class group<Entity, get_t<Get...>, Owned...> {
    static_assert(sizeof...(Get) + sizeof...(Owned));

    /*! @brief A registry is allowed to create groups. */
    friend class registry<Entity>;

    template<typename Component>
    using pool_type = std::conditional_t<std::is_const_v<Component>, const sparse_set<Entity, std::remove_const_t<Component>>, sparse_set<Entity, Component>>;

    template<typename Component>
    using component_iterator_type = decltype(std::declval<pool_type<Component>>().begin());

    // we could use pool_type<Type> *..., but vs complains about it and refuses to compile for unknown reasons (likely a bug)
    group(typename sparse_set<Entity>::size_type *length, sparse_set<Entity, std::remove_const_t<Owned>> *... owned, sparse_set<Entity, std::remove_const_t<Get>> *... others) ENTT_NOEXCEPT
        : length{length},
          pools{owned..., others...}
    {}

public:
    /*! @brief Underlying entity identifier. */
    using entity_type = typename sparse_set<Entity>::entity_type;
    /*! @brief Unsigned integer type. */
    using size_type = typename sparse_set<Entity>::size_type;
    /*! @brief Input iterator type. */
    using iterator_type = typename sparse_set<Entity>::iterator_type;

    /*! @brief Default copy constructor. */
    group(const group &) = default;
    /*! @brief Default move constructor. */
    group(group &&) = default;

    /*! @brief Default copy assignment operator. @return This group. */
    group & operator=(const group &) = default;
    /*! @brief Default move assignment operator. @return This group. */
    group & operator=(group &&) = default;

    /**
     * @brief Returns the number of entities that have the given components.
     * @return Number of entities that have the given components.
     */
    size_type size() const ENTT_NOEXCEPT {
        return *length;
    }

    /**
     * @brief Checks whether the group is empty.
     * @return True if the group is empty, false otherwise.
     */
    bool empty() const ENTT_NOEXCEPT {
        return !*length;
    }

    /**
     * @brief Direct access to the list of components of an owned type.
     *
     * The returned pointer is such that range `[raw(), raw() + size()]` is
     * always a valid range, even if the container is empty.
     *
     * @note
     * There are no guarantees on the order of the components. Use `each` if you
     * want to iterate the group in the expected order.
     *
     * @warning
     * Empty components aren't explicitly instantiated. Therefore, this function
     * always returns `nullptr` for them.
     *
     * @return A pointer to the array of components.
     */
    template<typename Component>
    Component * raw() const ENTT_NOEXCEPT {
        static_assert(std::disjunction_v<std::is_same<Component, Owned>..., std::is_same<std::remove_const_t<Component>, Owned>...>);
        return std::get<pool_type<Component> *>(pools)->raw();
    }

    /**
     * @brief Direct access to the list of entities.
     *
     * The returned pointer is such that range `[data(), data() + size()]` is
     * always a valid range, even if the container is empty.
     *
     * @note
     * There are no guarantees on the order of the entities. Use `begin` and
     * `end` if you want to iterate the view in the expected order.
     *
     * @return A pointer to the array of entities.
     */
    const entity_type * data() const ENTT_NOEXCEPT {
        return std::get<0>(pools)->data();
    }

    /**
     * @brief Returns an iterator to the first entity that has the given
     * components.
     *
     * The returned iterator points to the first entity that has the given
     * components. If the group is empty, the returned iterator will be equal to
     * `end()`.
     *
     * @note
     * Input iterators stay true to the order imposed to the underlying data
     * structures.
     *
     * @return An iterator to the first entity that has the given components.
     */
    iterator_type begin() const ENTT_NOEXCEPT {
        return std::get<0>(pools)->sparse_set<entity_type>::end() - *length;
    }

    /**
     * @brief Returns an iterator that is past the last entity that has the
     * given components.
     *
     * The returned iterator points to the entity following the last entity that
     * has the given components. Attempting to dereference the returned iterator
     * results in undefined behavior.
     *
     * @note
     * Input iterators stay true to the order imposed to the underlying data
     * structures.
     *
     * @return An iterator to the entity following the last entity that has the
     * given components.
     */
    iterator_type end() const ENTT_NOEXCEPT {
        return std::get<0>(pools)->sparse_set<entity_type>::end();
    }

    /**
     * @brief Finds an entity.
     * @param entity A valid entity identifier.
     * @return An iterator to the given entity if it's found, past the end
     * iterator otherwise.
     */
    iterator_type find(const entity_type entity) const ENTT_NOEXCEPT {
        const auto it = std::get<0>(pools)->find(entity);
        return it != end() && it >= begin() && *it == entity ? it : end();
    }

    /**
     * @brief Returns the identifier that occupies the given position.
     * @param pos Position of the element to return.
     * @return The identifier that occupies the given position.
     */
    entity_type operator[](const size_type pos) const ENTT_NOEXCEPT {
        return begin()[pos];
    }

    /**
     * @brief Checks if a group contains an entity.
     * @param entity A valid entity identifier.
     * @return True if the group contains the given entity, false otherwise.
     */
    bool contains(const entity_type entity) const ENTT_NOEXCEPT {
        return find(entity) != end();
    }

    /**
     * @brief Returns the components assigned to the given entity.
     *
     * Prefer this function instead of `registry::get` during iterations. It has
     * far better performance than its companion function.
     *
     * @warning
     * Attempting to use an invalid component type results in a compilation
     * error. Attempting to use an entity that doesn't belong to the group
     * results in undefined behavior.<br/>
     * An assertion will abort the execution at runtime in debug mode if the
     * group doesn't contain the given entity.
     *
     * @tparam Component Types of components to get.
     * @param entity A valid entity identifier.
     * @return The components assigned to the entity.
     */
    template<typename... Component>
    std::conditional_t<sizeof...(Component) == 1, std::tuple_element_t<0, std::tuple<Component &...>>, std::tuple<Component &...>>
    get([[maybe_unused]] const entity_type entity) const ENTT_NOEXCEPT {
        assert(contains(entity));

        if constexpr(sizeof...(Component) == 1) {
            static_assert(std::disjunction_v<std::is_same<Component..., Owned>..., std::is_same<std::remove_const_t<Component>..., Owned>...,
                          std::is_same<Component..., Get>..., std::is_same<std::remove_const_t<Component>..., Get>...>);
            return (std::get<pool_type<Component> *>(pools)->get(entity), ...);
        } else {
            return std::tuple<Component &...>{get<Component>(entity)...};
        }
    }

    /**
     * @brief Iterates entities and components and applies the given function
     * object to them.
     *
     * The function object is invoked for each entity. It is provided with the
     * entity itself and a set of references to all its components. The
     * _constness_ of the components is as requested.<br/>
     * The signature of the function must be equivalent to one of the following
     * forms:
     *
     * @code{.cpp}
     * void(const entity_type, Owned &..., Get &...);
     * void(Owned &..., Get &...);
     * @endcode
     *
     * @tparam Func Type of the function object to invoke.
     * @param func A valid function object.
     */
    template<typename Func>
    inline void each(Func func) const {
        auto raw = std::make_tuple((std::get<pool_type<Owned> *>(pools)->end() - *length)...);
        [[maybe_unused]] auto data = std::get<0>(pools)->sparse_set<entity_type>::end() - *length;
        const auto cend = std::get<0>(pools)->end();

        while(std::get<0>(raw) != cend) {
            if constexpr(std::is_invocable_v<Func, std::add_lvalue_reference_t<Owned>..., std::add_lvalue_reference_t<Get>...>) {
                if constexpr(sizeof...(Get)) {
                    const auto entity = *(data++);
                    func(*(std::get<component_iterator_type<Owned>>(raw)++)..., std::get<pool_type<Get> *>(pools)->get(entity)...);
                } else {
                    func(*(std::get<component_iterator_type<Owned>>(raw)++)...);
                }
            } else {
                const auto entity = *(data++);
                func(entity, *(std::get<component_iterator_type<Owned>>(raw)++)..., std::get<pool_type<Get> *>(pools)->get(entity)...);
            }
        }
    }

private:
    const size_type *length;
    const std::tuple<pool_type<Owned> *..., pool_type<Get> *...> pools;
};


}


#endif // ENTT_ENTITY_GROUP_HPP
