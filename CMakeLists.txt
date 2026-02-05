cmake_minimum_required(VERSION 3.10)
project(InventoryManagementSystem)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)

add_executable(ims
    src/main.cpp

    src/database/Database.cpp

    src/repository/ProductRepository.cpp
    src/repository/StockRepository.cpp
    src/repository/TransactionRepository.cpp

    src/services/InventoryService.cpp
    src/services/ReportService.cpp
)

target_include_directories(ims PRIVATE src)
target_link_libraries(ims SQLite::SQLite3)

# Ensure data directory exists (SQLite will create DB file, not folders)
add_custom_command(TARGET ims POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    "${CMAKE_SOURCE_DIR}/data"
)

