#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
  int id;
  char descripcion[314];
  char prioridad[10];
  time_t hora;
} ticket;


// Menú principal
void mostrarMenuPrincipal()
{
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalurie    ");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar pacientes por prioridad");
  puts("4) Atender al siguiente paciente");
  puts("5) Buscar y mostrar ticket por ID");
  puts("6) Salir");
}

// (1)
//
//
void registrar_paciente(List *pacientes) 
{
  printf("Registrar nuevo paciente\n");

  ticket *nuevo = (ticket *)malloc(sizeof(ticket));
  if (nuevo == NULL) return;

  printf("ID del ticket: ");
  scanf("%d", &nuevo->id);
  while (getchar() != '\n'); // Limpiar buffer

  // Verificar si el ID ya existe
  ticket *temp = list_first(pacientes);
  while (temp != NULL) {
    if (temp->id == nuevo->id) {
      printf("Ya existe un ticket con ese ID. Registro cancelado.\n");
      free(nuevo); // Liberar memoria reservada
      return;
    }
    temp = list_next(pacientes);
  }

  printf("Descripción del problema: ");
  fgets(nuevo->descripcion, sizeof(nuevo->descripcion), stdin);
  nuevo->descripcion[strcspn(nuevo->descripcion, "\n")] = 0;

  strcpy(nuevo->prioridad, "Bajo");
  nuevo->hora = time(NULL); // Hora real

  list_pushBack(pacientes, nuevo);
  printf("Ticket registrado correctamente.\n");
}

// (2)
//
//
void asignar_prioridad(List *pacientes)
{
  int id_buscar;
  char nueva_prioridad[10];

  printf("Ingrese el ID del ticket al que desea asignar prioridad: ");
  scanf("%d", &id_buscar);

  // Limpiar el buffer después de usar scanf
  while (getchar() != '\n');

  // Buscar el ticket con el ID ingresado
  ticket *t = list_first(pacientes);
  while (t != NULL) {
      if (t->id == id_buscar) {
          // Si se encuentra el ticket, solicitamos la nueva prioridad
          printf("Ingrese la nueva prioridad (Alto, Medio, Bajo): ");
          fgets(nueva_prioridad, sizeof(nueva_prioridad), stdin);
          nueva_prioridad[strcspn(nueva_prioridad, "\n")] = 0;  // Eliminar el salto de línea

          // Validar la entrada de prioridad
          if (strcmp(nueva_prioridad, "Alto") == 0 || strcmp(nueva_prioridad, "Medio") == 0 || strcmp(nueva_prioridad, "Bajo") == 0) {
              strcpy(t->prioridad, nueva_prioridad);
              printf("Prioridad actualizada correctamente a '%s'.\n", t->prioridad);
          } else {
              printf("Prioridad inválida. Por favor, ingrese 'Alto', 'Medio' o 'Bajo'.\n");
          }
          return;
      }
      t = list_next(pacientes); // Mover al siguiente ticket
  }

  // Si no se encuentra el ticket con ese ID
  printf("No se encontró un ticket con el ID %d.\n", id_buscar);
}

// (3)
//
//
void mostrar_lista_pacientes(List *pacientes)
{
  printf("Pacientes en espera:\n");
  if (list_first(pacientes) == NULL) {
    printf("No hay pacientes en espera.\n");
    return;
  }

  printf("----------------------------\n");

  ticket *t = list_first(pacientes);
  while (t != NULL) {
    char hora_formateada[64];
    struct tm *info_hora = localtime(&t->hora);
    strftime(hora_formateada, sizeof(hora_formateada), "%Y-%m-%d %H:%M:%S", info_hora);

    printf("ID: %d\n", t->id);
    printf("Descripción: %s\n", t->descripcion);
    printf("Prioridad: %s\n", t->prioridad);
    printf("Hora de llegada: %s\n", hora_formateada);
    printf("----------------------------\n");
    
    t = list_next(pacientes);
  }
}

// (4)
//
//
int prioridad_valor(const char *prioridad) {
  if (strcmp(prioridad, "Alto") == 0) return 3;
  if (strcmp(prioridad, "Medio") == 0) return 2;
  if (strcmp(prioridad, "Bajo") == 0) return 1;
  return 0;
}

int comparar(const void *a, const void *b) {
  ticket *ticket_a = (ticket *)a;
  ticket *ticket_b = (ticket *)b;

  int prioridad_a = prioridad_valor(ticket_a->prioridad);
  int prioridad_b = prioridad_valor(ticket_b->prioridad);

  // Comparar primero por prioridad (de mayor a menor)
  if (prioridad_a != prioridad_b)
      return prioridad_b - prioridad_a; // "Alto" primero

  // Si la prioridad es igual, comparar por hora (el más antiguo primero)
  return (int)difftime(ticket_a->hora, ticket_b->hora);
}



void mostrar_lista_ordenada(List *tickets)
{
  if (list_first(tickets) == NULL) {
      printf("No hay tickets pendientes.\n");
      return;
  }

  // Crear un array temporal para ordenar
  int size = list_size(tickets);
  ticket *array_tickets = malloc(size * sizeof(ticket));
  if (array_tickets == NULL) {
      printf("Error al asignar memoria.\n");
      return;
  }

  // Copiar los tickets a un array para ordenarlos
  ticket *t = list_first(tickets);
  for (int i = 0; t != NULL; t = list_next(tickets), i++) {
      array_tickets[i] = *t;
  }

  // Ordenar los tickets usando qsort
  qsort(array_tickets, size, sizeof(ticket), comparar);

  printf("Tickets pendientes:\n");
  printf("----------------------------\n");
  for (int i = 0; i < size; i++) {
    printf("ID: %d\n", array_tickets[i].id);
    printf("Descripción: %s\n", array_tickets[i].descripcion);
    printf("Prioridad: %s\n", array_tickets[i].prioridad);
    printf("Hora de llegada: %s", ctime(&array_tickets[i].hora));
    printf("----------------------------\n");
}


  // Liberar la memoria temporal
  free(array_tickets);
}

// (5)
//
//
void procesar_siguiente_ticket(List *pacientes) {
  if (list_first(pacientes) == NULL) {
    printf("No hay tickets pendientes.\n");
    return;
  }

  ticket *mejor = NULL;
  ticket *actual = list_first(pacientes);
  while (actual != NULL) {
    if (mejor == NULL || comparar(actual, mejor) < 0) {
      mejor = actual;
    }
    actual = list_next(pacientes);
  }

  ticket *aux = list_first(pacientes);
  while (aux != NULL) {
    if (aux == mejor) {
      list_popCurrent(pacientes);
      break;
    }
    aux = list_next(pacientes);
  }

  printf("--------------------------\n");
  printf("Ticket a atender:\n");
  printf("ID: %d\n", mejor->id);
  printf("Descripción: %s\n", mejor->descripcion);
  printf("Prioridad: %s\n", mejor->prioridad);
  printf("Hora de registro: %s", ctime(&mejor->hora)); // Hora en formato legible
  printf("--------------------------\n");

  free(mejor);
}


// (6)
//
//
void buscar_ticket_por_id(List *tickets) {
  if (list_first(tickets) == NULL) {
    printf("No hay tickets registrados.\n");
    return;
  }

  int id_buscado;
  printf("Ingrese el ID del ticket a buscar: ");
  scanf("%d", &id_buscado);

  ticket *t = list_first(tickets);
  while (t != NULL) {
    if (t->id == id_buscado) {
      printf("--------------------------\n");
      printf("Ticket encontrado:\n");
      printf("ID: %d\n", t->id);
      printf("Descripción: %s\n", t->descripcion);
      printf("Prioridad: %s\n", t->prioridad);
      printf("Hora de registro: %s", ctime(&t->hora)); // Hora en formato legible
      printf("--------------------------\n");
      return;
    }
    t = list_next(tickets);
  }

  printf("No se encontró ningún ticket con ID %d.\n", id_buscado);
}


// (main)
//
//
int main() {
  char opcion;
  List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes
  if (pacientes == NULL) {
    printf("No se pudo crear la lista.\n");
    return 1;
  }

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':
      // Lógica para asignar prioridad
      asignar_prioridad(pacientes);
      break;
    case '7':
      mostrar_lista_pacientes(pacientes);
      break;
    case '3':
      // Lógica para mostrar pacientes por prioridad
      mostrar_lista_ordenada(pacientes);
      break;
    case '4':
      // Lógica para atender al siguiente paciente
      procesar_siguiente_ticket(pacientes);
      break;
    case '5':
      // Lógica para mostrar ticket por id
      buscar_ticket_por_id(pacientes);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitaluria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pacientes);

  return 0;
}
