/*
--------------------------------------------------------------------------------
               IE-0117 Programación Bajo Plataformas Abiertas
                        Samuel Berrocal Soto.
                        Mario Benavides.
                        David Campos Espinoza.
--------------------------------------------------------------------------------
  Cato es una aplicación del juego de gato (tic-tac-toe) escrito en C, con
            una interfaz gráfica por medio de GTK+3.0 y Glade.
--------------------------------------------------------------------------------
*/

#include  <gtk/gtk.h>
#include  <stdlib.h>

// Botones de GTK.
// Matriz de gato 3 x 3.
 GtkButton *botones[3][3]={{NULL,NULL,NULL},{NULL,NULL,NULL},{NULL,NULL,NULL}};
 GtkButton *statusClick;

 int indicador = 0;
 int juegoContinua = 1;
 int contadorMovimientos = 0;

// Arreglo para registrar el marcador de puntaje.
 int marcador_puntaje[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
 // Arreglo para registrar botones apretados, y no sobre-escribirlos.
 int casillaOcupada[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);

// GTK builder
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "mainUI.glade", NULL);

// Ventana principal
    window = GTK_WIDGET (gtk_builder_get_object(builder, "mainWindow"));
    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show(window);
    gtk_main();
    return 0;
}

void salir_juego()
{
    gtk_main_quit();
    exit(0);
}

void acerca_de()
{
  GtkWidget   *about;
  GtkBuilder  *builder;

  builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "mainUI.glade", NULL);

  about = GTK_WIDGET(gtk_builder_get_object(builder, "acercaDe"));
  gtk_builder_connect_signals(builder, NULL);

  gtk_dialog_run (GTK_DIALOG (about));

  gtk_widget_destroy (about);
}

 void reset_juego()
 {
     int i, j;
     for(i = 0; i < 3; i++)
     {
         for(j = 0; j < 3; j++)
         {
             gtk_button_set_label(botones[i][j], " ");
         }
     }
 }
void reiniciar_juego(GtkWidget *click_button, gpointer   user_data)
{
  int i,j;
 indicador = 0; contadorMovimientos = 0; juegoContinua = 1;
  for(i = 0;i < 3;i++)
  {
      for(j = 0;j < 3;j++)
      {
          marcador_puntaje[i][j] = 0;
          botones[i][j] = NULL;
      }
  }
  reset_juego();
}

void inicio(GtkWidget *click_button, gpointer   user_data)
{
  statusClick = (GtkButton *) user_data;
  if(!indicador)
    {
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 1");
      indicador = 1;
    }
}

int revisar_ganador(int a[3][3])
{
  // Contadores de puntaje.
  int ganaJugador1 = 0;
  int ganaJugador2 = 0;
  int i, j;
  // Ciclo para revisar el ganador por filas.
  for(i = 0; i < 3; i++)
  {
    for(j = 0; j < 3; j++)
    {
      if(a[i][j] == 1){
        ganaJugador1++;
      }
      if(a[i][j] == 2){
        ganaJugador2++;
      }
    }
    // Retorna el valor 1 para el jugador 1, 2 para el jugador 2.
    // Esto se utiliza en el switch de cada boton.
    if(ganaJugador1 == 3){
      return 1;
    }
    if(ganaJugador2 == 3){
      return 2;
    }
    // Reinicia contadores de puntaje si no encuentra ganador.
    ganaJugador1 = 0;
    ganaJugador2 = 0;
  }
  // Ciclo para revisar el ganador por columnas.
  for(i = 0; i < 3; i++)
  {
    for(j = 0; j < 3; j++)
    {
      if(a[j][i] == 1){
        ganaJugador1++;
      }
      if(a[j][i] == 2){
        ganaJugador2++;
      }
    }
    if(ganaJugador1 == 3){
      return 1;
    }
    if(ganaJugador2 == 3){
      return 2;
    }
    ganaJugador1 = 0;
    ganaJugador2 = 0;
  }
  // Ciclo para revisar el ganador por diagonal.
  for(i = 0; i < 3; i++)
  {
    if(a[i][i] == 1){
      ganaJugador1++;
    }
    if(a[i][i] == 2){
      ganaJugador2++;
    }
  }
  if(ganaJugador1 == 3){
    return 1;
  }
  if(ganaJugador2 == 3){
    return 2;
  }
  ganaJugador1 = 0;
  ganaJugador2 = 0;

  // Ciclo para revisar diagonal inversa.
  for(i = 0, j = 2; i < 3; i++, j--)
  {
    if(a[i][j] == 1){
      ganaJugador1++;
    }
    if(a[i][j] == 2){
      ganaJugador2++;
    }
  }
  if(ganaJugador1 == 3){
    return 1;
  }
  if(ganaJugador2 == 3){
    return 2;
  }
  ganaJugador1 = 0;
  ganaJugador2 = 0;
  return 0;
}

int boton11(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  // Si la casilla ya está ocupada, rechaza el input.
  if(casillaOcupada[0][0]){
    return 0;
  }
  // Corre cuando el indicador se le dio click.
  if(indicador  &&  juegoContinua)
  {
    // Si es un movimiento impar, juega el jugador 1.
    if(++contadorMovimientos % 2)
    {
      marcador_puntaje[0][0] = 1;   // Marca el puntaje.
      casillaOcupada[0][0] = 1;     // Marca la casilla ocupada.
      gtk_button_set_label(buttonTemp, "X");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 0: if(contadorMovimientos == 9)
                {
                  gtk_button_set_label(statusClick, "EMPATE");
                  juegoContinua = 0;
                  return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0;
                return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0;
                return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 2");
    }
    // Si es un movimiento par, juega el jugador 2.
    else
    {
      marcador_puntaje[0][0] = 2;
      casillaOcupada[0][0] = 1;
      gtk_button_set_label(buttonTemp, "O");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 1");
    }
  }
  return 0;
}


int boton12(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(casillaOcupada[0][1]){
    return 0;
  }
  if(indicador  &&  juegoContinua)
  {
    if(++contadorMovimientos % 2)
    {
      marcador_puntaje[0][1] = 1;
      casillaOcupada[0][1] = 1;
      gtk_button_set_label(buttonTemp, "X");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 0: if(contadorMovimientos == 9)
                {
                  gtk_button_set_label(statusClick, "EMPATE");
                  juegoContinua = 0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 2");
    }
    else
    {
      marcador_puntaje[0][1] = 2;
      casillaOcupada[0][1] = 1;
      gtk_button_set_label(buttonTemp, "O");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 1");
    }
  }
  return 0;
}

int boton13(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(casillaOcupada[0][2]){
    return 0;
  }
  if(indicador  &&  juegoContinua)
  {
    if(++contadorMovimientos % 2)
    {
      marcador_puntaje[0][2] = 1;
      casillaOcupada[0][2] = 1;
      gtk_button_set_label(buttonTemp, "X");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 0: if(contadorMovimientos == 9)
                {
                  gtk_button_set_label(statusClick, "EMPATE");
                  juegoContinua = 0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 2");
    }
    else
    {
      marcador_puntaje[0][2] = 2;
      casillaOcupada[0][2] = 1;
      gtk_button_set_label(buttonTemp, "O");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 1");
    }
  }
  return 0;
}

int boton21(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(casillaOcupada[1][0]){
    return 0;
  }
  if(indicador && juegoContinua)
  {
    if(++contadorMovimientos % 2)
    {
      marcador_puntaje[1][0] = 1;
      casillaOcupada[1][0] = 1;
      gtk_button_set_label(buttonTemp, "X");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 0: if(contadorMovimientos == 9)
                {
                  gtk_button_set_label(statusClick, "EMPATE");
                  juegoContinua = 0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 2");
    }
    else
    {
      marcador_puntaje[1][0] = 2;
      casillaOcupada[1][0] = 1;
      gtk_button_set_label(buttonTemp, "O");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 1");
    }
  }
  return 0;
}

int boton22(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(casillaOcupada[1][1]){
    return 0;
  }
  if(indicador && juegoContinua)
  {
    if(++contadorMovimientos % 2)
    {
      marcador_puntaje[1][1] = 1;
      casillaOcupada[1][1] = 1;
      gtk_button_set_label(buttonTemp, "X");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 0: if(contadorMovimientos == 9)
                {
                  gtk_button_set_label(statusClick, "EMPATE");
                  juegoContinua = 0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 2");
    }
    else
    {
      marcador_puntaje[1][1] = 2;
      casillaOcupada[1][1] = 1;
      gtk_button_set_label(buttonTemp, "O");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 1");
    }
  }
  return 0;
}

int boton23(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(casillaOcupada[1][2]){
    return 0;
  }
  if(indicador && juegoContinua)
  {
    if(++contadorMovimientos % 2)
    {
      marcador_puntaje[1][2] = 1;
      casillaOcupada[1][2] = 1;
      gtk_button_set_label(buttonTemp, "X");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 0: if(contadorMovimientos == 9)
                {
                  gtk_button_set_label(statusClick, "EMPATE");
                  juegoContinua = 0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 2");
    }
    else
    {
      marcador_puntaje[1][2] = 2;
      casillaOcupada[1][2] = 1;
      gtk_button_set_label(buttonTemp, "O");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 1");
    }
  }
  return 0;
}

int boton31(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(casillaOcupada[2][0]){
    return 0;
  }
  if(indicador && juegoContinua)
  {
    if(++contadorMovimientos % 2)
    {
      marcador_puntaje[2][0] = 1;
      casillaOcupada[2][0] = 1;
      gtk_button_set_label(buttonTemp, "X");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 0: if(contadorMovimientos == 9)
                {
                  gtk_button_set_label(statusClick, "EMPATE");
                  juegoContinua = 0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 2");
    }
    else
    {
      marcador_puntaje[2][0] = 2;
      casillaOcupada[2][0] = 1;
      gtk_button_set_label(buttonTemp, "O");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 1");
    }
  }
  return 0;
}

int boton32(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(casillaOcupada[2][1]){
    return 0;
  }
  if(indicador && juegoContinua)
  {
    if(++contadorMovimientos % 2)
    {
      marcador_puntaje[2][1] = 1;
      casillaOcupada[2][1] = 1;
      gtk_button_set_label(buttonTemp, "X");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 0: if(contadorMovimientos == 9)
                {
                  gtk_button_set_label(statusClick, "EMPATE");
                  juegoContinua = 0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 2");
    }
    else
    {
      marcador_puntaje[2][1] = 2;
      casillaOcupada[2][1] = 1;
      gtk_button_set_label(buttonTemp, "O");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 1");
    }
  }
  return 0;
}

int boton33(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(casillaOcupada[2][2]){
    return 0;
  }
  if(indicador  &&  juegoContinua)
  {
    if(++contadorMovimientos % 2)
    {
      marcador_puntaje[2][2] = 1;
      casillaOcupada[2][2] = 1;
      gtk_button_set_label(buttonTemp, "X");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 0: if(contadorMovimientos == 9)
                {
                  gtk_button_set_label(statusClick, "EMPATE");
                  juegoContinua = 0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 2");
    }
    else
    {
      marcador_puntaje[2][2] = 2;
      casillaOcupada[2][2] = 1;
      gtk_button_set_label(buttonTemp, "O");
      switch(revisar_ganador(marcador_puntaje))
      {
        case 1: gtk_button_set_label(statusClick, "¡EL JUGADOR 1 GANA!");
                juegoContinua = 0; return 0;
        case 2: gtk_button_set_label(statusClick, "¡EL JUGADOR 2 GANA!");
                juegoContinua = 0; return 0;
      }
      gtk_button_set_label(statusClick, "TURNO DEL JUGADOR 1");
    }
  }
  return 0;
}
