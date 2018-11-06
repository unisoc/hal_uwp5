if(CONFIG_HAS_UWP)
	add_subdirectory_ifdef(CONFIG_SIPC drivers/src/sipc)
	zephyr_include_directories(
		drivers/include
		soc
		)
	zephyr_sources(soc/system.c)
	zephyr_sources_ifdef(CONFIG_USE_UWP_HAL_CACHE soc/cache.c)
	zephyr_sources_ifdef(CONFIG_USE_UWP_HAL_GNSS soc/gnss.c)
	zephyr_sources_ifdef(CONFIG_USE_UWP_HAL_FW soc/load_fw.c)

	zephyr_sources_ifdef(CONFIG_USE_UWP_HAL_SFC drivers/src/hal_sfc_phy.c)
	zephyr_sources_ifdef(CONFIG_USE_UWP_HAL_SFC drivers/src/hal_sfc.c)
endif()
