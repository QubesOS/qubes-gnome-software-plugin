project(
  'gnome-software-plugin-qubes',
  'c',
  version: '1.0.0',
  meson_version: '>= 1.0.0',
)

# Dependencies
gnome_software_dep = dependency('gnome-software')
glib_dep = dependency('glib-2.0')
gobject_dep = dependency('gobject-2.0')
gio_dep = dependency('gio-2.0')
gsettings_desktop_schemas = dependency('gsettings-desktop-schemas')

gs_plugin_dir = gnome_software_dep.get_variable('plugindir')
gs_plugin_api_version = gs_plugin_dir.split('plugins-')[-1].to_int()

cargs = [
  '-DG_LOG_DOMAIN="GsPluginQubes"',
  '-DI_KNOW_THE_GNOME_SOFTWARE_API_IS_SUBJECT_TO_CHANGE',
  '-DGS_PLUGIN_API=@0@'.format(gs_plugin_api_version),
]

plugin_qubes_lib = shared_library(
  'gs_plugin_qubes',
  sources : 'src/gs-plugin-qubes/gs-plugin-qubes.c',
  install : true,
  install_dir: gs_plugin_dir,
  c_args : cargs,
  dependencies : [gnome_software_dep, glib_dep, gobject_dep, gio_dep, gsettings_desktop_schemas],
)

install_data(
  'data/org.gnome.Software.Plugin.Qubes.metainfo.xml',
  install_dir: join_paths(get_option('datadir'), 'metainfo'),
)