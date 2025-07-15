cmake_minimum_required(VERSION 3.10)
project(HFT_Simulator)

set(CMAKE_CXX_STANDARD 17)

add_library(HFT
    src/OrderBook.cpp
    src/MatchingEngine.cpp
    src/MarketDataFeed.cpp
)

target_include_directories(HFT PUBLIC src)

add_executable(simulator src/main.cpp)
target_link_libraries(simulator HFT)

