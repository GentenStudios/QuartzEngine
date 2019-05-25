add_subdirectory(Core)
add_subdirectory(Voxels)
add_subdirectory(Math)
add_subdirectory(Graphics)
add_subdirectory(Utilities)
add_subdirectory(Platform)

set(quartzSources
	${coreSources}
	${voxelSources}
	${mathSources}
	${graphicsSources}
	${utilitySources}
	${platformSources}

	PARENT_SCOPE
)
