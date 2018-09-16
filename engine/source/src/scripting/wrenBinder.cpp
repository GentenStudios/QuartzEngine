#include "scripting/wrenBinder.hpp"



void wrenBinder::setupBindings()
{
	/// @todo Load basic function binds in here. Maybe do it in an external file?
}

void wrenBinder::addBinding( wrenBindingInfo bindInfo, void* callback )
{
	m_wrenBindings[bindInfo] = callback; // Set the callback function for the specific bindInfo in the hashmap
}

void* wrenBinder::returnBinding( wrenBindingInfo bindInfo )
{
	return m_wrenBindings[bindInfo]; // Look for the binded function (void*) in the hashmap, using bindInfo as the key
}

WrenForeignMethodFn wrenBinder::handleBinds(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature)
{
	wrenBindingInfo bindData = {vm, module, className, isStatic, signature};

	void* bindReturn = returnBinding( bindData );
	if (bindReturn != nullptr) // Make sure the function isn't a null pointer, basically checks whether function binding exists
	{
		return reinterpret_cast<void(*)(WrenVM*)>( bindReturn ); // Return the function as a void pointer with a parameter of WrenVM*
	}

	return nullptr; // not sure if this will crash but whatever. ¯\_(ツ)_/¯
}
