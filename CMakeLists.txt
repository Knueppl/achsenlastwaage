cmake_minimum_required(VERSION 2.8)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(FORM_DIR ${CMAKE_SOURCE_DIR}/form)

find_package(Qt4 REQUIRED)

set(QT_USE_QTSQL TRUE)
set(QT_USE_QTWEBKIT TRUE)
set(QT_USE_QTXMLPATTERNS TRUE)

include(${QT_USE_FILE})
include_directories(${QT_QTSQL_INCLUDE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    )

set(MOC_HEADERS ${SRC_DIR}/axis_view.h
                ${SRC_DIR}/fzw12.h
                ${SRC_DIR}/camera.h
                ${SRC_DIR}/control.h
                ${SRC_DIR}/plot_weights.h
                ${SRC_DIR}/vehicle_manager.h
                ${SRC_DIR}/weight_list.h
                ${SRC_DIR}/SupplierDialog.h
                ${SRC_DIR}/ProductDialog.h
                ${SRC_DIR}/CreateVehicleDialog.h
                )

qt4_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

qt4_wrap_ui(MOC_FORMS
            ${FORM_DIR}/CreateVehicleDialog.ui
            )

set(SRC ${SRC_DIR}/axis_items.cpp
        ${SRC_DIR}/axis_view.cpp
        ${SRC_DIR}/camera.cpp
        ${SRC_DIR}/control.cpp
        ${SRC_DIR}/fzw12.cpp
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/plot_weights.cpp
        ${SRC_DIR}/vehicle_manager.cpp
        ${SRC_DIR}/weight_list.cpp
        ${SRC_DIR}/weight_note.cpp
        ${SRC_DIR}/SupplierDialog.cpp
        ${SRC_DIR}/ProductDialog.cpp
        ${SRC_DIR}/Database.cpp
        ${SRC_DIR}/CreateVehicleDialog.cpp
        ${MOC_SOURCES}
        ${MOC_FORMS}
        )

add_executable(achenlastwaage ${SRC})

target_link_libraries(achenlastwaage
                      ${QT_LIBRARIES}
                      ${QT_QTSQL_LIBRARIES}
                      )
