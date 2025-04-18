#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tipoInfo {
    char nombre[31];
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

//--------------------Declarar Funciones--------------------

void insertarPrincipio (struct listaDoble *lista);
void insertarFinal (struct listaDoble *lista);
void insertarOrdenado (struct listaDoble *lista);


//--------------------MAIN--------------------

int main (void) {
    
    struct listaDoble lista;
    lista.primero = NULL; lista.ultimo = NULL;
    
    int option;
    struct tipoNodo *encontrado;
    int buscarCodigo;
    
    printf("****************MENÚ****************\n");
    printf("[1]Insertar al principio.\n");
    printf("[2]Insertar al final.\n");
    printf("[3]Insertar ordenado\n");
    printf("[4]Buscar un codigo.\n");
    printf("[5]Mostrar la lista.\n");
    printf("[6]Eliminar un nodo.\n");
    printf("[0]Salir.\n");
    printf("************************************\n\n");
    
    do {
        
        printf("**Introduce una opción: "); scanf("%d", &option);
        
        switch (option) {
                
            case 1:
                insertarPrincipio(&lista);
                break;
                
            case 2:
                insertarFinal(&lista);
                break;
                
            case 3:
                insertarOrdenado(&lista);
                break;
                
            default:
                break;
        }
        
        
    } while (option != 0);
    
    return 0;
}

void insertarPrincipio (struct listaDoble *lista) {
    
    struct tipoNodo *nuevo;
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    if (nuevo==NULL) {
        printf("error... al asignar memoria.\n"); return;
    }
    
    printf("Introduce los datos del contacto:\n");
    printf("\t-Nombre: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.nombre);
    printf("\t-Número: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.numero);
    printf("\t-Correo: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.correo);
    
    if (lista->primero == NULL) { //La lista está vacía
        
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
        
    } else { //Lista con nodos
        
        nuevo->anterior = NULL;
        nuevo->siguiente = lista->primero;
        lista->primero->anterior = nuevo;
        lista->primero = nuevo;
    }
}

void insertarFinal (struct listaDoble *lista) {
    
    struct tipoNodo *nuevo;
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    if (nuevo==NULL) {
        printf("error... al asignar memoria.\n"); return;
    }
    
    printf("Introduce los datos del contacto:\n");
    printf("\t-Nombre: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.nombre);
    printf("\t-Número: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.numero);
    printf("\t-Correo: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.correo);
    
    if (lista->primero == NULL) {
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
    } else {
        
        nuevo->anterior = lista->ultimo;
        nuevo->siguiente = NULL;
        lista->ultimo->siguiente= nuevo;
        lista->ultimo = nuevo;
    }
}

void insertarOrdenado (struct listaDoble *lista) {
    
    struct tipoNodo *nuevo, *recorre;
    recorre = lista->primero;
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    if (nuevo==NULL) {
        printf("error... al asignar memoria.\n"); return;
    }
    
    printf("Introduce los datos del contacto:\n");
    printf("\t-Nombre: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.nombre);
    printf("\t-Número: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.numero);
    printf("\t-Correo: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.correo);
    
    //Caso dónde la lista está vacía, no hay que buscar:
    if (lista->primero == NULL) {
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
        return; //IMPORTANTE
    }
    
    while (recorre != NULL && strcmp(recorre->informacion.nombre, nuevo->informacion.nombre) < 0) {
        recorre = recorre->siguiente;
    }
    
    if (recorre == lista->primero) { //Insertar al principio:
        nuevo->anterior = NULL;
        nuevo->siguiente = lista->primero;
        lista->primero->anterior = nuevo;
        lista->primero = nuevo;
    } //Insertar al final:
    else if (recorre == NULL) { //OJOOO! NULL no lista->ultimo
        nuevo->anterior = lista->ultimo;
        nuevo->siguiente = NULL;
        lista->ultimo->siguiente = nuevo;
        lista->ultimo = nuevo;
    } //Insertar en el medio:
    else {
        nuevo->anterior = recorre->anterior;
        nuevo->siguiente = recorre;
        recorre->anterior->siguiente = nuevo;
        recorre->anterior = nuevo;
    }
    
}
