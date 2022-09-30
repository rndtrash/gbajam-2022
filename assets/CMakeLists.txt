gba_add_maxmod_soundbank(soundbank GENERATE_HEADER
	${CMAKE_CURRENT_LIST_DIR}/hampter.wav
	${CMAKE_CURRENT_LIST_DIR}/buyselltrade.mod
	${CMAKE_CURRENT_LIST_DIR}/dreamy.mod
	${CMAKE_CURRENT_LIST_DIR}/abyssal.xm
)
set_target_properties(soundbank PROPERTIES SUFFIX ".bin")

set(GBFS_GAME_ASSETS
#	${CMAKE_CURRENT_LIST_DIR}/disclaimer.png
	${CMAKE_CURRENT_LIST_DIR}/disclaimer.img.bin
	${CMAKE_CURRENT_LIST_DIR}/disclaimer.map.bin
	${CMAKE_CURRENT_LIST_DIR}/disclaimer.pal.bin

#	${CMAKE_CURRENT_LIST_DIR}/rotundsters/jerry.png
#	${CMAKE_CURRENT_LIST_DIR}/rotundsters/snowball.png
#	${CMAKE_CURRENT_LIST_DIR}/rotundsters/seedy.png
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	gba_add_gbfs(assets GENERATE_ASM soundbank ${GBFS_GAME_ASSETS})
	enable_language(ASM)

	target_sources(gbajam-2022
		PRIVATE
			"$<TARGET_PROPERTY:assets,ASM_OUTPUT>"
	)
else()
	gba_add_gbfs(assets soundbank ${GBFS_GAME_ASSETS})

	target_compile_definitions(gbajam-2022
		PRIVATE
			ASSETS_GBFS
	)
endif()

add_dependencies(assets soundbank)
add_dependencies(gbajam-2022 assets)

set_target_properties(assets PROPERTIES SUFFIX ".gbfs")
