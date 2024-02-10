nonpareil_sources = [
	'proc.c',
	'proc_classic.c',
	'proc_nut.c',
	'proc_woodstock.c',
	'helios.c',
	'phineas.c',
	'mod1_file.c',
	'util.c',
	'arch.c',
	'model.c',
	'glib_async_queue_source.c',
	'digit_ops.c',
	'helios_chargen.c',
	'dis_nut.c',
	'coconut_lcd.c',
	'dis_woodstock.c',
	'platform.c',
	'release.c'
]

nonpareil_deps = [
	dependency('glib-2.0')
]

nonpareil = shared_library('nonpareil', nonpareil_sources,
	dependencies: nonpareil_deps,
	install: true
)