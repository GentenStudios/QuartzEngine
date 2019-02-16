add_subdirectory(graphics)
add_subdirectory(math)
add_subdirectory(platform)
add_subdirectory(utilities)

set(coreSources
	${graphicsSources}
	${mathSources}
	${platformSources}
	${utilitySources}

	PARENT_SCOPE
)
