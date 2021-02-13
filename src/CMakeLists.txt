set(yasd_SRCS
	main.cpp
	configuration.cpp
	application.cpp
	windows/main_window.cpp
	windows/track_window.cpp
	windows/input.cpp
	tabs/config_tab.cpp
	tabs/track_tab.cpp
	wizards/new_wizard.cpp
	wizards/pages/cars_page.cpp
	wizards/pages/track_page.cpp
	dialogs/cars_dialog.cpp
	dialogs/track_dialog.cpp
)

add_executable(yasd
	${yasd_SRCS}
)

target_compile_definitions(yasd
	PRIVATE -DPROJECT_VERSION="${PROJECT_VERSION}")

target_include_directories(yasd
	PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(yasd
	Qt5::Widgets
	Qt5::Gui
)
