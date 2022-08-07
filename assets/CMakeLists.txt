gba_add_maxmod_soundbank(soundbank GENERATE_HEADER
	${CMAKE_CURRENT_LIST_DIR}/hampter.wav
	${CMAKE_CURRENT_LIST_DIR}/nogood.mod
)
set_target_properties(soundbank PROPERTIES SUFFIX ".bin")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	gba_add_gbfs(assets GENERATE_ASM soundbank)
	enable_language(ASM)

	target_sources(gbajam-2022
		PRIVATE
			"$<TARGET_PROPERTY:assets,ASM_OUTPUT>"
	)
else()
	gba_add_gbfs(assets soundbank)

	target_compile_definitions(gbajam-2022
		PRIVATE
			ASSETS_GBFS
	)
endif()

add_dependencies(assets soundbank)
add_dependencies(gbajam-2022 assets)

set_target_properties(assets PROPERTIES SUFFIX ".gbfs")
