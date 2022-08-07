cmake_minimum_required(VERSION 3.18)

set(ARM_GNU_TOOLCHAIN "${CMAKE_CURRENT_LIST_DIR}/gba-toolchain")
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/gba-toolchain/arm-gba-toolchain.cmake")

project(gbajam-2022 C)

set(GBA_LIBS rom tonc maxmod gbfs agbabi)

gba_add_library_subdirectory(${GBA_LIBS})

add_executable(gbajam-2022)
set_target_properties(gbajam-2022 PROPERTIES SUFFIX ".elf")

add_subdirectory(assets)
add_subdirectory(src)

target_compile_features(gbajam-2022
	PRIVATE
		c_std_17
)
target_compile_options(gbajam-2022 PRIVATE -mthumb -ffunction-sections -fdata-sections -Wall -Wextra)
target_link_options(gbajam-2022 PRIVATE -Wl,--gc-sections)
target_link_libraries(gbajam-2022 PRIVATE ${GBA_LIBS})

gba_target_sources_compile_options(gbajam-2022
	IWRAM -g0 -Os -marm
	EWRAM -g0 -O3 -mthumb
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	gba_target_objcopy(gbajam-2022 FIX_HEADER)
else()
	gba_target_objcopy(gbajam-2022 FIX_HEADER PAD 256 OUTPUT gbajam-2022_noassets.gba)
	add_custom_command(TARGET gbajam-2022 POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E cat gbajam-2022_noassets.gba assets/assets.gbfs ">" gbajam-2022.gba
	)
endif()

add_custom_target(TARGET run
	COMMAND visualboyadvance-m ${CMAKE_CURRENT_BINARY_DIR}/gbajam-2022.gba
	DEPENDS gbajam-2022
	WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
