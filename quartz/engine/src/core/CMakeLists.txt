add_subdirectory(graphics)
add_subdirectory(math)
add_subdirectory(utils)
add_subdirectory(platform)

set(coreSources
	${graphicsSources}
	${mathSources}
	${utilSources}
	${platformSources}

	PARENT_SCOPE
)