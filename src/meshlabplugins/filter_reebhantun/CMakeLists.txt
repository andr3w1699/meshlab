# Copyright 2019-2020, Collabora, Ltd.
# SPDX-License-Identifier: BSL-1.0
if (TARGET external-boost AND TARGET external-cgal AND TARGET external-libigl)

# MeshLab Plugin for ReebHanTun
message("Building ReebHanTun plugin")

set(RHTDIR ../../external/downloads/ReebHanTun-main/src)
set(SOURCES filter_reebhanthun.cpp)
set(HEADERS filter_reebhanthun.h)
set(ANNDIR ../../external/downloads/ReebHanTun-main/ann/ANN)
# Add as include search directory the directory where the ReebHanTun sources are located
include_directories(${RHTDIR})
include_directories(${RHTDIR}/../ann)
set (CMAKE_CXX_STANDARD 11)
set(REEB_SOURCES 
	${RHTDIR}/CycleOptimization/Annotation/Annotated_polyhedron_3.h
	${RHTDIR}/CycleOptimization/Annotation/Annotated_polyhedron_items_3.h
	${RHTDIR}/CycleOptimization/Annotation/AnnotationComputation.h
	${RHTDIR}/CycleOptimization/Annotation/AnnotationComputation.cpp
	${RHTDIR}/CycleOptimization/Annotation/HalfedgeDS_annotated_face_base.h
	${RHTDIR}/CycleOptimization/Annotation/HalfedgeDS_annotated_halfedge_base.h
	${RHTDIR}/CycleOptimization/Annotation/HalfedgeDS_annotated_vertex_base.h
	${RHTDIR}/CycleOptimization/Annotation/Polyhedron_annotator_3.h
	${RHTDIR}/CycleOptimization/ShortCycles.cpp
	${RHTDIR}/CycleOptimization/SimpleGraph.h
	${RHTDIR}/CycleOptimization/canonical_loops.h 
	${RHTDIR}/CycleOptimization/canonical_loops.cpp
	${RHTDIR}/CycleOptimization/DijkstraAlgorithm.h 
	${RHTDIR}/CycleOptimization/DijkstraAlgorithm.cpp
	${RHTDIR}/CycleOptimization/edge_annotations_gauss.h 
	${RHTDIR}/CycleOptimization/edge_annotations_gauss.cpp
	${RHTDIR}/CycleOptimization/FibonacciHeap.h 
	${RHTDIR}/CycleOptimization/FibonacciHeap.cpp
	${RHTDIR}/AdjListGraph.cpp
	${RHTDIR}/AdjListGraph.h
	${RHTDIR}/ANNSearch.h
	${RHTDIR}/ANNSearch.cpp
	${RHTDIR}/FilesOutputForOptimalCycles.cpp
	${RHTDIR}/FilesOutputForOptimalCycles.h
	${RHTDIR}/Graph_max_tree.h
	${RHTDIR}/IntersectionOnMesh.h
	${RHTDIR}/IntersectionOnMesh.cpp
	${RHTDIR}/InverseLinkNumberMatrix.h
	${RHTDIR}/InverseLinkNumberMatrix.cpp
	${RHTDIR}/LinkNumberComputing.cpp
	${RHTDIR}/LinkNumberComputing.h
	${RHTDIR}/MapLoopsBackToMeshLevelSetAndArc.cpp
	${RHTDIR}/MapLoopsBackToMeshLevelSetAndArc.h
	${RHTDIR}/NonOverlappedLevelCycleAndArc.cpp
	${RHTDIR}/NonOverlappedLevelCycleAndArc.h
	${RHTDIR}/NonOverlappingCycles.cpp
	${RHTDIR}/NonOverlappingCycles.h
	${RHTDIR}/psbmReebGraph.cpp
	${RHTDIR}/psbmReebGraph.h
	${RHTDIR}/psbmReebGraphElements.h
	${RHTDIR}/ReebGraphPairing.cpp
	${RHTDIR}/ReebGraphPairing.h
	${RHTDIR}/SegmentIntersection.h
	${RHTDIR}/SegmentIntersection.cpp
	${RHTDIR}/SegmentPairIntersection.cpp
	${RHTDIR}/SimpleMesh.cpp
	${RHTDIR}/SimpleMesh.h 
	${RHTDIR}/UniqueDirection.cpp
	${RHTDIR}/UniqueDirection.h 
	${RHTDIR}/RenderVector3.h
	${ANNDIR}/ANN.cpp
	${ANNDIR}/ANN.h
	${ANNDIR}/ANNperf.h
	${ANNDIR}/ANNx.h
	${ANNDIR}/bd_fix_rad_search.cpp
	${ANNDIR}/bd_pr_search.cpp
	${ANNDIR}/bd_search.cpp
	${ANNDIR}/bd_tree.cpp
	${ANNDIR}/bd_tree.h
	${ANNDIR}/brute.cpp
	${ANNDIR}/kd_dump.cpp
	${ANNDIR}/kd_fix_rad_search.cpp
	${ANNDIR}/kd_fix_rad_search.h
	${ANNDIR}/kd_pr_search.cpp
	${ANNDIR}/kd_pr_search.h
	${ANNDIR}/kd_search.cpp
	${ANNDIR}/kd_search.h
	${ANNDIR}/kd_split.cpp
	${ANNDIR}/kd_split.h
	${ANNDIR}/kd_tree.cpp
	${ANNDIR}/kd_tree.h
	${ANNDIR}/kd_util.cpp
	${ANNDIR}/kd_util.h
	${ANNDIR}/perf.cpp
	${ANNDIR}/pr_queue.h
	${ANNDIR}/pr_queue_k.h
)

add_meshlab_plugin(filter_reebhanthun ${SOURCES} ${REEB_SOURCES} ${HEADERS})

target_link_libraries(filter_reebhanthun PRIVATE external-boost external-cgal)
else()
	message(
		STATUS "Skipping filter_reebhantun - don't know about boost, cgal or libann on this system.")
endif()





# #set(CMAKE_CXX_FLAGS "-lboost_program_options")
# include_directories( ${CMAKE_SOURCE_DIR}/src "${CMAKE_SOURCE_DIR}/src/include" "${CMAKE_SOURCE_DIR}/src/CycleOptimization" "${CMAKE_SOURCE_DIR}/src/CycleOptimization/Annotation" "${CMAKE_SOURCE_DIR}/ann/") 
# link_directories( ${CMAKE_SOURCE_DIR}/src/lib) 
# # ADD library directory for ANN lib
# link_directories( ${CMAKE_SOURCE_DIR}/ANN/lib)

# # Boost
# find_package( Boost 1.40 COMPONENTS program_options system REQUIRED )
# include_directories( ${Boost_INCLUDE_DIRS} )
# link_directories(${Boost_LIBRARY_DIRS})

# # CGAL
# find_package( CGAL REQUIRED )
# message("CGAL version: ${CGAL_VERSION}")
# message("CGAL_USE_FILE: ${CGAL_USE_FILE}")
# include( ${CGAL_USE_FILE} )

# # Usa FetchContent per scaricare la libreria ANN
# include(FetchContent)

# FetchContent_Declare(
#     ann
#     GIT_REPOSITORY https://github.com/michaelquigley/ann.git
#     GIT_TAG master  # Puoi specificare un tag specifico se necessario
# )

# # Scarica e costruisci la libreria ANN
# FetchContent_MakeAvailable(ann)

# # Usa FetchContent per scaricare la libreria VCG
# FetchContent_Declare(
#     vcglib
#     GIT_REPOSITORY https://github.com/cnr-isti-vclab/vcglib.git
#     GIT_TAG devel  # Puoi specificare un tag specifico se necessario
# )

# # Scarica e costruisci la libreria VCG
# FetchContent_MakeAvailable(vcglib)

# target_link_libraries(
# 	vcgtest
# 	PUBLIC
# 		${Boost_LIBRARIES} 
# 		boost_system 
# 		boost_program_options 
# 		ann
# 		vcglib  
# 	)
# include_directories(../build/_deps/ann-src)
# include_directories(../build/_deps/vcglib-src)


