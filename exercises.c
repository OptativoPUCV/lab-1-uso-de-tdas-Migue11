#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

//#include "exercises.h"

//Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
//NO MODIFICAR
void imprime_lista(List *L) {
   int *dato;
   dato = (int*)first(L);
   printf("[");
   while(dato != NULL) {
      printf("%d ", *dato);
      dato = (int*)next(L);
   }
   printf("]\n");

}

//Ojo que la pila se vacía al imprimir y se imprime en orden inverso
//NO MODIFICAR
void imprime_y_vacia_pila(Stack *P) {
   void *dato;
   printf("[");
   while((dato = pop(P)) != NULL) {
      printf("%d ", *(int*)dato);
   }
   printf("]\n");
}

/* 
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/

List* crea_lista() {
   List* L = create_list();
    for (int i = 1; i <= 10; i++) {
        int *elemento = (int *)malloc(sizeof(int));
        *elemento = i;
        pushBack(L, elemento); 
    }

   return L;
}

/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.
*/

int sumaLista(List* L){
   int suma = 0;
   int* dato = (int*)first(L);
   while (dato != NULL) {
       suma += *dato;
       dato = (int*)next(L);
   }
   return suma;
}


/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos 
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/

void eliminaElementos(List *L, int elem) {
   for (void* data = first(L); data != NULL; data = next(L)) {
       if (*(int*)data == elem) {
           popCurrent(L);
       }
   }
}

/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/

void copia_pila(Stack* P1, Stack* P2) {
   List* aux = create_list();
   void* dato = first(P1);
   while (dato != NULL) {
       pushBack(aux, dato);
       dato = next(P1);
   }
   dato = first(aux);
   while (dato != NULL) {
       pushBack(P2, dato);
       dato = next(aux);
   }
   free(aux);
   
}

/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus 
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/

int parentesisBalanceados(char *cadena) {
   List* pila = create_list();

   for (int i = 0; cadena[i] != '\0'; i++) {
       char c = cadena[i];

       if (c == '(' || c == '{' || c == '[') {
           char *p = malloc(sizeof(char));
           *p = c;
           pushBack(pila, p);
       } else if (c == ')' || c == '}' || c == ']') {
           if (get_size(pila) == 0) {
               return 0; // No hay paréntesis de apertura correspondiente
           }
           char *top = (char *)popBack(pila);
           if ((c == ')' && *top != '(') ||
               (c == '}' && *top != '{') ||
               (c == ']' && *top != '[')) {
               free(top);
               return 0; // Los paréntesis no coinciden
           }
           free(top);
       }
   }

   int balanceado = get_size(pila) == 0;

   // Liberar cualquier paréntesis que quede en la pila
   while (get_size(pila) > 0) {
       free(popBack(pila));
   }

   free(pila);
   return balanceado;


