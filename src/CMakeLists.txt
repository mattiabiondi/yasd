set(yasd_SRCS
	main.cpp
		gui/main_window.cpp
		gui/dialogs/new_dialog.cpp
		gui/dialogs/new_dialog.cpp
		gui/pages/cars_set_page.cpp
		gui/pages/map_page.cpp)

add_executable(yasd
	${yasd_SRCS}
)

target_compile_definitions(yasd
	PRIVATE -DPROJECT_VERSION="${PROJECT_VERSION}")

target_link_libraries(yasd
	Qt5::Widgets
	Qt5::Gui
)
