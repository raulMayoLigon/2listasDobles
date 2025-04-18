#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//----------------LISTA----------------

struct fechaPublicacion {
    int dia;
    int mes;
    int anno;
};

struct tipoInfo {
    char usuario [21];
    char texto [21];
    struct fechaPublicacion fecha;
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

//----------------Declarar Funciones----------------

void anadirTweet (struct listaDoble *lista);
void mostrarUltimoTweet (struct listaDoble *lista);
void mostrarTweets (struct listaDoble *lista);
void insertarOrdenado (struct listaDoble *lista);

//----------------MAIN----------------

int main(void) {
    
    struct listaDoble lista;
    lista.primero = NULL; lista.ultimo = NULL;
    
    int option;
    
    printf("***************MENÚ***************\n");
    printf("[1]Añadir un tweet.\n");
    printf("[2]Mostrar el último tweet de un usuario.\n");
    printf("[3]Visualizar los tweets de un usuario.\n");
    printf("[4]Añadir un tweet ordenado por año.\n");
    printf("[0]Salir.\n");
    
    do {
        printf("\n**Introduce una opción: "); scanf("%d", &option);
        
        switch (option) {
                
            case 1:
                anadirTweet(&lista);
                break;
                
            case 2:
                mostrarUltimoTweet(&lista);
                break;
                
            case 3:
                mostrarTweets(&lista);
                break;
                
            case 4:
                insertarOrdenado(&lista);
                break;
                
            default:
                break;
        }
        
    } while (option != 0);
    
    return 0;
}

//----------------FUNCIONES----------------

void anadirTweet (struct listaDoble *lista) {
    
    struct tipoNodo *nuevo;
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    
    printf("Identificador: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.usuario);
    printf("Tweet: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.texto);
    
    printf("Fecha: \n");
    printf("\t-Día: "); scanf("%d", &nuevo->informacion.fecha.dia);
    printf("\t-Mes: "); scanf("%d", &nuevo->informacion.fecha.mes);
    printf("\t-Año: "); scanf("%d", &nuevo->informacion.fecha.anno);
    
    if (lista->primero == NULL) { //La lista esta vacía
        
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        
        lista->primero = nuevo;
        lista->ultimo = nuevo;
        
    } else { //La lista ya tiene nodos
        
        nuevo->anterior = lista->ultimo;
        lista->ultimo->siguiente = nuevo;
        lista->ultimo = nuevo;
        nuevo->siguiente = NULL;
    }
}

void mostrarUltimoTweet (struct listaDoble *lista) {
    
    struct tipoNodo *recorrer;
    recorrer = lista->ultimo;
    
    char buscar [21];
    
    printf("Introduce el identificador del usuario: "); fflush(stdin);
    scanf("%[^\n]", buscar);
    
    while (recorrer != NULL) {
        
        if (strcmp(buscar, recorrer->informacion.usuario) == 0) {
            printf("Usuario Encontrado!\n");
            printf("%d / %d / %d\n", recorrer->informacion.fecha.dia, recorrer->informacion.fecha.mes, recorrer->informacion.fecha.anno);
            printf("%s\n", recorrer->informacion.texto);
            return;
        }
        
        recorrer = recorrer->anterior;
    }
    printf("El usuario %s no ha participado en la red\n", buscar);
    return;
}

void mostrarTweets (struct listaDoble *lista) {
    
    struct tipoNodo *recorrer;
    recorrer = lista->primero;
    
    char buscar [21];
    int contador = 0;
    
    printf("Introduce el identificador del usuario que buscas: "); fflush(stdin);
    scanf("%[^\n]", buscar);
    
    while (recorrer != NULL) {
        
        if (strcmp(buscar, recorrer->informacion.usuario) == 0) {
            printf("%d / %d / %d\n", recorrer->informacion.fecha.dia, recorrer->informacion.fecha.mes, recorrer->informacion.fecha.anno);
            printf("%s\n", recorrer->informacion.texto);
            contador ++;
        }
        recorrer = recorrer->siguiente;
    }
    if (contador == 0) {
        printf("El usuario %s no ha participado en la red.\n", buscar);
    }
}

void insertarOrdenado (struct listaDoble *lista) {
    
    struct tipoNodo *nuevo;
    struct tipoNodo *recorre = lista->primero;
    
    //1. Reservo:
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    if (nuevo == NULL) {
        printf("Error al asignar memoria, saliendo... "); return;
    }
    
    //2. Relleno:
    printf("Introduce el identificador del usuario: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.usuario);
    printf("tweet: "); fflush(stdin);
    scanf("%[^\n]", nuevo->informacion.texto);
    printf("Introduce la fecha:\n");
    do {
        printf("\t-Día: "); scanf("%d", &nuevo->informacion.fecha.dia);
    } while (nuevo->informacion.fecha.dia < 1 || nuevo->informacion.fecha.dia > 31);
    do {
        printf("\t-Mes: "); scanf("%d", &nuevo->informacion.fecha.mes);
    } while (nuevo->informacion.fecha.mes < 1 || nuevo->informacion.fecha.mes > 12);
    do {
        printf("\t-Año: "); scanf("%d", &nuevo->informacion.fecha.anno);
    } while (nuevo->informacion.fecha.anno < 2000 || nuevo->informacion.fecha.anno > 2025);
    
    //3. Conecto con la lista:
    
    //3.a: OJO está ordenada debo buscar el sitio donde insertar.
    
    //Tratar el caso donde la lista está vacía en el que no hay que buscar el sitio
    if (lista->primero == NULL) {
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
        return;
    }
    
    //Busco el sitio, primero busco el año
    while (recorre != NULL && recorre->informacion.fecha.anno < nuevo->informacion.fecha.anno) {
        recorre = recorre->siguiente;
    }
    //Buscamos el mes y lo ponemos al final
    while (recorre != NULL && recorre->informacion.fecha.anno == nuevo->informacion.fecha.anno && recorre->informacion.fecha.mes < nuevo->informacion.fecha.mes) {
        recorre = recorre->siguiente;
    }
    
    //Buscamos el día y lo ponemos al final
    while (recorre != NULL && recorre->informacion.fecha.anno == nuevo->informacion.fecha.anno && recorre->informacion.fecha.mes == nuevo->informacion.fecha.mes && recorre->informacion.fecha.dia <= nuevo->informacion.fecha.dia) {
        recorre = recorre->siguiente;
    }
    
    //He colocado recorre en el siguiente al nuevo.
    //¿qué casos tengo?
    
    //1. Vaya al principio:
    if (recorre == lista->primero) {
        recorre->anterior = nuevo;
        nuevo->siguiente = recorre;
        nuevo->anterior = NULL;
        lista->primero = nuevo;
    }
    
    //2. Vaya al final:
    else if (recorre == NULL) { //Ha llegado al final
        nuevo->anterior = lista->ultimo;
        nuevo->siguiente = NULL;
        lista->ultimo->siguiente = nuevo;
        lista->ultimo = nuevo;
    }
    
    //3. Vaya al medio:
    else {
        nuevo->siguiente = recorre;
        nuevo->anterior = recorre->anterior;
        recorre->anterior->siguiente = nuevo;
        recorre->anterior = nuevo;
    }
}
