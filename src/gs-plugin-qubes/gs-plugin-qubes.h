#pragma once

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define GS_TYPE_PLUGIN_QUBES (gs_plugin_qubes_get_type ())

G_DECLARE_FINAL_TYPE (GsPluginQubes, gs_plugin_qubes, GS, PLUGIN_QUBES, GsPlugin)

G_END_DECLS
