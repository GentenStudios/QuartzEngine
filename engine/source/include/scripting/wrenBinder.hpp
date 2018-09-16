#include <map>

#include <wren.hpp>

class wrenBinder
{
public:
	struct wrenBindingInfo;

	void setupBindings();
	void addBinding( wrenBindingInfo bindInfo, void* callback );
	void* returnBinding( wrenBindingInfo );

	WrenForeignMethodFn handleBinds( WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature );

private:
	std::map<wrenBindingInfo, void*> m_wrenBindings;
};
