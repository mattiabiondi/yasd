set(yasd_SRCS
	main.cpp
	gui/main_window.cpp
	gui/wizards/new_wizard.cpp
	gui/wizards/pages/cars_page.cpp
	gui/wizards/pages/map_page.cpp
)

add_executable(yasd
	${yasd_SRCS}
)

target_compile_definitions(yasd
	PRIVATE -DPROJECT_VERSION="${PROJECT_VERSION}")

target_link_libraries(yasd
	Qt5::Widgets
	Qt5::Gui
)
