#include <gnome-software.h>

#include "gs-plugin-qubes.h"


struct _GsPluginQubes {
	GsPlugin	 parent;
};

G_DEFINE_TYPE (GsPluginQubes, gs_plugin_qubes, GS_TYPE_PLUGIN)

static void
gs_plugin_qubes_init (GsPluginQubes *self)
{
	GsPlugin *plugin = GS_PLUGIN (self);

	gs_plugin_add_rule (plugin, GS_PLUGIN_RULE_RUN_AFTER, "appstream");
	gs_plugin_add_rule (plugin, GS_PLUGIN_RULE_RUN_AFTER, "packagekit");
	gs_plugin_add_rule (plugin, GS_PLUGIN_RULE_RUN_AFTER, "flatpak");
    gs_plugin_add_rule (plugin, GS_PLUGIN_RULE_RUN_BEFORE, "icons");
}

// NOTE: Debian and Fedora may run different plugin API versions
#if GS_PLUGIN_API >= 23
#define GS_REFINE_ASYNC_EXTRA_ARGS GsPluginRefineRequireFlags require_flags, \
 GsPluginEventCallback event_callback, \
 void *event_user_data,
#else
#define GS_REFINE_ASYNC_EXTRA_ARGS
#endif

static void
gs_plugin_qubes_refine_async (
	GsPlugin				*plugin,
	GsAppList				*list,
	GsPluginRefineFlags		 flags,
	GS_REFINE_ASYNC_EXTRA_ARGS
	GCancellable			*cancellable,
	GAsyncReadyCallback		 callback,
	gpointer				 user_data
)
{
	g_autoptr(GTask) task = NULL;

	task = g_task_new (plugin, cancellable, callback, user_data);
	g_task_set_source_tag (task, gs_plugin_qubes_refine_async);

	for (guint i = 0; i < gs_app_list_length (list); i++) {
		GsApp *app = gs_app_list_index (list, i);

		/* not valid */
		if (gs_app_get_id (app) == NULL)
			continue;

		gs_app_add_quirk (app, GS_APP_QUIRK_NOT_LAUNCHABLE);

        gs_app_remove_kudo (app, GS_APP_KUDO_HAS_SCREENSHOTS);

        GPtrArray *screenshots = gs_app_get_screenshots (app);
        g_ptr_array_set_size (screenshots, 0);

	}

	g_task_return_boolean (task, TRUE);
}

static gboolean
gs_plugin_qubes_refine_finish (
	GsPlugin      *plugin,
    GAsyncResult  *result,
    GError       **error
)
{
	return g_task_propagate_boolean (G_TASK (result), error);
}

static void
gs_plugin_qubes_class_init (GsPluginQubesClass *klass)
{
	GsPluginClass *plugin_class = GS_PLUGIN_CLASS (klass);

	plugin_class->refine_async = gs_plugin_qubes_refine_async;
	plugin_class->refine_finish = gs_plugin_qubes_refine_finish;
}

GType
gs_plugin_query_type (void)
{
	return GS_TYPE_PLUGIN_QUBES;
}
