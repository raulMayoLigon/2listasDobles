#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//--------------------LISTA--------------------

struct tipoInfo {
    int codigo;
    double value;
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
struct tipoNodo *funcionBuscarCodigo (struct tipoNodo *buscar, int codigoBuscar);
void mostrarLista (struct listaDoble *lista);
void eliminarNodo (struct listaDoble *lista);

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
                
            case 4:
                printf("Introduce el código que buscas: "); scanf("%d", &buscarCodigo);
                encontrado = funcionBuscarCodigo(lista.primero, buscarCodigo);
                if (encontrado == NULL) {
                    printf("Losiento no se encontró el código...\n");
                }
                break;
                
            case 5:
                mostrarLista(&lista);
                break;
                
            case 6:
                eliminarNodo(&lista);
                break;
                
            default:
                break;
        }
        
        
    } while (option != 0);
    
    return 0;
}

//--------------------FUNCIONES--------------------

void insertarPrincipio (struct listaDoble *lista) {
    
    struct tipoNodo *nuevo;
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    if (nuevo == NULL) {
        printf("Error al asignar memoria...\n"); return;
    }
    
    printf("Introduce el código: "); scanf("%d", &nuevo->informacion.codigo);
    printf("Introduce el valor: "); scanf("%lf", &nuevo->informacion.value);

    
    if (lista->primero == NULL) { //Lista vacía:
        
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
    } else { //Lista con nodos:
        
        nuevo->anterior = NULL;
        nuevo->siguiente = lista->primero;
        lista->primero->anterior = nuevo;
        lista->primero = nuevo;
    }
}

void insertarFinal (struct listaDoble *lista) {
    
    struct tipoNodo *nuevo;
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    if (nuevo == NULL) {
        printf("Error al asignar memoria...\n"); return;
    }
    
    printf("Introduce el código: "); scanf("%d", &nuevo->informacion.codigo);
    printf("Introduce el valor: "); scanf("%lf", &nuevo->informacion.value);
    
    if (lista->primero == NULL) { //Lista vacía:
        
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
    } else { //Lista con nodos:
        
        nuevo->anterior = lista->ultimo;
        nuevo->siguiente = NULL;
        lista->ultimo->siguiente = nuevo;
        lista->ultimo = nuevo;
    }
}

void insertarOrdenado (struct listaDoble *lista) {
    
    struct tipoNodo *nuevo;
    struct tipoNodo *recorre;
    recorre = lista->primero;
    
    //1. Reservo:
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    
    //2. Relleno:
    printf("Introduce el código: "); scanf("%d", &nuevo->informacion.codigo);
    printf("Introduce el valor: "); scanf("%lf", &nuevo->informacion.value);
    
    //3. Conecto:
    
    //Lista vacía, no hay que buscar el sitio:
    if (lista->primero == NULL) {
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
        return;
    }
    
    //Busco el sitio:
    while (recorre != NULL && recorre->informacion.codigo < nuevo->informacion.codigo) {
        recorre = recorre->siguiente;
    }
    //Ya sabemos donde debemos insertarlo, casos:
    
    //He colocado recorre en el siguiente al nuevo.
    //Nuevo va al principio:
    if (recorre == lista->primero) {
        recorre->anterior = nuevo;
        nuevo->siguiente = lista->primero;
        nuevo->anterior = NULL;
        lista->primero = nuevo;
    }
    //Nuevo va al final
    else if (recorre == NULL) { //Ha llegado al final
        nuevo->anterior = lista->ultimo;
        nuevo->siguiente = NULL;
        lista->ultimo->siguiente = nuevo;
        lista->ultimo = nuevo;
    }
    //Va al medio;
    else {
        nuevo->anterior = recorre->anterior;
        nuevo->siguiente = recorre;
        recorre->anterior->siguiente = nuevo;
        recorre->anterior = nuevo;
        
    }
}

struct tipoNodo *funcionBuscarCodigo (struct tipoNodo *primero, int codigoBuscar) {
    
    struct tipoNodo *recorre;
    recorre = primero;
    
    while (recorre != NULL) {
        if (recorre->informacion.codigo == codigoBuscar) {
            printf("[Código: %d Valor: %lf]\n", recorre->informacion.codigo, recorre->informacion.value);
            return recorre;
        }
        recorre = recorre->siguiente;
    }
    return  NULL;
}

void mostrarLista (struct listaDoble *lista) {
    
    struct tipoNodo *recorre;
    recorre = lista->primero;
    
    if (lista->primero == NULL) {
        printf("La lista está vacía...\n"); return;
    }
    
    printf("\n[NULL] --> ");
    while (recorre != NULL) {
        
        printf(" <-- [ %d | %lf ] --> ", recorre->informacion.codigo, recorre->informacion.value);
        recorre = recorre->siguiente;
    }
    printf(" <-- [NULL]\n");
}

void eliminarNodo (struct listaDoble *lista) {
    
    struct tipoNodo *eliminar;
    int codigoEliminar;
    printf("Introduce el codigo que deseas eliminar: "); scanf("%d", &codigoEliminar);
    
    eliminar = funcionBuscarCodigo(lista->primero, codigoEliminar);
    
    if (eliminar == NULL) {
        printf("Nodo no encontrado...\n");
    }
    if (eliminar != NULL) {
        //Casos:
        
        //1. Es el único:
        if (lista->ultimo == lista->primero) {
            lista->primero = NULL;
            lista->ultimo = NULL;
        }
        //2. Es el primero.
        else if (lista->primero == eliminar) {
            lista->primero = lista->primero->siguiente;
            lista->primero->anterior = NULL;
        //3. Es el último.
        } else if (lista->ultimo == eliminar) {
            lista->ultimo = lista->ultimo->anterior;
            lista->ultimo->siguiente = NULL;
        //4. Está en el medio:
        } else {
            eliminar->anterior->siguiente = eliminar->siguiente;
            eliminar->siguiente->anterior = eliminar->anterior;
        }
    }
    printf("Eliminando...\n");
}

