set(yasd_SRCS
	main.cpp
	mainwindow.cpp
)

add_executable(yasd
	${yasd_SRCS}
)

target_compile_definitions(yasd
	PRIVATE -DPROJECT_VERSION="${PROJECT_VERSION}")

target_link_libraries(yasd
	Qt5::Widgets
)
