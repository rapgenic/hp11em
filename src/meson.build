subdir('nonpareil')

hp11em_sources = [
  'main.c',
  'window.c',
  'key.c',
  'application.c',
]

hp11em_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1'),
]

hp11em_link = [
  nonpareil
]

gnome = import('gnome')

hp11em_sources += gnome.compile_resources('hp11em-resources',
  'hp11em.gresource.xml',
  c_name: 'hp11em'
)

executable('hp11em', hp11em_sources,
  dependencies: hp11em_deps,
  link_with: hp11em_link,
  install: true,
)
