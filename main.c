#include "gtk_auto.h"
#include <gtk/gtk.h>

// funtion construct
static void activate (GtkApplication *app, gpointer user_data) {

    GtkWidget *window, *mainBox;
    GtkWidget *buttboxConvert, *buttboxHam, *buttBoxError, * buttBoxSuma;
    GtkWidget *buttonConvert, *buttonHam, *buttonError, *buttonSuma;

    // Create box for buttons
    buttBoxConvert = gtk_button_box_new();
    buttBoxHam = gtk_button_box_new();
    buttBoxError = gtk_button_box_new();
    buttBoxSuma = gtk_button_box_new();

    // Create buttons and add at button box
    buttonConvert = gtk_button_new_with_label("Binario - Gray");
    buttonSuma = gtk_button_new_with_label("Sumar formato Gray");
    buttonHam = gtk_button_new_with_label("Código Hamming");
    buttonError = gtk_button_new_with_label("Deteccion y correcion de errores");

    mainBox = gtk_box_new();
        
    // Set properties for winow
    window = gtk_application_window_new (app);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show_all (window);
}

// funtion main
int main (int argc, char **argv) {
    GtkApplication *app;
    int status;
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}

// Compiler gcc `pkg-config --cflags gtk+-3.0` -o hannoi hannoi.c `pkg-config --libs gtk+-3.0`