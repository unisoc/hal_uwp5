zephyr_include_directories(.)

zephyr_sources_ifdef(CONFIG_BT_UWP5661	sipc.c)
zephyr_sources_ifdef(CONFIG_BT_UWP5661	uki_config.c)
zephyr_sources_ifdef(CONFIG_BT_UWP5661	uki_utlis.c)
zephyr_sources_ifdef(CONFIG_BT_UWP5661	uwp5661.c)

