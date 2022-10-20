// #include "gtk_auto.h"
#include <gtk/gtk.h>

// funtion construct
static void activate (GtkApplication *app, gpointer user_data) {

    GtkWidget *window, *mainBox;
    GtkWidget *buttBoxConvert, *buttBoxHam, *buttBoxError, * buttBoxSuma;
    GtkWidget *buttonConvert, *buttonHam, *buttonError, *buttonSuma;
    GtkStyleContext *style;

    // Create mian container box 
    mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    // Create box for buttons
    buttBoxConvert = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxHam = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxError = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxSuma = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    // Create buttons and add at button box
    buttonConvert = gtk_button_new_with_label("Binario - Gray");
    buttonSuma = gtk_button_new_with_label("Sumar formato Gray");
    buttonHam = gtk_button_new_with_label("Código Hamming");
    buttonError = gtk_button_new_with_label("Deteccion y correcion de errores");

    gtk_button_set_relief(GTK_BUTTON(buttonConvert), GTK_RELIEF_HALF);

    gtk_container_add(GTK_CONTAINER(buttBoxConvert), buttonConvert);
    gtk_container_add(GTK_CONTAINER(buttBoxHam), buttonHam);
    gtk_container_add(GTK_CONTAINER(buttBoxError), buttonError);
    gtk_container_add(GTK_CONTAINER(buttBoxSuma), buttonSuma);

    gtk_widget_set_size_request(GTK_WIDGET(buttonConvert), 240, 40);
    gtk_widget_set_size_request(GTK_WIDGET(buttonSuma), 240, 40);
    gtk_widget_set_size_request(GTK_WIDGET(buttonError), 240, 40);
    gtk_widget_set_size_request(GTK_WIDGET(buttonHam), 240, 40);

    // add box buttons at main box
    gtk_box_pack_start(GTK_BOX(mainBox), buttBoxConvert, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(mainBox), buttBoxHam, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(mainBox), buttBoxSuma, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(mainBox), buttBoxError, TRUE, TRUE, 10);
        
    // Set properties for winow
    window = gtk_application_window_new (app);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    
    style; "labels" = "widgets" {
    font_name = "Sans Bold 14"
    }

    
    gtk_container_add(GTK_CONTAINER(window), mainBox);
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

// Compiler gcc `pkg-config --cflags gtk+-3.0` -o main main.c `pkg-config --libs gtk+-3.0`