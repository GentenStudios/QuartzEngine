add_subdirectory(Graphics)
add_subdirectory(Math)
add_subdirectory(Platform)
add_subdirectory(Utilities)

set(coreSources
	${graphicsSources}
	${mathSources}
	${platformSources}
	${utilitySources}

	PARENT_SCOPE
)
