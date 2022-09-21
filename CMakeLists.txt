cmake_minimum_required(VERSION 3.23)
project(SparkFun_AutoDriver_Arduino_Library_Improved)

set(CMAKE_CXX_STANDARD 14)

include_directories(examples)
include_directories(examples/gantry)
include_directories(examples/SparkFundSPINexample)
include_directories(examples/SparkFunGetSetParamTest)
include_directories(examples/SparkFunLibraryTest)
include_directories(examples/autoDriverMultiboardTest)
include_directories(src)

add_executable(SparkFun_AutoDriver_Arduino_Library_Improved
        examples/gantry/gantry.ino
        examples/SparkFundSPINexample/SparkFundSPINcommands.ino
        examples/SparkFundSPINexample/SparkFundSPINexample.ino
        examples/SparkFundSPINexample/SparkFundSPINsupport.ino
        examples/SparkFundSPINexample/SparkFunL6470.h
        examples/SparkFunGetSetParamTest/SparkFunGetSetParamTest.ino
        examples/SparkFunLibraryTest/SparkFunLibraryTest.ino
        examples/SparkFunLibraryTest/SparkFunnotes.h
        examples/SparkFunLibraryTest/SparkFunsupportFunctions.ino
        examples/SparkFunLibraryTest/SparkFunwantYouGone.ino
        examples/autoDriverMultiboardTest/autoDriverMultiboardTest.ino
        src/SparkFunAutoDriver.cpp
        src/SparkFunAutoDriver.h
        src/SparkFunAutoDriverCommands.cpp
        src/SparkFunAutoDriverConfig.cpp
        src/SparkFunAutoDriverSupport.cpp
        src/SparkFundSPINConstants.h)
