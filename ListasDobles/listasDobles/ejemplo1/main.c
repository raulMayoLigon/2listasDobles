#include <stdio.h>
#include <stdlib.h>

//********Declarar lista y nodos********
struct tipoInfo{
    int codigo;
    double value;
};

struct tipoNodo{
    struct tipoInfo information;
    struct tipoNodo *siguiente;
    struct tipoNodo *anterior;
};

struct listaDoble{
    struct tipoNodo *primero;
    struct tipoNodo *ultimo;
};

//********Declarar funciones********
int menu(void);
void visualizarListaUltimo(struct tipoNodo *ultimo);
void visualizarInfo(struct tipoInfo info);
void rellenarInfo(struct tipoInfo *info);
void anadirFinalLista(struct listaDoble *lista);
struct tipoNodo *buscar(struct tipoNodo *primero, int codigoBuscar);
void eliminar(struct listaDoble *lista, int codigoBorrar);
struct tipoNodo *buscarOrdenado(struct tipoNodo *primero, int codigoBuscar);
void anadirOrdenado(struct listaDoble *lista);


//********Func MAIN********
int main(void) {
    struct listaDoble lista;
    lista.primero = NULL;
    lista.ultimo = NULL;
    int codigo;
    struct tipoNodo *encontrado;
    
    int opc;
    
    do{
        opc = menu();
        switch (opc) {
                
            case 1: visualizarListaUltimo(lista.ultimo);
                break;
                
            case 2:anadirFinalLista(&lista);
                break;
                
            case 3:
                printf("Introduce el código a buscar: "); scanf("%d", &codigo);
                encontrado = buscar(lista.primero, codigo);
                if (encontrado == NULL) {
                    printf("No existe ese código");
                } else {
                    printf("Si existe ese código:");
                    visualizarInfo(encontrado->information);
                }
                break;
                
            case 4:
                printf("Introduce el código a borrar: "); scanf("%d", &codigo);
                eliminar(&lista, codigo);
                break;
                
            case 5:
                printf("Introduce el código a buscar: "); scanf("%d", &codigo);
                encontrado = buscarOrdenado(lista.primero, codigo);
                //OJO cuando buscarOrdenado no está devuelve el sitio donde debería estar.
                if ((encontrado == NULL) && (encontrado->information.codigo == codigo)) {
                    printf("Si existe ese código\n");
                    visualizarInfo(encontrado->information);
                } else {
                    printf("No existe ese código\n");
                }
                break;
                
            case 6:
                break;
                
            case 7:
                break;
                
        }
        
    }while (opc!=0);
    
    return 0;
}

//********func MENÚ*********
int menu(void){
    int opc;
    do{
        printf("\n*****************MENU********************\n");
        printf("\n\t1.Visualizar la lista del último al primero");
        printf("\n\t2.Añadir al final de la lista");
        printf("\n\t3.Buscar un elemento con un codigo en la lista");
        printf("\n\t4.Eliminar el nodo con un codigo");
        printf("\n\t5.Buscar ordenado");
        printf("\n\t6.Añadir ordenado");
        printf("\n\t7.Visualizar para cada código el número de nodos que hay (ordenado)");
        
        printf("\n\t0. Salir");
        printf("\n*******************************************\n");
        printf("\n\t Introduce una opción: ");
        scanf("%d",&opc);
        
    }while ((opc<0) || (opc>7));
    return opc;
}

//********FUNCIONES********
void visualizarListaUltimo(struct tipoNodo *ultimo){
    struct tipoNodo *recorre = ultimo;
    if (ultimo == NULL){
        printf("\n---Lista vacía---");
        return;
    }
    while (recorre != NULL){
        visualizarInfo(recorre->information);
        recorre = recorre->anterior; //va por los punteros anterior
    }
}

void visualizarInfo(struct tipoInfo info){
    printf("\n Codigo: \t%d Valor: %.2lf",info.codigo,info.value);
    
}

void rellenarInfo(struct tipoInfo *info){
    printf("\n Introduce el código: ");
    scanf("%d",&info->codigo);
    printf("\n Introduce el valor: ");
    scanf("%lf",&info->value);
}

void anadirFinalLista(struct listaDoble *lista) {
    struct tipoNodo *nuevo;
   
    //1.Reservo
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    if (nuevo == NULL) {
        printf("ERROR... al asignar memoria"); return;
    }
    //2.Relleno la información.
    rellenarInfo(&nuevo->information);
    //3.Conecto lista.
    //Casos-> lista vacía / lista con nodos.
    if (lista->primero == NULL) {
        lista->primero = nuevo;
    } else {
        lista->ultimo->siguiente = nuevo;
    }
    //acciones comunes a ambos casos
    nuevo->anterior = lista->ultimo;
    nuevo->siguiente = NULL;
    lista->ultimo = nuevo;
}

struct tipoNodo *buscar(struct tipoNodo *primero, int codigoBuscar) {
    
    struct tipoNodo *recorrer;
    recorrer = primero;
    //Recorremos la lista hasta que lo encuentres o llegue a NULL si no está
    while (recorrer != NULL && (recorrer->information.codigo != codigoBuscar)) {
        recorrer = recorrer->siguiente;
    }
    //Me paro cuando lo encuentra y si no lo encuentra está en NULL.
    return recorrer;
}

void eliminar(struct listaDoble *lista, int codigoBorrar) {
    
    struct tipoNodo *borrar, *anterior, *siguiente;
    
    borrar = buscar(lista->primero, codigoBorrar);
    if (borrar == NULL) {
        printf("Imporsible borrar, no existe ese código"); return;
    }
    //Tengo un nodo a borrar, localizado por el dedo a borrar
    //Tengo qu tratar todos los casos que tenga en una lista doble
    anterior = borrar->anterior;
    siguiente = borrar->siguiente;
    
    //Liberar la memoria del nodo que borro
    if ((borrar == lista->primero) && (borrar == lista->ultimo)) { //Es el único
        lista->primero = NULL;
        lista->ultimo = NULL;
    } else if (borrar == lista->primero) { //El que borro es el primero y tengo más en la lista.
        siguiente->anterior = NULL;
        lista->primero = siguiente;
    } else if (borrar == lista->ultimo) { //borro el último y tengo más en la lista.
        anterior->siguiente = NULL;
        lista->ultimo = anterior;
    } else { //Borro en medio de mi lista.
        anterior->siguiente = siguiente;
        siguiente->anterior = anterior;
    }
    
    //Libero memoria:
    free(borrar);
}

struct tipoNodo *buscarOrdenado(struct tipoNodo *primero, int codigoBuscar) {
    /* Devuelve un puntero que localiza el nodo que tiene ese código cuando lo encuentra o devuelve un puntero que localiza el sitio donde debería estar cuando no lo encuentra. */
    
    struct tipoNodo *recorrer;
    recorrer = primero;
    while (recorrer != NULL && (recorrer->information.codigo < codigoBuscar)) {
        recorrer = recorrer->siguiente;
    }
    return recorrer;
}

void anadirOrdenado(struct listaDoble *lista){
    
    struct tipoNodo *nuevo, *siguiente, *anterior;
   
    //1.Reservo
    nuevo = (struct tipoNodo *)malloc(sizeof(struct tipoNodo));
    if (nuevo == NULL) {
        printf("ERROR... al asignar memoria"); return;
    }
    //2.Relleno la información.
    rellenarInfo(&nuevo->information);
    
    //3.Conecto con la lista
    //Antes de buscar vamos a ver si la lista está vacía g me quito este caso
    if (lista->primero == NULL) {
        //Añado el único
        nuevo->anterior = NULL;
        nuevo->siguiente = NULL;
        lista->primero = nuevo;
        lista->ultimo = nuevo;
    }
    //3.2. Busca el sitio donde tiene que ir e nuevo. Usamos nuestra función de buscar ordenado (que ya nos devuelve el sitio)
    siguiente = buscarOrdenado(lista->primero, nuevo->information.codigo);
    
    //3.3. Trata todos los casos, ya he tratado el de lista vacía.
    //¿Qué casos tengo? | 1.Que vaya al principio | 2.Al final | 3.En medio |
    
    if (siguiente == lista->primero) { //Inserto al principio.
        nuevo->anterior = NULL;
        nuevo->siguiente = siguiente; //nuevo->siguiente = lista->primero
        siguiente->anterior = nuevo;
        lista->primero = nuevo;
        
    } else if (siguiente == NULL) { //Va al final
        nuevo->anterior = lista->ultimo;
        nuevo->siguiente = NULL; // nuevo->siguiente = siguiente
        lista->ultimo->siguiente = nuevo;
        lista->ultimo = nuevo;
        
    } else { //Va en el medio
        anterior = siguiente->anterior;
        
        nuevo->anterior = anterior;
        nuevo->siguiente = siguiente;
        anterior->siguiente = nuevo;
        siguiente->anterior = nuevo;
    }
}
