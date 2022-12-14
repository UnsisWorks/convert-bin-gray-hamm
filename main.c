#include <gtk/gtk.h>
#include <math.h>

GtkWidget *mainWindow, *bin, *gray, *combo, *labelRequest;
gchar format[10];

// Convert decimal to binary
const gchar* decToBin(gint64 decimal , int returns){
    GString *mod = g_string_new("");
    int result;
    result = decimal;
    char aux[25];
    while (result != 0) {
        // Conversión y obtención de modulo
        sprintf(aux, "%d", (result % 2));
        result = result / 2;
        // g_print("mod2: %s\n", aux);
        
        mod = g_string_prepend(mod, aux);
    }

    if (strcmp(format, "-1") == 0){
        // g_print("no format\n");
    } else {
            int decimal = atoi(format);
            // g_print("format: %d\n", decimal);
        // Valid multipl to format
        gint difference = 0;
        for (gint i = decimal; i <= (mod->len + decimal); i += decimal) {
            if (i >= (mod->len - 1)) {
                difference = i - (mod->len);
            }
        }
        // Add char's for complete multi the 4
        if (difference < decimal && difference != 0) {
            for (gint i = 1; i <= difference; i++) {
                g_string_prepend_c(mod, '0');
            }
        }
    }

    if (returns == 0) {
        gchar len[5]; // = mod->len + '0';
        sprintf(len, "%ld", mod->len);
        const gchar *res = len;
        return res;
    }
    return mod->str;
}

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

// Cast binary to gray
void binaryToGray(GString *binario){
    // Init Gray with the firts digit binary
    gchar init[2];
    init[0] = binario->str[0];
    init[1] = '\0';
    GString *sgray = g_string_new(init);
    char v;
    gchar aux[30];
    // Apply XoR to the bits
    for (int i = 0; i < binario->len - 1; i++) {
        if (i < binario->len){
            v = (binario->str[i]);
            int a = atoi(&v);
            v = (binario->str[i + 1]);
            int b = atoi(&v);
            // Sum representaation and assingnament to gray
            int c = a ^ b;
            sprintf(aux, "%d", c);
            g_print("%d && %d = %d\n",a , b, c);
            sgray = g_string_append_c(sgray, aux[0]);
        }
    }
    gtk_entry_set_text(GTK_ENTRY(gray), sgray->str);
}

// Cast gray to binary
void grayToBin(GString *sgray){
    // init binary with firts bit
    gchar init[2];
    init[0] = sgray->str[0];
    init[1] = '\0';
    GString *binario = g_string_new(init);
    char v;
    gchar aux[30];

    // Apply XOR at the bits. 
    for (int i = 1; i <  sgray->len; i++){
        v = (sgray->str[i]);
        int a = atoi(&v);
        v = (binario->str[i - 1]);
        int b = atoi(&v);
        int c = a ^ b;
        sprintf(aux, "%d", c);
        binario = g_string_append(binario, aux);
    }
    gtk_entry_set_text(GTK_ENTRY(bin), binario->str);
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
        switch (type) {
        case 0:
            // Code for cast Bin to Gray -- Valid
            // Iterat value (except char end string '\0')

            if (flag == TRUE) {
                g_print("Continue\n");
                binaryToGray(value);

            } else {
                showMessage(NULL, "Ingresar unicamente 0 y 1", "Aviso");
            }
            break;
        case 1:
            // Code for cast Gray to Bin
            if (flag) {
                g_print("Continue\n");
                grayToBin(value);
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
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect(window, "destroy", G_CALLBACK(closeWindow), NULL);

    // Set class for reference in CSS
    gtk_widget_set_name(GTK_WIDGET(box), "box-convert");

    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(binLab)), "label-convert");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(grayLab)), "label-convert");

    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(bin)), "entry-convert");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(gray)), "entry-convert");

    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
}

void generatorHamming (GtkWidget *widget, gpointer user_data) {
    // get text the entrys
    const gchar *binary = gtk_entry_get_text(GTK_ENTRY(bin));
    GString *value;
    gint count = 0;

    // Confirm string with contain
    if (!strcmp(binary, "") == 0) {
        count++;
        value = g_string_new(binary);
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
        if (flag == TRUE) {
            // ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
            
            // Confirm selected type parity
            gint selection = gtk_combo_box_get_active(GTK_COMBO_BOX(combo));
            if (selection != 0) {
                // Calc bits parity
                int bp = 0;
                while (pow(2, bp) <= value->len + bp + 1){
                    bp++;
                }

                // Create variables for the assignment bits the parity (bp)
                GString *position = g_string_new("");
                g_print("bit de paridad: %d\n", bp);
                int index = value->len + bp;
                int bitParidad[index];
                strcpy(format, "-1");
                const gchar *maxDigits = decToBin(index, 0);
                strcpy(format, maxDigits);
                char positions[index][50];
                GString *password = g_string_new("");
                GString *request = g_string_new("");
                gchar requestAux[index];
                g_print("Max diigts: %d\n", index);
                
                // locate bits the parity
                for (int i = 0; i < index; i++) {
                    // Get position in binary
                    position = g_string_assign(position, decToBin(i + 1, 1));
                    // Save position in format binary
                    strcpy(positions[i], position->str);
                    count = 0;
                    for (int j = 0; j < position->len; j++) {
                        if (position->str[j] == '1') {
                            count++;
                        }
                    }
                    // Asignar bit de paridad ligado
                    if (count == 1){
                        bitParidad[i] = 1;
                    } else {
                        bitParidad[i] = 0;
                    }
                }
                count = 0;
                int k = 0;
                int l = 0;
                int emparejador = 0;
                // Add bits the data
                for (int i = 0; i < index; i++) {
                    if (bitParidad[i] == 0) {
                        requestAux[i] = value->str[k];
                        k++;
                    }
                }
                k = 0;
                // Iterate the length of the Hamming
                for (int i = 0; i < index; i++) {
                    // Add bits of parity
                    if (bitParidad[i] == 1) {
                        while (positions[i][k] != '\0') {
                            // Obtener bit en común para el conteo. -> emparejador <-
                            if(positions[i][k] == '1') {
                                emparejador = k;
                                break;
                            }
                            k++;
                        }
                        k = 0;
                        // Iterate only DATA and search parity bits (1)
                        for (int j = i; j < index; j++) {
                            if ((bitParidad[j] == 0)) {
                                // Count the '1' corresponding to parity
                                if (positions[j][emparejador] == '1'){
                                    if (requestAux[j] == '1') {
                                        count++;
                                    }
                                }
                            }
                        }
                        
                        if (selection == 1) {
                            // Se asegura la paridad par
                            if (count % 2 == 0) {
                                requestAux[i] = '0';
                                
                            } else {
                                g_print("ES UN 1\n");
                                requestAux[i] = '1';
                            }
                        } else {
                            // Se asegura la paridad impar
                            if (count % 2 != 0) {
                                requestAux[i] = '0';
                                
                            } else {
                                requestAux[i] = '1';
                            }
                        }
                        count = 0;
                    }
                }
                // Show results
                for (int i = 0; i < index; i++) {
                    g_print(" %c", requestAux[i]);
                    request = g_string_append_c(request, requestAux[i]);
                }
                gtk_label_set_text(GTK_LABEL(labelRequest), request->str);
            } else {
                showMessage(NULL, "Seleccione el tipo de paridad", "Advertencia");
            }
        }
    } else {
        showMessage(NULL, "Debe ingresar un binario", "Advertenacia");
    }
}

// Create interface for button signal "Hamming"
static void hamming (GtkWidget *widget, gpointer user_data) {
    gtk_widget_set_visible(GTK_WIDGET(mainWindow), FALSE);
    GtkWidget *window, *box, *buttBox, *button, *label, *fixed;

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 25);
    fixed = gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(box), fixed, FALSE, FALSE, 0);

    // Create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Haming");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 300);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect(window, "destroy", G_CALLBACK(closeWindow), NULL);

    buttBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    button = gtk_button_new_with_label("Obtener Hamming");
    gtk_container_add(GTK_CONTAINER(buttBox), button);
    g_signal_connect(button, "clicked", G_CALLBACK(generatorHamming), NULL);

    combo = gtk_combo_box_text_new_with_entry();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "    Tipo de paridad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "   Bit de paridad par");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Bit de paridad impar");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

    label = gtk_label_new("Binario");
    labelRequest = gtk_label_new("HAMMING");
    bin = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(bin), "Binario");
    gtk_widget_set_size_request(GTK_WIDGET(bin), 230, 35);

    // Add widgets at fixed
    gtk_fixed_put(GTK_FIXED(fixed), label, 35, 30);
    gtk_fixed_put(GTK_FIXED(fixed), labelRequest, 115, 210);
    gtk_fixed_put(GTK_FIXED(fixed), bin, 35, 50);
    gtk_fixed_put(GTK_FIXED(fixed), combo, 55, 112);
    gtk_fixed_put(GTK_FIXED(fixed), buttBox, 60, 165);

    gtk_widget_set_name(GTK_WIDGET(box), "box-hamming");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(label)), "label-hamming");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(labelRequest)), "label-hamming");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(button)), "button-hamming");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(bin)), "entry-hamming");

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);
}


static void detectionHamming (GtkWidget *widget, GtkWidget user_data) {
    // get text the entrys
    const gchar *binary = gtk_entry_get_text(GTK_ENTRY(bin));
    GString *value;
    gint type = 0;
    gint count = 0;

    // Confirm string with contain
    if (!strcmp(binary, "") == 0) {
        type = 0;
        count++;
        value = g_string_new(binary);
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
        if (flag) {
            type = gtk_combo_box_get_active(GTK_COMBO_BOX(combo));
            GString *position = g_string_new("");
            
            if (type != 0) {
                
                // Variables generales de la corrección
                int index = value->len;
                int bitParidad[index];
                strcpy(format, "-1");
                const gchar *maxDigits = decToBin(index, 0);
                strcpy(format, maxDigits);
                char positions[index][50];
                GString *password = g_string_new("");
                GString *request = g_string_new("");
                // g_print("Max diigts: %s\n", maxDigits);
                
                // Localizar bits de paridad
                for (int i = 0; i < index; i++) {
                    // Get position in binary
                    // g_print("send max: %s\n", maxDigits);
                    position = g_string_assign(position, decToBin(i + 1, 1));
                    // Save position in format binary
                    strcpy(positions[i], position->str);
                    count = 0;
                    g_print("Posicion: %d bin: %s\n", i + 1, position->str);
                    for (int j = 0; j < position->len; j++) {
                        if (position->str[j] == '1') {
                            count++;
                        }
                    }
                    // Asignar bit de paridad ligado
                    if (count == 1){
                        bitParidad[i] = 1;
                        // g_print("Paridad - %d", i);
                    } else {
                        bitParidad[i] = 0;
                        // g_print("Valor - %d", i);
                    }
                    puts("");
                }
                
                //  Paridad par
                if (type == 1) {
                    // Continiue
                    count = 0;
                    int k = 0;
                    int l = 0;
                    int emparejador = 0;
                    for (int i = 0; i < index; i++) {
                        if (bitParidad[i] == 1) {
                            while (positions[i][k] != '\0') {
                                // Obtener bit en común para el conteo. emparejador <-
                                if(positions[i][k] == '1') {
                                    emparejador = k;
                                    break;
                                    // g_print("emparejado en: %d\n", emparejador);
                                }
                                // g_print("char: %c - ", positions[i][k]);
                                k++;
                            }
                            puts("");
                            k = 0;
                            
                            for (int j = i; j < index; j++) {
                                // Recorremos unicamente los DATOS
                                if ((bitParidad[j] == 0) || j == i) {
                                    // g_print("pre paridad\n");
                                    if (positions[j][emparejador] == '1'){
                                        g_print("Verificar [%d][%d]\t", j, emparejador);
                                        if (value->str[j] == '1') {
                                            count++;
                                            g_print(" = 1 count: %d\n", count);
                                        }else {
                                            g_print(" = 0 count:s %d\n", count);
                                        }
                                    }
                                }
                            }
                            
                                // Se asegura la paridad par
                                if (count % 2 == 0) {
                                    g_print("ES UN 0\n");
                                    password = g_string_prepend_c(password, '0');
                                } else {
                                    g_print("ES UN 1\n");
                                    password = g_string_prepend_c(password, '1');
                                }
                                count = 0;
                                // g_print("i: %d j: %d\n", i, j);
                        }
                            // break;
                    }
                    int pass = g_ascii_strtoll(password->str, NULL, 2);
                    g_print("Request clave : %s dec: %d\n", password->str, pass);
                    if (value->str[pass - 1] == '1') {
                        value->str[pass- 1] = '0';
                    } else {
                        value->str[pass- 1] = '1';
                    }
                    g_print("Request finela : %s\n", value->str);
                    gtk_label_set_text(GTK_LABEL(labelRequest), value->str);

                // Paridad impar
                } else if (type == 2) {
                    // Continiue
                    count = 0;
                    int k = 0;
                    int l = 0;
                    int emparejador = 0;
                    for (int i = 0; i < index; i++) {
                        if (bitParidad[i] == 1) {
                            while (positions[i][k] != '\0') {
                                // Obtener bit en común para el conteo. emparejador <-
                                if(positions[i][k] == '1') {
                                    emparejador = k;
                                    break;
                                    // g_print("emparejado en: %d\n", emparejador);
                                }
                                // g_print("char: %c - ", positions[i][k]);
                                k++;
                            }
                            puts("");
                            k = 0;
                            
                            for (int j = i; j < index; j++) {
                                // Recorremos unicamente los DATOS
                                if ((bitParidad[j] == 0) || j == i) {
                                    // g_print("pre paridad\n");
                                    if (positions[j][emparejador] == '1'){
                                        g_print("Verificar [%d][%d]\t", j, emparejador);
                                        if (value->str[j] == '1') {
                                            count++;
                                            g_print(" = 1 count: %d\n", count);
                                        }else {
                                            g_print(" = 0 count:s %d\n", count);
                                        }
                                    }
                                }
                            }
                            
                                // Se asegura la paridad impar
                                if (count % 2 != 0) {
                                    g_print("ES UN 0\n");
                                    password = g_string_prepend_c(password, '0');
                                } else {
                                    g_print("ES UN 1\n");
                                    password = g_string_prepend_c(password, '1');
                                }
                                count = 0;
                                // g_print("i: %d j: %d\n", i, j);
                        }
                            // break;
                    }
                    int pass = g_ascii_strtoll(password->str, NULL, 2);
                    g_print("Request clave : %s dec: %d\n", password->str, pass);

                    if (value->str[pass - 1] == '1') {
                        value->str[pass- 1] = '0';
                    } else {
                        value->str[pass- 1] = '1';
                    }
                    g_print("Request finela : %s\n", value->str);
                    gtk_label_set_text(GTK_LABEL(labelRequest), value->str);

                }
            } else {
                showMessage(NULL, "Debe seleccionar un tipo de paridad", "Advertencia");
            }
            
        } else {
            showMessage(NULL, "Solo debe ingresar 1 - 0", "Advertencia");
        }
    } else {
        showMessage(NULL, "Debe llenar el campo", "Advertencia");
    }
}

// Create interface for button signal "Correción y deteciión de errores"
static void correctionHamming (GtkWidget *widget, gpointer user_data) {
    gtk_widget_set_visible(GTK_WIDGET(mainWindow), FALSE);
    GtkWidget *window, *box, *buttBox, *button, *label, *fixed;

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 25);
    fixed = gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(box), fixed, FALSE, FALSE, 0);
    combo = gtk_combo_box_text_new_with_entry();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "    Tipo de paridad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "   Bit de paridad par");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Bit de paridad impar");
    // MODIFICAR SELECCION
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 1);

    // Create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Haming");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect(window, "destroy", G_CALLBACK(closeWindow), NULL);

    buttBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    button = gtk_button_new_with_label("Obtener Hamming");
    g_signal_connect(button, "clicked", G_CALLBACK(detectionHamming), bin);
    gtk_container_add(GTK_CONTAINER(buttBox), button);

    labelRequest = gtk_label_new("Código Corregido");
    label = gtk_label_new("Binario");
    bin = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(bin), "Binario");
    gtk_widget_set_size_request(GTK_WIDGET(bin), 230, 35);
    gtk_entry_set_alignment(GTK_ENTRY(bin), 0.5);

    // Add widgets at fixed
    gtk_fixed_put(GTK_FIXED(fixed), label, 35, 30);
    gtk_fixed_put(GTK_FIXED(fixed), bin, 35, 50);
    gtk_fixed_put(GTK_FIXED(fixed), buttBox, 55, 115);
    gtk_fixed_put(GTK_FIXED(fixed), combo, 280, 50);
    gtk_fixed_put(GTK_FIXED(fixed), labelRequest, 35, 190);

    gtk_widget_set_name(GTK_WIDGET(box), "box-error");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(label)), "label-error");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(labelRequest)), "label-error");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(button)), "button-error");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(bin)), "entry-error");

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);
}

// Funtion for sumary formats grays
static void sumaryBCD(GtkWidget *widget, gpointer user_data) {
    const gchar *ftGray  = gtk_entry_get_text(GTK_ENTRY(gray));
    const gchar *ndGray  = gtk_entry_get_text(GTK_ENTRY(bin));
    GString *ftValue;
    GString *ndValue;

    // Verification the string void
    if ((strcmp(ftGray, "") != 0) && (strcmp(ndGray, "") != 0)){
        ftValue = g_string_new(ftGray);
        ndValue = g_string_new(ndGray);
        GString *valueAux = g_string_new("");

        gboolean ftFlag = TRUE;
        gboolean ndFlag = TRUE;

        gint64 decimal;
        gint64 nddecimal;

        // Verification the string valid
        for (gint i = 0; i <= (ftValue->len) - 1; i++) {
            // Compare chars the object string with '0' y '1'
            if (!((ftValue->str[i] == '0') || ftValue->str[i] == '1')) {
                ftFlag = FALSE;
                break;
            }
        }
        
        // for (gint i = 0; i <= (ndValue->len) - 1; i++) {
        //     // Compare chars the object string with '0' y '1'
        //     if (!((ndValue->str[i] == '0') || ndValue->str[i] == '1')) {
        //         ndFlag = FALSE;
        //         break;
        //     }
        // }


        // // Valid multipl the 4 to ftValue 
        gint difference = 0;
        // for (gint i = 4; i <= (ftValue->len + 4); i += 4) {
        //     if (i >= (ftValue->len - 1)) {
        //         difference = i - (ftValue->len);
        //     }
        // }

        if ((ftValue->len % 4) != 0) {
            ftFlag = FALSE;
            puts("FALSO 1");
        }

        g_print("string: %s\n", ftValue->str); 
        if (ftFlag == TRUE){
            // Verification the format BCD valid
            for (gint i = 4; i < (ftValue -> len) + 4; i += 4) {
                // Save 4 bits 
                valueAux = g_string_assign(valueAux, ftValue->str);
                valueAux = g_string_erase (valueAux, i, - 1);
                valueAux = g_string_erase (valueAux, 0, i - 4);
                // g_print("desde: %d hasta: %d \n", i - 4, i); 
                // g_print("erase: %s\n", valueAux->str); 

                decimal = strtol(valueAux->str, NULL, 2);
                // g_print("decimal: %ld\n", decimal); 
                if(decimal > 9) {
                    difference = i - (ftValue->len);
                }
                
            }

            if ((ftValue->len - 1) % 4 == 0) {
                ftFlag = FALSE;
            puts("FALSO 2");
            }
        }
        
        
        // Valid multipl the 4 to ndValue 
        // for (gint i = 4; i <= (ndValue->len + 4); i += 4) {
        //     if (i >= (ndValue->len - 1)) {
        //         ftFlag = FALSE;
        //     }
        // }
            // g_print("string: %s\n", ndValue->str); 
        if (ftFlag == TRUE){
            // puts("entry +   ");
            // Verification the format BCD valid
            for (gint i = 4; i < (ndValue -> len) + 4; i += 4) {
                // Save 4 bits 
                valueAux = g_string_assign(valueAux, ndValue->str);
                valueAux = g_string_erase (valueAux, i, - 1);
                valueAux = g_string_erase (valueAux, 0, i - 4);
                // g_print("desde: %d hasta: %d \n", i - 4, i); 

                decimal = strtol(valueAux->str, NULL, 2);
                // g_print("decimal: %ld\n", decimal); 
                if(decimal > 9) {
                    ndFlag = FALSE;
                }
                
            }
        }

        // continue
        if ((ftFlag == TRUE) && (ndFlag == TRUE)) {
            
            // somatory the 4 in 4
            int ftLong = ftValue -> len; 
            int ndLong = ndValue -> len;
            int length;
            if (ndLong >= ftLong) {
                length = ndLong;
            } else {
                length = ftLong + 4;
            }

            gint suma;
            char aux2;
            GString *request = g_string_new("");
            for (gint i = 4; i < length; i += 4) {
                // Save 4 bits 
                puts("entry ");
                valueAux = g_string_assign(valueAux, ndValue->str);
                valueAux = g_string_erase (valueAux, i, - 1);
                valueAux = g_string_erase (valueAux, 0, i - 4);

                decimal = g_ascii_strtoll(valueAux->str, NULL, 2);
                
                valueAux = g_string_assign(valueAux, ftValue->str);
                valueAux = g_string_erase (valueAux, i + 4, - 1);
                valueAux = g_string_erase (valueAux, 0, i);

                nddecimal = g_ascii_strtoll(valueAux->str, NULL, 2);

                suma = decimal + nddecimal;
                aux2= sprintf(aux2, "%c", suma);
                request = g_string_prepend(request, decToBin(suma, -1));
                g_print("Decimal: %ld decimal 2: %ld resultado: %d - %s\n", decimal, nddecimal, suma, decToBin(suma, -1));
            }
            
        } else {
            showMessage(NULL, "Formato invalido", "Error");
        }
        
        
    } else {
        showMessage(NULL, "Debe llenar todos los campos", "Advertencia");
    }
    
}
// Create inface for signal button 'SumarGray'
static void sumaBcd(GtkWidget *widget, gpointer user_data){
    gtk_widget_set_visible(GTK_WIDGET(mainWindow), FALSE);
    GtkWidget *window, *box, *buttBox, *button, *label, *fixed, *stGray, *ndGray;

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 25);
    fixed = gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(box), fixed, FALSE, FALSE, 0);

    // Create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sumar formato Gray");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 300);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect(window, "destroy", G_CALLBACK(closeWindow), NULL);

    buttBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    button = gtk_button_new_with_label("Sumar");
    gtk_container_add(GTK_CONTAINER(buttBox), button);

    g_signal_connect(button, "clicked", G_CALLBACK(sumaryBCD), NULL);

    label = gtk_label_new("Primer bcd");
    gray = gtk_entry_new();
    bin = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(gray), "Formato BCD");
    gtk_widget_set_size_request(GTK_WIDGET(gray), 230, 35);
    gtk_entry_set_alignment(GTK_ENTRY(gray), 0.5);
    gtk_entry_set_placeholder_text(GTK_ENTRY(bin), "Formato BCD");
    gtk_widget_set_size_request(GTK_WIDGET(bin), 230, 35);
    gtk_entry_set_alignment(GTK_ENTRY(bin), 0.5);

    // Add widgets at fixed
    gtk_fixed_put(GTK_FIXED(fixed), label, 35, 20);
    gtk_fixed_put(GTK_FIXED(fixed), gray, 35, 60);
    gtk_fixed_put(GTK_FIXED(fixed), bin, 35, 120);
    gtk_fixed_put(GTK_FIXED(fixed), buttBox, 55, 175);

    gtk_widget_set_name(GTK_WIDGET(box), "box-hamming");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(label)), "label-hamming");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(button)), "button-hamming");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(gray)), "entry-hamming");
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(bin)), "entry-hamming");

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
    buttonSuma = gtk_button_new_with_label("Sumar formato BCD");
    buttonHam = gtk_button_new_with_label("Código Hamming");
    buttonError = gtk_button_new_with_label("Deteccion y correcion de errores");

    // Create signals for buttons
    g_signal_connect(buttonConvert, "clicked", G_CALLBACK(convert), NULL);
    g_signal_connect(buttonHam, "clicked", G_CALLBACK(hamming), NULL);
    g_signal_connect(buttonSuma, "clicked", G_CALLBACK(sumaBcd), NULL);
    g_signal_connect(buttonError, "clicked", G_CALLBACK(correctionHamming), NULL);

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

// Compiler gcc `pkg-config --cflags gtk+-3.0` -o main main.c `pkg-config --libs gtk+-3.0` -lm