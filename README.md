# Motorless Aicraft Firmware (временное название)
...
## Добавлениие нового модуля
1. В папке **Modules** создается новая папка. В данной папке модуля создается **CMakeLists.txt**:
    ```cmake
    cmake_minimum_required(VERSION 3.22)

    add_library(example_module STATIC
        example_class.cpp
    

    target_include_directories(example_module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

    target_link_libraries(example_module PUBLIC stm32cubemx)
    target_link_libraries(example_module PUBLIC servo)
    target_link_libraries(example_module PUBLIC bmi088_legacy)
    target_link_libraries(example_module PUBLIC swo_debug)
    ```
    * ```add_library(example_module STATIC example_class.cpp)``` - создание библиотеки **example_module** и добавление к ней source файлов
    * ```target_include_directories(example_module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})``` - указание созданной библиотеке папок с хедерами. В данном примере используется сама папка модуля
    * ```target_link_libraries(example_module PUBLIC stm32cubemx)``` - добавление зависимсостей для данной библиотеки.
      * **stm32cubemx** - библиотека, которая содержит все базовые функции stm32
      * **servo** - библиотека для управления сервоприводами
      * **bmi088_legacy** - библиотека для IMU датчика bmi088 (версия библиотеки на СИ)
      * **swo_debug** - библиотека для вывода текста в терминал через программатор
2. В **CMakeLists.txt** в **корне** проекта:
    * В ```target_link_libraries(${CMAKE_PROJECT_NAME}``` добавляется название модуля
    * Через ```add_subdirectory``` добавляется путь к папке модуля, где лежит **CMakeLists.txt** самого модуля.
3. Добавление другим модулям зависимости от созданного модуля:
    * В **CMakeLists.txt** любого модуля добавляется строчка вида: ```target_link_libraries(stm32cubemx PUBLIC  bmi088_legacy)```, где:
      * **stm32cubemx** -  название модуля, который зависит от другого
      * **example_module** - название модуля, от которого зависит другой
    * **main.cpp** относится к модулю stm32cubemx, его **CMakeLists.txt**: ```cmake/stm32cubemx/CMakeLists.txt```

Сейчас у всех модулей стоят спецификаторы **PUBLIC**. Как только кто-то лучше поймет CMake, поменяем на нужные. Сейчас из-за public бибилотека имеет доступ ко всем зависимостям библиотек, от которых сама зависит.