add_executable(${PROJECT_NAME}
	main.cpp
	configuration.cpp
	application.cpp
	input.cpp
	utils.cpp
	windows/main_window.cpp
	windows/track_window.cpp
	windows/track/track.cpp
	windows/cars/car.cpp
	tabs/config_tab.cpp
	tabs/track_tab.cpp
	tabs/track_tab0.cpp
	wizards/new_wizard.cpp
	wizards/pages/cars_page.cpp
	wizards/pages/track_page.cpp
	dialogs/cars_dialog.cpp
	dialogs/track_dialog.cpp
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
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
