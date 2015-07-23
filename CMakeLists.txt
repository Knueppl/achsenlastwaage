cmake_minimum_required(VERSION 2.8)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(FORM_DIR ${CMAKE_SOURCE_DIR}/form)
set(PIC_DIR ${CMAKE_SOURCE_DIR}/picture)

find_package(Qt4 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(QT_USE_QTSQL TRUE)
set(QT_USE_QTWEBKIT TRUE)
set(QT_USE_QTXMLPATTERNS TRUE)

include(${QT_USE_FILE})
include_directories(${QT_QTSQL_INCLUDE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${SRC_DIR}
                    )

set(MOC_HEADERS ${SRC_DIR}/SupplierDialog.h
                ${SRC_DIR}/CreateVehicleDialog.h
                ${SRC_DIR}/MainWindow.h
                ${SRC_DIR}/DatabaseDialog.h
                ${SRC_DIR}/Scale.h
                ${SRC_DIR}/DummyScale.h
                ${SRC_DIR}/DummyScaleWidget.h
                ${SRC_DIR}/GoodsDialog.h
                ${SRC_DIR}/SupplierDialog.h
                ${SRC_DIR}/FieldDialog.h
                )

qt4_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

qt4_wrap_ui(MOC_FORMS
            ${FORM_DIR}/CreateVehicleDialog.ui
            ${FORM_DIR}/MainWindow.ui
            ${FORM_DIR}/DatabaseDialog.ui
            ${FORM_DIR}/CreateTextDialog.ui
            ${FORM_DIR}/DummyScaleWidget.ui
            ${FORM_DIR}/DatabaseCombo.ui
            )

qt4_add_resources(RESOURCES
                  ${PIC_DIR}/resource.qrc
                  )

set(SRC ${SRC_DIR}/SupplierDialog.cpp
        ${SRC_DIR}/Database.cpp
        ${SRC_DIR}/CreateVehicleDialog.cpp
        ${SRC_DIR}/MainWindow.cpp
        ${SRC_DIR}/DatabaseDialog.cpp
        ${SRC_DIR}/CreateTextDialog.cpp
        ${SRC_DIR}/Scale.cpp
        ${SRC_DIR}/DummyScale.cpp
        ${SRC_DIR}/DummyScaleWidget.cpp
        ${SRC_DIR}/Weighting.cpp
        ${SRC_DIR}/GoodsDialog.cpp
        ${SRC_DIR}/SupplierDialog.cpp
        ${SRC_DIR}/FieldDialog.cpp
        ${SRC_DIR}/VehicleButton.cpp
        ${SRC_DIR}/achsenlastwaage.cpp
        ${RESOURCES}
        ${MOC_SOURCES}
        ${MOC_FORMS}
        )

add_executable(achenlastwaage ${SRC})

target_link_libraries(achenlastwaage
                      ${QT_LIBRARIES}
                      ${QT_QTSQL_LIBRARIES}
                      )
