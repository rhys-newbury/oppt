include(${CMAKE_CURRENT_LIST_DIR}/../shared/RRTConnect/CMakeLists.txt)
set(RRT_HEURISTIC_PLUGIN_SRC
    ${CMAKE_CURRENT_LIST_DIR}/CarMazeRRTHeuristicPlugin.cpp ${RRT_CONNECT_SRC})
add_heuristic_plugin(CarMazeRRTHeuristicPlugin "${RRT_HEURISTIC_PLUGIN_SRC}")
