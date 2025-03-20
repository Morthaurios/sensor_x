cmake_minimum_required (VERSION 3.22)

project (Sensor_driver
    DESCRIPTION "Sensor driver"
    VERSION 1.0.0
    LANGUAGES C )

add_library(Sensor_driver)

target_sources( Sensor_driver PRIVATE
    Sensor.c
)

target_include_directories( Sensor_driver PUBLIC
    .
)

target_link_libraries( Sensor_driver PRIVATE
    Platform_Types
    I2C_driver
)