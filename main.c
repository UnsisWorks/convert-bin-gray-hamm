#include <gtk/gtk.h>

GtkWidget *mainWindow, *bin, *gray;

static void showMessage (GtkWidget *widget, gchar *message, gchar *title) {
    GtkWidget *dialog, *label, *contentArea;
    GtkDialogFlags flags;

    // Create at window dialog with title, parent, flags, text in button
    dialog = gtk_dialog_new_with_buttons(title, NULL, flags, "Aceptar", GTK_RESPONSE_NONE, NULL);

    // Set properties at window dialog
    contentArea = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_window_set_default_size(GTK_WINDOW(dialog), 200, 200);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT );
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    label = gtk_label_new(message);
    // gtk_label

    // Close window dialog to the price button accept
    g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
    // Add witget and show result
    gtk_container_add(GTK_CONTAINER(contentArea), label);
    gtk_widget_show_all(dialog);
}

// Funtion for cast bin to gray and reverse
static void binToGray(GtkWidget *widget, gpointer user_data) {
    // get text the entrys
    const gchar *binary = gtk_entry_get_text(GTK_ENTRY(bin));
    const gchar *sgray = gtk_entry_get_text(GTK_ENTRY(gray));
    GString *value;
    gint type = 0;
    gint count = 0;

    // Confirm string with contain
    if (!strcmp(binary, "") == 0) {
        type = 0;
        count++;
        value = g_string_new(binary);
    }
    if (!strcmp(sgray, "") == 0) {
        count++;
        type = 1;
        value = g_string_new(sgray);
    }
    
    if (count == 1) {
        gboolean flag = TRUE;
        for (gint i = 0; i <= (value->len) - 1; i++) {
            // Compare chars the object string with '0', '1' y '.'
            if (!((value->str[i] == '0') || value->str[i] == '1'/* || value->str[i] == '.'*/)) {
                flag = FALSE;
                break;
            }
        }
        g_print("Continue\n");
        switch (type) {
        case 0:
            // Code for cast Bin to Gray -- Valid
            // Iterat value (except char end string '\0')

            if (flag) {


            } else {
                showMessage(NULL, "Ingresar unicamente 0 y 1", "Aviso");
            }
            break;
        case 1:
            // Code for cast Gray to Bin
            if (flag) {
            } else {
                showMessage(NULL, "Ingresar unicamente 0 y 1", "Aviso");
            }
            break;
        default:
            break;
        }
        
    } else {
        g_print("Not continue\n");
        // MESSAGE WARING
        showMessage(NULL, "Debe llenar un campo", "Aviso");
        //g_string_free(value, TRUE);
    }
}

// Funtion general for set visible in TRUE in main window
static void closeWindow(GtkWidget *widget, gpointer user_data) {
    gtk_widget_set_visible(GTK_WIDGET(mainWindow), TRUE);
}

// Function construct for window the button convert binario to gray
static void convert(GtkWidget *widget, GtkWidget *s) {
    gtk_widget_set_visible(GTK_WIDGET(mainWindow), FALSE);
    GtkWidget *window, *box, *fixedBin, *fixedGray;
    GtkWidget *binLab, *grayLab, *buttBox, *button;

    // Create Containers for widgets
    fixedBin = gtk_fixed_new();
    fixedGray = gtk_fixed_new();
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL , 25);

    // Create entrys for convert
    bin = gtk_entry_new();
    gray = gtk_entry_new();
    // Set properties at entry widgets
    gtk_widget_set_size_request(GTK_WIDGET(bin), 210, 35);
    gtk_widget_set_size_request(GTK_WIDGET(gray), 210, 35);
    gtk_entry_set_placeholder_text(GTK_ENTRY(bin), "Binario");
    gtk_entry_set_placeholder_text(GTK_ENTRY(gray), "Formato Gray");
    gtk_entry_set_alignment(GTK_ENTRY(bin), 0.5);
    gtk_entry_set_alignment(GTK_ENTRY(gray), 0.5);

    binLab = gtk_label_new("Binario");
    grayLab = gtk_label_new("Gray");

    buttBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    button = gtk_button_new_with_label("Convertir");
    g_signal_connect(button, "clicked", G_CALLBACK(binToGray), NULL);
    gtk_container_add(GTK_CONTAINER(buttBox), button);

    // Add widgets at container fixed
    gtk_fixed_put(GTK_FIXED(fixedBin), binLab, 30, 0);
    gtk_fixed_put(GTK_FIXED(fixedBin), bin, 30, 40);
    gtk_fixed_put(GTK_FIXED(fixedGray), grayLab, 30, 0);
    gtk_fixed_put(GTK_FIXED(fixedGray), gray, 30, 40);

    // Set components at box 
    gtk_box_pack_start(GTK_BOX(box), fixedBin, FALSE, FALSE, 25);
    gtk_box_pack_start(GTK_BOX(box), fixedGray, FALSE, FALSE, 25);
    gtk_box_pack_start(GTK_BOX(box), buttBox, FALSE, FALSE, 25);

    // Create new window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ON_PARENT);
    // gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    // g_signal_connect(window, "destroy", G_CALLBACK(closeWindow), NULL);

    // Set class for reference in CSS
    gtk_widget_set_name(GTK_WIDGET(box), "box-convert");

    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(binLab)), "label-convert");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(grayLab)), "label-convert");

    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(bin)), "entry-convert");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(gray)), "entry-convert");

    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
}

static void hamming (GtkWidget *widget, gpointer user_data) {
    gtk_widget_set_visible(GTK_WIDGET(mainWindow), FALSE);
    GtkWidget *window, *box, *buttBox, *button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Haming");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 500);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    buttBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    button = gtk_button_new_with_label("Obtener Hamming");

    gtk_container_add(GTK_CONTAINER(buttBox), button);

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 25);
    gtk_widget_set_name(GTK_WIDGET(box), "box-hamming");

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);
}
// funtion construct
static void activate (GtkApplication *app, gpointer user_data) {

    GtkWidget *mainBox;
    GtkWidget *buttBoxConvert, *buttBoxHam, *buttBoxError, * buttBoxSuma;
    GtkWidget *buttonConvert, *buttonHam, *buttonError, *buttonSuma;
    GtkStyleContext *style;
    GtkCssProvider *cssProvider;
    
    // Cargar estilos css
    cssProvider = gtk_css_provider_new();

    // Create mian container box 
    mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_box_set_homogeneous (GTK_BOX(mainBox), TRUE);

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

    // Create signals for buttons
    g_signal_connect(buttonConvert, "clicked", G_CALLBACK(convert), NULL);
    g_signal_connect(buttonHam, "clicked", G_CALLBACK(hamming), NULL);

    // gtk_button_set_relief(GTK_BUTTON(buttonConvert), GTK_RELIEF_HALF);
    // Add buttons at button box
    gtk_container_add(GTK_CONTAINER(buttBoxConvert), buttonConvert);
    gtk_container_add(GTK_CONTAINER(buttBoxHam), buttonHam);
    gtk_container_add(GTK_CONTAINER(buttBoxError), buttonError);
    gtk_container_add(GTK_CONTAINER(buttBoxSuma), buttonSuma);

    // Set size buttons
    gtk_widget_set_size_request(GTK_WIDGET(buttonConvert), 240, 90);
    gtk_widget_set_size_request(GTK_WIDGET(buttonSuma), 240, 90);
    gtk_widget_set_size_request(GTK_WIDGET(buttonError), 240, 90);
    gtk_widget_set_size_request(GTK_WIDGET(buttonHam), 240, 90);

    // add box buttons at main box
    gtk_container_add(GTK_CONTAINER(mainBox), buttBoxConvert);
    gtk_container_add(GTK_CONTAINER(mainBox), buttBoxHam);
    gtk_container_add(GTK_CONTAINER(mainBox), buttBoxSuma);
    gtk_container_add(GTK_CONTAINER(mainBox), buttBoxError);
        
    // Add class selector at buttons for use in CSS
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonConvert), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonSuma), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonError), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonHam), "button");

    gtk_widget_set_name(GTK_WIDGET(mainBox), "box");

    // Load style for CSS file
    gtk_css_provider_load_from_path(cssProvider, "./style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(cssProvider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Set properties for winow
    mainWindow = gtk_application_window_new (app);
    gtk_window_set_position(GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (mainWindow), "Window");
    gtk_window_set_default_size (GTK_WINDOW (mainWindow), 600, 800);
    gtk_window_set_resizable(GTK_WINDOW(mainWindow), TRUE);
    
    gtk_container_add(GTK_CONTAINER(mainWindow), mainBox);
    gtk_widget_show_all (mainWindow);
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