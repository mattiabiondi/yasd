add_executable(${PROJECT_NAME}
	main.cpp
	configuration.cpp
	session.cpp
	application.cpp
	input.cpp
	utils.cpp
	windows/main_window.cpp
	widgets/track_widget.cpp
	widgets/track/track.cpp
	widgets/cars/car.cpp
	dialogs/config_dialog.cpp
	wizards/new_wizard.cpp
	wizards/pages/cars_page.cpp
	wizards/pages/track_page.cpp
	dialogs/cars_dialog.cpp
	dialogs/track_dialog.cpp
	dialogs/config_dialog.cpp
	dialogs/charts_dialog.cpp
	genetic_algorithm/dna.cpp
	genetic_algorithm/genetic_algorithm_methods.cpp
	neural_network/neural_network.cpp
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE -DPROJECT_VERSION="${PROJECT_VERSION}")

target_include_directories(${PROJECT_NAME}
	PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
	Qt5::Widgets
	Qt5::Gui
	Qt5::Charts
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
