#ifndef __EXAMPLEAPPPREFS_H
#define __EXAMPLEAPPPREFS_H

#include "exampleappwin.h"
#include <gtk/gtk.h>

#define EXAMPLE_APP_PREFS_TYPE (example_app_prefs_get_type())
G_DECLARE_FINAL_TYPE(ExampleAppPrefs, example_app_prefs, EXAMPLE, APP_PREFS, GtkDialog)

ExampleAppPrefs *example_app_prefs_new(ExampleAppWindow *win);

#endif /* __EXAMPLEAPPPREFS_H */
