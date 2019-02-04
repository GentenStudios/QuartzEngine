#include <Windows.h>

#include <luamod/luastate.h>
#include <luamod/table.h>
#include <luamod/function.h>

namespace test_lib {
	void ShowMessageBox(const char* title, const char* text, int buttons) {
		::MessageBox(0, text, title, buttons);
	}
}

int main() {
	lm::LuaState lua;
	
	lua.SetGlobal("MessageBoxButtons_OK", MB_OK);
	lua.SetGlobal("MessageBoxButtons_OKCancel", MB_OKCANCEL);

	lua.Register("ShowMessageBox", &test_lib::ShowMessageBox);
	lua.Register("GetRandomNumber", []() {
		// https://xkcd.com/221/
		return 4; // chosen by fair dice roll.
		          // guaranteed to be random.
	});

	lm::Table resultTable = lua.RunFile<lm::Table>("scripts/index.lua");
	std::string tablePropertyA = resultTable.GetProperty<std::string>("a");
	std::string tablePropertyB = resultTable.GetProperty<std::string>("b");

	lm::Table tablePropertyC = resultTable.GetProperty<lm::Table>("c");
	int tablePropertyCPropertyD = tablePropertyC.GetProperty<int>("d");

	printf("{\n");
	printf("\ta=\"%s\",\n", tablePropertyA.c_str());
	printf("\tb=\"%s\",\n", tablePropertyB.c_str());
	printf("\tc={\n");
	printf("\t\td=%i\n", tablePropertyCPropertyD);
	printf("\t}\n");
	printf("}\n");


	return 0;
}
