set(TARGET_NAME lecture-04-lib)

set(SOURCES
	CommonFunc.cpp
	StringFunc.cpp
	pch.cpp
)

# Same source list compiled twice: once as-is (ANSI/"A" flavor) and once
# with -DUNICODE (Wide/"W" flavor). This is the "static library
# separation and duplication" one-source dual compile required by the
# assignment -- mirrors cppcore's own Src/CMakeLists.txt pattern.
add_library(${TARGET_NAME}A OBJECT ${SOURCES})
add_library(${TARGET_NAME}W OBJECT ${SOURCES})

target_include_directories(${TARGET_NAME}A PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CPPCORE_INC_DIR}
)
target_include_directories(${TARGET_NAME}W PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CPPCORE_INC_DIR}
)

target_compile_options(${TARGET_NAME}A PUBLIC -Wno-narrowing)
target_compile_options(${TARGET_NAME}W PUBLIC -Wno-narrowing)
target_compile_definitions(${TARGET_NAME}W PUBLIC -DUNICODE -D_UNICODE)

# Combine both object flavors into a single static archive. Symbols whose
# signature depends on UNICODE (PrintString) end up as two distinct
# mangled names, and symbols that don't (CommonFunc) exist twice in the
# archive but that's harmless: static-archive linking is lazy, so the
# final link only pulls in whichever object member is needed to resolve
# each reference.
add_library(${TARGET_NAME} STATIC
	$<TARGET_OBJECTS:${TARGET_NAME}A>
	$<TARGET_OBJECTS:${TARGET_NAME}W>
)

target_include_directories(${TARGET_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CPPCORE_INC_DIR}
)
