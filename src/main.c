#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
struct Player
{
    int amount_clicked;
    double money;
    double multiplier;
} player;
typedef struct
{
    GtkWidget *counterlabel;
    GtkWidget *clickButton;
    GtkWidget *moneyLabel;
    GtkWidget *shopGrid;
    GtkWidget *shopGridArr[6];
} app_widgets;
void clicked_btn(GtkButton *button, app_widgets *app_widgets)
{
    char text[20];
    sprintf(text, "Clicked: %d", ++player.amount_clicked);
    player.money += 5 * player.multiplier;
    gtk_label_set_text(GTK_LABEL(app_widgets->counterlabel), text);
    sprintf(text, "Money: %.2f", player.money);
    gtk_label_set_text(GTK_LABEL(app_widgets->moneyLabel), text);
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
    widgets->clickButton = GTK_WIDGET(gtk_builder_get_object(builder, "clickbtn"));
    widgets->moneyLabel = GTK_WIDGET(gtk_builder_get_object(builder, "moneylabel"));
    player.amount_clicked = 0;
    player.money = 0.00;
    player.multiplier = 1;
    gtk_label_set_text(GTK_LABEL(widgets->counterlabel), "Clicked: 0");

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
