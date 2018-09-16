/**
 * @file wrenBinder.hpp
 * @brief The Class & Function declarations for Wren <-> C++ bindings
*/

#include <map>

#include <wren.hpp>

/**
 * @brief The wrenBinder class, manages binding Wren and C++ functions together.
 */
class wrenBinder
{
public:
	/**
	 * @brief The wrenBindingInfo struct to hold data for easy transfer
	 * @details The wrenBindingInfo data structure is used to pass around all the required
	 *			Wren-specific variables that are needed for C++ to execute functions and data modificiations
	 *			properly from the WrenVM.
	 */
	struct wrenBindingInfo
	{
		WrenVM* vm;				///< A pointer to a WrenVM. This is required so C++ functions can reference and use variables and methods from a specific VM
		const char* module;		///< The module from which the foreign method is being called.
		const char* className;	///< The name of the Class from which the foreign method originates from.
		bool isStatic;			///< Whether the foreign method being called is static or not.
		const char* signature;	///< The foreign method's signature.

		/**
		 * @brief "Less Than" Operator Overload to make Hashmaps work as intended.
		 */
		bool operator<(const wrenBindingInfo other) const
		{
			return	vm									< other.vm									&&
					std::hash<std::string>{}(module)	< std::hash<std::string>{}(other.module)	&&
					std::hash<std::string>{}(className) < std::hash<std::string>{}(other.className) &&
					isStatic							< other.isStatic							&&
					std::hash<std::string>{}(signature) < std::hash<std::string>{}(other.signature);
		}
	};

	/**
	 * @brief The function to automatically load certain binds into the hashmap.
	 */
	void setupBindings();

	/**
	 * @brief Function to add bindings to the hashmap.
	 * @param bindInfo An instance of the wrenBindingInfo struct. Used for passing Wren-specfic data much more tidily as function parameters
	 * @param callback A void pointer of the C++ function to be called when the respective foreign Wren method is called
	 */
	void addBinding( wrenBindingInfo bindInfo, void* callback );

	/**
	 * @brief Returns a void pointer to the callback function of a foreign Wren method.
	 * @return Returns a void pointer to a function.
	 */
	void* returnBinding( wrenBindingInfo );

	/**
	 * @brief Function to handle foreign method "translation to C++ function" requests from the WrenVM.
	 * @param vm A pointer to a WrenVM instance.
	 * @param module The name of the module from which the foreign method is being called.
	 * @param className The name of the class from which the foreign method is being called
	 * @param isStatic Whether the foreign method is static or not.
	 * @param signature The function signature of the foreign method.
	 * @return A WrenForeignMethodFn, which is a typedef for a void(WrenVM* vm) function.
	 */
	WrenForeignMethodFn handleBinds( WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature );

private:
	/**
	 * @brief The hashmap storing the key-value pair for the actual binds themselves.
	 */
	std::map<wrenBindingInfo, void*> m_wrenBindings;
};
