#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------LISTA---------------------

struct tipoInfo {
    char nombre [31];
    char numero [16];
    char correo [51];
};

struct tipoNodo {
    struct tipoInfo informacion;
    struct tipoNodo *anterior;
    struct tipoNodo *siguiente;
};

struct listaDoble {
    struct tipoNodo *primero;
    struct tipoNodo *ultimo;
};

//---------------------Declarar Funciones---------------------

void insertarOrdenado (struct listaDoble *lista);
void mostrarContactos (struct listaDoble *lista);
struct tipoNodo *buscarNombre (struct tipoNodo *primero, char *buscar);

//---------------------MAIN---------------------

int main (void) {
    
    struct listaDoble lista;
    lista.primero = NULL; lista.ultimo = NULL;
    
    int option;
    struct tipoNodo *encontrado;
    char buscarNodo [31];
    
    printf("***********MENÚ***********\n");
    printf("[1]Añadir un contacto\n");
    printf("[2]Mostrar todos los contactos\n");
    printf("[3]Buscar un contacto por nombre.\n");
    printf("[0]\n");
    printf("**************************\n");
    
    do {
        printf("**Introduce una opción: "); scanf("%d", &option);
        
        switch (option) {
                
            case 1:
                insertarOrdenado(&lista);
                break;
                
            case 2:
                mostrarContactos(&lista);
                break;
                
            case 3:
                printf("Introduce el nombre del usuario que buscas: ");
                scanf("%s", buscarNodo);
                
                encontrado = buscarNombre(lista.primero, buscarNodo);
                if (encontrado == NULL) {
                    printf("No se encontró el contacto...\n");
                }
                break;
                
            default:
                break;
        }
        
    } while (option != 0);
    
    return 0;
}

//---------------------FUNCIONES---------------------

void insertarOrdenado (struct listaDoble *lista) {
    
    //1. Reservo:
    struct tipoNodo *nuevo;
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    struct tipoNodo *recorre;
    recorre = lista->primero;
    
    //2. Relleno:
    printf("Introduce los datos del contacto:\n");
    printf("\t-Nombre: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.nombre);
    printf("\t-Número: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.numero);
    printf("\t-Correo: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.correo);
    
    //3. Conecto con la lista:
    //La lista está vacía:
    if (lista->primero == NULL) {
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
        return;
    }
    
    //Buscamos el sitio dónde va:
    while (recorre != NULL && strcmp(recorre->informacion.nombre, nuevo->informacion.nombre) < 0) {
        recorre = recorre->siguiente;
    }
    
    //Hemos colocado recorre en el siguiente a nuevo, ahora tenemos que ver los casos:
    
    //1. Va al principio:
    if (recorre == lista->primero) {
        recorre->anterior = nuevo;
        nuevo->siguiente = recorre;
        lista->primero = nuevo;
        nuevo->anterior = NULL;
    }
    //2. Vaya al final:
    else if (recorre == NULL) {
        nuevo->anterior = lista->ultimo;
        nuevo->siguiente = NULL;
        lista->ultimo->siguiente = nuevo;
        lista->ultimo = nuevo;
    }
    //3. Vaya en el medio:
    else {
        nuevo->siguiente = recorre;
        nuevo->anterior = recorre->anterior;
        recorre->anterior->siguiente = nuevo;
        recorre->anterior = nuevo;
    }
    
}

void mostrarContactos (struct listaDoble *lista) {
    
    struct tipoNodo *recorrer = lista->primero;
    
    while (recorrer != NULL) {
        
        printf("----Contacto----\n");
        printf("%s\n", recorrer->informacion.nombre);
        printf("%s\n", recorrer->informacion.numero);
        printf("%s\n", recorrer->informacion.correo);
        recorrer = recorrer->siguiente;
    }
    if (lista->primero == NULL) {
        printf("No tienes ningún contacto agendado...\n");
    }
}

struct tipoNodo *buscarNombre (struct tipoNodo *primero, char *buscar) {
    
    struct tipoNodo *recorrer;
    recorrer = primero;
    
    while (recorrer != NULL) {
        if (strcmp(recorrer->informacion.nombre, buscar) == 0) {
            printf("Encontrado!\nTu contacto es:\n");
            printf("%s\n", recorrer->informacion.nombre);
            printf("%s\n", recorrer->informacion.numero);
            printf("%s\n", recorrer->informacion.correo);

            return recorrer;
        }
        recorrer = recorrer->siguiente;
    }
    return NULL;
}
