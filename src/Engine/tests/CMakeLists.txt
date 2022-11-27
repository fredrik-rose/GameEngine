add_executable(CameraTests camera_tests.c)
add_executable(CoordinateSystemTransformationsTests coordinate_system_transformations_tests.c)
add_executable(IlluminaitonTests illumination_tests.c)

target_link_libraries(CameraTests LINK_PUBLIC
    Base
    Engine
    LinearAlgebra
    TestFramework
)
target_link_libraries(CoordinateSystemTransformationsTests LINK_PUBLIC
    Base
    Engine
    LinearAlgebra
    TestFramework
)
target_link_libraries(IlluminaitonTests LINK_PUBLIC
    Base
    Engine
    TestFramework
)

add_test(NAME CameraTests COMMAND CameraTests)
add_test(NAME CoordinateSystemTransformationsTests COMMAND CoordinateSystemTransformationsTests)
add_test(NAME IlluminaitonTests COMMAND IlluminaitonTests)
