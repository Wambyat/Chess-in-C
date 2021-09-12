#include <gtk/gtk.h>
#include <string.h>

void btn_clicked(GtkWidget *widget, GtkEntry *entry);
void myCSS(void);
void createWind(GtkWidget **window, gint width, gint height);
void createGrid(GtkWidget **grid, GtkWidget **window, const gchar *name);

int main(int argc, char *argv[]){
    GtkWidget *window, *grid;
    GtkWidget *button1,*button2,*button3,*button4,*button5,*button6,*button7,*button8;
    GtkWidget *b[8][8];

    gtk_init(&argc, &argv);
    myCSS();

    /*     Create the Window     */
    createWind(&window, 1000, 1000);

    /*     Create a Grid     */
    createGrid(&grid, &window, "myGrid");
    int bo[8][8]=
    {
        {12,13,14,15,16,14,13,12},
        {11,11,11,11,11,11,11,11},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {21,21,21,21,21,21,21,21},
        {22,23,24,25,26,24,23,22}
    };
    int i,j;
    gchar *item[1];
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            switch(bo[i][j])
            {
                case 11:
                        item[0]="♟";
                        break;
                case 21:
                        item[0]="♟";
                        break;
                case 12:
                        item[0]="♜";
                        break;
                case 22:
                        item[0]="♜";
                        break;
                case 13:
                        item[0]="♞";
                        break;
                case 23:
                        item[0]="♞";
                        break;
                case 14:
                        item[0]="♝";
                        break;
                case 24:
                        item[0]="♝";
                        break;
                case 15:
                        item[0]="♛";
                        break;
                case 25:
                        item[0]="♛";
                        break;
                case 16:
                        item[0]="♚";
                        break;
                case 26:
                        item[0]="♚";
                        break;
                default:
                        item[0]=" ";
            }
            b[i][j] = gtk_button_new_with_label(item[0]);
            gtk_widget_set_name(b[i][j], "myButton_red");
            gtk_widget_set_size_request(b[i][j], 20,20);
            g_object_set (b[i][j], "margin", 5, NULL);
            gtk_grid_attach(GTK_GRID(grid), b[i][j], j, i, 1, 1);
        }

    }
    bo[0][0]=11;

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

void myCSS(void){
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "mystyle.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}

void createWind(GtkWidget **window, gint width, gint height){
    *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(*window), "MyApp");
    gtk_window_set_default_size(GTK_WINDOW(*window), width, height);
    gtk_window_set_resizable (GTK_WINDOW(*window), TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(*window), 5);
    g_signal_connect(*window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void createGrid(GtkWidget **grid, GtkWidget **window, const gchar *name){
    *grid = gtk_grid_new ();
    gtk_grid_set_row_homogeneous(GTK_GRID(*grid), FALSE);
    gtk_grid_set_column_homogeneous(GTK_GRID(*grid), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER (*grid), 15);
    gtk_grid_set_column_spacing(GTK_GRID(*grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(*grid), 5);
    gtk_widget_set_name(*grid, name);
    g_object_set (*grid, "margin", 2, NULL);
    gtk_container_add (GTK_CONTAINER (*window), *grid);
}

void btn_clicked(GtkWidget *widget, GtkEntry *entry){
    (void)widget;
    const gchar *gstrTexto;

    gstrTexto = gtk_entry_get_text(entry);
    g_print("%s\n", gstrTexto);
    gtk_editable_select_region(GTK_EDITABLE(entry) , 0, 3);
}
