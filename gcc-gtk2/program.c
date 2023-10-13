#include <gtk/gtk.h>

void on_button_clicked(GtkWidget *widget, gpointer data)
{
    // Get the text from the text entry widget
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(data));
    // Show a message dialog with the text
    GtkWidget *dialog = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", text);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void add_text_entry_and_button(GtkWidget *window)
{
    // Create a vertical box to hold the widgets
    GtkWidget *vbox = gtk_vbox_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    // Create a text entry widget
    GtkWidget *text_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), text_entry, FALSE, FALSE, 0);
    // Create a button widget
    GtkWidget *button = gtk_button_new_with_label("Submit");
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
    // Connect the "clicked" signal of the button to a callback function
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), text_entry);
}

int main(int argc, char *argv[])
{
    // Initialize GTK
    gtk_init(&argc, &argv);
    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "My GTK 2 App");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    // Set the window size to 400x300
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    // Set the window to be centered on my screen
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    // Add a text entry and a button to the main window
    add_text_entry_and_button(window);
    // Connect to the "destroy" signal of the main window
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Show the window and all of its widgets
    gtk_widget_show_all(window);
    // Start the main loop
    gtk_main();
    return EXIT_SUCCESS;
}
