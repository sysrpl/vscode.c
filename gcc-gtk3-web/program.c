#include <string.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

static void on_entry_activate(GtkEntry *entry, gpointer user_data)
{
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(user_data);
    const gchar *input_url = gtk_entry_get_text(entry);

    if (!strstr(input_url, "://"))
    {
        gchar *formatted_url = g_strdup_printf("https://%s", input_url);
        webkit_web_view_load_uri(web_view, formatted_url);
        g_free(formatted_url);
    }
    else
    {
        webkit_web_view_load_uri(web_view, input_url);
    }
}

static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    if ((event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_l)) {
        GtkWidget *widget = GTK_WIDGET(user_data);
        gtk_widget_grab_focus(widget);
        return TRUE;
    }
    if ((event->state & GDK_CONTROL_MASK) && (event->keyval == GDK_KEY_F5)) {
        WebKitWebView *web_view = WEBKIT_WEB_VIEW(widget);
        webkit_web_view_reload_bypass_cache(web_view);
        return TRUE;
    }
    return FALSE;
}

static void on_back_button_clicked(GtkButton *button, gpointer user_data)
{
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(user_data);
    webkit_web_view_go_back(web_view);
}

static void on_forward_button_clicked(GtkButton *button, gpointer user_data)
{
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(user_data);
    webkit_web_view_go_forward(web_view);
}

static void update_navigation_buttons(
    WebKitWebView *web_view, GtkWidget *back_button, GtkWidget *forward_button)
{
    gtk_widget_set_sensitive(back_button, webkit_web_view_can_go_back(web_view));
    gtk_widget_set_sensitive(forward_button, webkit_web_view_can_go_forward(web_view));
}

static void on_web_view_load_changed(
    WebKitWebView *web_view, WebKitLoadEvent load_event, gpointer user_data)
{
    GtkEntry *url_entry = GTK_ENTRY(((gpointer *)user_data)[0]);
    GtkWidget *back_button = GTK_WIDGET(((gpointer *)user_data)[1]);
    GtkWidget *forward_button = GTK_WIDGET(((gpointer *)user_data)[2]);

    if (load_event == WEBKIT_LOAD_COMMITTED)
    {
        const gchar *url = webkit_web_view_get_uri(web_view);
        gtk_entry_set_text(url_entry, url);
        update_navigation_buttons(web_view, back_button, forward_button);
    }
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *header_bar = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);

    GtkWidget *back_button =
        gtk_button_new_from_icon_name("go-previous-symbolic", GTK_ICON_SIZE_BUTTON);
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), back_button);

    GtkWidget *forward_button =
        gtk_button_new_from_icon_name("go-next-symbolic", GTK_ICON_SIZE_BUTTON);
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), forward_button);

    GtkWidget *url_entry = gtk_entry_new();
    gtk_header_bar_set_custom_title(GTK_HEADER_BAR(header_bar), url_entry);
    gtk_widget_set_hexpand(url_entry, TRUE);

    // CSS for the appplication
    const gchar *css =
        ".circular {"
        "  border-radius: 16px;"
        "  padding: 4px 4px;"
        "}"
        ".indented {"
        "  padding-left: 10px;"
        "}";

    // Load and apply the CSS to a provider
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    GtkStyleContext *context;

    // Apply the style to the back button
    context = gtk_widget_get_style_context(back_button);
    gtk_style_context_add_provider(
        context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_style_context_add_class(context, "circular");

    // Apply the style to the forward button
    context = gtk_widget_get_style_context(forward_button);
    gtk_style_context_add_provider(
        context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_style_context_add_class(context, "circular");

    // Apply the style to the forward button
    context = gtk_widget_get_style_context(url_entry);
    gtk_style_context_add_provider(
        context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_style_context_add_class(context, "circular");
    gtk_style_context_add_class(context, "indented");

    // Cleanup the css provider
    g_object_unref(provider);

    WebKitWebView *web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(web_view));

    g_signal_connect(url_entry, "activate", G_CALLBACK(on_entry_activate), web_view);
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_button_clicked), web_view);
    g_signal_connect(forward_button, "clicked", G_CALLBACK(on_forward_button_clicked), web_view);

    gpointer user_data[] = {url_entry, back_button, forward_button};
    g_signal_connect(web_view, "load-changed", G_CALLBACK(on_web_view_load_changed), user_data);
    g_signal_connect(web_view, "key-press-event", G_CALLBACK(on_key_press), url_entry);

    webkit_web_view_load_uri(web_view, "https://www.reddit.com");

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}