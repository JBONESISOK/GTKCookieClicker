#include <gtk/gtk.h>

typedef struct
{
    GtkWidget *counterlabel;
    int count;
} app_widgets;
void clicked_btn(GtkButton *button, app_widgets *app_widgets)
{
    app_widgets->count++;

    char text[20];
    sprintf(text, "Clicked: %d", app_widgets->count);
    gtk_label_set_text(GTK_LABEL(app_widgets->counterlabel), text);
}
int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    GtkWidget *window;
    app_widgets *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/window_main.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_window_set_title(GTK_WINDOW(window), "Cookie Clicker");
    widgets->counterlabel = GTK_WIDGET(gtk_builder_get_object(builder, "counterlabel"));
    gtk_label_set_text(GTK_LABEL(widgets->counterlabel), "Clicked: 0");
    widgets->count = 0;
    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();
    g_slice_free(app_widgets, widgets);
    return 0;
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
