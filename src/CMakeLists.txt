set(GBAJAM_SOURCES
	main.c
)

set(GBAJAM_HEADERS
)

target_sources(gbajam-2022
	PRIVATE
		${GBAJAM_SOURCES}
		${GBAJAM_HEADERS}
)

target_include_directories(gbajam-2022
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_BINARY_DIR}/assets
)
