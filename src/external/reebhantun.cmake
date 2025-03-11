# Opzione per abilitare il download
option(ALLOW_DOWNLOAD_REEBHANTUN "Allow download of ReebHanTun source" ON)

if(ALLOW_DOWNLOAD_REEBHANTUN)
	# Directory di destinazione per il download
	set(REEBHANTUN_DIR "${MESHLAB_EXTERNAL_DOWNLOAD_DIR}/ReebHanTun-main")
	set(REEBHANTUN_CHECK "${REEBHANTUN_DIR}/vcgtest/main.cpp")  # Usa il file main.cpp come controllo
	set(ANN_CHECK "${REEBHANTUN_DIR}/ann/ANN/ANN.cpp")  # Usa il file ANN.cpp come controllo

	# Controlla se il file di verifica esiste
	if (NOT EXISTS ${REEBHANTUN_CHECK})
		# Link per scaricare lo zip da GitHub
		set(REEBHANTUN_LINK
			https://github.com/andr3w1699/ReebHanTun/archive/refs/heads/main.zip)

		# Funzione di download e decompressione
		download_and_unzip(
			NAME "ReebHanTun"
			LINK ${REEBHANTUN_LINK}
			DIR ${MESHLAB_EXTERNAL_DOWNLOAD_DIR})

		# Verifica se il download è riuscito
		if (NOT download_and_unzip_SUCCESS)
			message(STATUS "- ReebHanTun - download failed.")
		endif()
	endif()	
	if (NOT EXISTS ${ANN_CHECK})
			# Link per scaricare lo zip da GitHub
			set(ANN_LINK
				https://github.com/michaelquigley/ann/archive/refs/heads/master.zip)
			# Funzione di download e decompressione
			download_and_unzip(
				NAME "ANN"
				LINK ${ANN_LINK}
				DIR ${MESHLAB_EXTERNAL_DOWNLOAD_DIR}/ReebHanTun-main)
			file(RENAME ${MESHLAB_EXTERNAL_DOWNLOAD_DIR}/ReebHanTun-main/ann-master  ${MESHLAB_EXTERNAL_DOWNLOAD_DIR}/ReebHanTun-main/ann)
			# Verifica se il download è riuscito
			if (NOT download_and_unzip_SUCCESS)
				message(STATUS "- ANN - download failed.")
			endif()
		endif()
	

	# Se il file esiste, aggiunge la directory e imposta la libreria
	if(EXISTS ${REEBHANTUN_CHECK})
		message(STATUS "- ReebHanTun - using downloaded source")
		# TO DO al momento la repo ReebHanTun è scaricata ma "sganciata"
		# add_subdirectory(${REEBHANTUN_DIR})
		#add_library(external-reebhantun INTERFACE)
		#target_link_libraries(external-reebhantun INTERFACE reeb-hantun)
	endif()
endif()
