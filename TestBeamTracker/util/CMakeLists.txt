add_executable(printHits ./printHits)
#target_include_directories(printHits PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(printHits PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(printHits PUBLIC TestBeamTracker)
target_link_libraries(printHits PUBLIC ActsCore)
#target_link_libraries(printHits PRIVATE ${Boost_LIBRARIES})
install(TARGETS printHits RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(printGeometry ./printGeometry)
#target_include_directories(printGeometry PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(printGeometry PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(printGeometry PUBLIC TestBeamTracker)
target_link_libraries(printGeometry PUBLIC ActsCore)
#target_link_libraries(printGeometry PRIVATE ${Boost_LIBRARIES})
install(TARGETS printGeometry RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(testKalmanFilter ./testKalmanFilter)
#target_include_directories(testKalmanFilter PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(testKalmanFilter PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(testKalmanFilter PUBLIC TestBeamTracker)
target_link_libraries(testKalmanFilter PUBLIC ActsCore)
#target_link_libraries(testKalmanFilter PRIVATE ${Boost_LIBRARIES})
install(TARGETS testKalmanFilter RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

