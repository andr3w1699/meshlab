# Copyright 2019-2020, Collabora, Ltd.
# SPDX-License-Identifier: BSL-1.0

# MeshLab Plugin for ReebHanTun

set(SOURCES filter_reebhanthun.cpp)
set(HEADERS filter_reebhanthun.h)

add_meshlab_plugin(filter_reebhanthun ${SOURCES} ${HEADERS})

target_link_libraries(filter_reebhanthun PRIVATE ${Boost_LIBRARIES} ${CGAL_LIBRARIES})
