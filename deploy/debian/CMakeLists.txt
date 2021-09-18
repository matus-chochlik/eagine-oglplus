# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
execute_process(
	COMMAND ${DPKG_ARCHITECTURE_COMMAND} --query DEB_BUILD_ARCH
	OUTPUT_VARIABLE PKG_ARCH
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
	COMMAND ${DPKG_ARCHITECTURE_COMMAND} --query DEB_BUILD_MULTIARCH
	OUTPUT_VARIABLE PKG_MULTIARCH
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(PKG_VERSION ${EAGINE_VERSION})
set(PKG_NAME "eagine-oglplus-dev_${EAGINE_VERSION}-1_${PKG_ARCH}")
set(PKG_DIR "${CMAKE_CURRENT_BINARY_DIR}/${PKG_NAME}")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set(BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/../..")
set(PKG_PREFIX "${PKG_DIR}/usr")

get_target_property(PKG_HEADERS eagine-oglplus-headers PUBLIC_HEADER)

file(GENERATE OUTPUT build-pkg-cfg INPUT build-pkg-cfg.in)
configure_file(pkg-headers.txt.in pkg-headers.txt @ONLY)
configure_file(build-pkg.sh.in build-pkg.sh @ONLY)

add_custom_command(
	OUTPUT "${PKG_DIR}/DEBIAN/control"
	COMMAND ${BASH_COMMAND}
	ARGS "${CMAKE_CURRENT_BINARY_DIR}/build-pkg.sh"
	DEPENDS eagine-oglplus
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	COMMENT "Copying files for ${PKG_NAME}.deb package"
)

add_custom_command(
	OUTPUT ${PKG_NAME}.deb
	COMMAND ${DPKG_DEB_COMMAND}
	ARGS --build --root-owner-group ${PKG_NAME}
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	DEPENDS "${PKG_DIR}/DEBIAN/control"
	COMMENT "Building ${PKG_NAME}.deb package"
)

add_custom_target(
	eagine-oglplus-deb
	DEPENDS ${PKG_NAME}.deb eagine-core-deb eagine-shapes-deb

)
install(
	FILES "${CMAKE_CURRENT_BINARY_DIR}/${PKG_NAME}.deb"
	DESTINATION opt/eagine/debian/
	COMPONENT deb-packages
	EXCLUDE_FROM_ALL
	OPTIONAL
)

