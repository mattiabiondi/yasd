set(yasd_SRCS
	main.cpp
	configuration.cpp
	application.cpp
	gui/main_window.cpp
	gui/tabs/config_tab.cpp
	gui/wizards/new_wizard.cpp
	gui/wizards/pages/cars_page.cpp
	gui/wizards/pages/map_page.cpp
	gui/dialogs/cars_dialog.cpp
	gui/dialogs/map_dialog.cpp
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
