#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

abb_t *abb_crear(abb_comparador comparador)
{
	abb_t *arbol = malloc(sizeof(abb_t));

	if (arbol == NULL)
		return NULL;
	
	if(comparador == NULL)
		return NULL;
	
	arbol->nodo_raiz = NULL;
	arbol->comparador = comparador;
	arbol->tamanio = 0;
	
	return arbol;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if(arbol == NULL)
		return NULL;
	
	nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t));

	if (nodo == NULL)
		return NULL;
	
	if(arbol->nodo_raiz == NULL){
		nodo->elemento = elemento;
		nodo->izquierda = NULL;
		nodo->derecha = NULL;
		arbol->nodo_raiz = nodo;
		arbol->tamanio++;
		return arbol;
	}

	nodo_abb_t *nodo_actual = arbol->nodo_raiz;

	while (nodo_actual) {
        if (arbol->comparador(elemento, nodo_actual->elemento) == 0) {
            free(nodo);
            return NULL;
        }
		if (arbol->comparador(elemento, nodo_actual->elemento) < 0){
			if(nodo_actual->izquierda == NULL){
				nodo->elemento = elemento;
				nodo->izquierda = NULL;
				nodo->derecha = NULL;
				nodo_actual->izquierda = nodo;
				arbol->tamanio++;
				return arbol;
			}
            nodo_actual = nodo_actual->izquierda;
		}
        else {
			if(nodo_actual->derecha == NULL){
				nodo->elemento = elemento;
				nodo->izquierda = NULL;
				nodo->derecha = NULL;
				nodo_actual->derecha = nodo;
				arbol->tamanio++;
				return arbol;
			}
			nodo_actual = nodo_actual->derecha;
		}
    }

	return arbol;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if(!arbol)
		return NULL;

	nodo_abb_t *nodo_actual = arbol->nodo_raiz;

	while(nodo_actual){
		int comparador = arbol->comparador(elemento, nodo_actual->elemento);
		if(comparador == 0)
			return nodo_actual->elemento;
		if(comparador < 0)
			nodo_actual = nodo_actual->izquierda;
		else
			nodo_actual = nodo_actual->derecha;
	}

	return NULL;
}

void *buscar_predecesor(abb_t *arbol, nodo_abb_t *nodo_actual)
{
	if(!arbol)
		return NULL;

	nodo_abb_t *nodo_predecesor = nodo_actual->izquierda;

	while(nodo_predecesor->derecha){
		nodo_predecesor = nodo_predecesor->derecha;
	}

	return nodo_predecesor->elemento;
}

void nodo_destruir(nodo_abb_t *nodo) {
    if (!nodo) return;

    nodo_destruir(nodo->izquierda);
    nodo_destruir(nodo->derecha);
    free(nodo);
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if(!arbol)
		return NULL;
	
	if(arbol->nodo_raiz == NULL)
		return NULL;

	nodo_abb_t *nodo_actual = arbol->nodo_raiz;
	nodo_abb_t *nodo_padre = NULL;

	while(nodo_actual){
		int comparador = arbol->comparador(elemento, nodo_actual->elemento);
		if(comparador == 0){
			// sin hijos
			if(nodo_actual->izquierda == NULL && nodo_actual->derecha == NULL){
				nodo_destruir(nodo_actual);
				arbol->tamanio--;
				return elemento;
			}

			// 2 hijos - funciona
			if(nodo_actual->izquierda != NULL && nodo_actual->derecha != NULL){
				void *predecesor = buscar_predecesor(arbol, nodo_actual);
				nodo_actual->elemento = predecesor;
				free(predecesor);
				arbol->tamanio--;
				return elemento;
			}

			//1 hijo
			nodo_abb_t *nodo_hijo = nodo_actual->izquierda ? nodo_actual->izquierda : nodo_actual->derecha;
			if(!nodo_padre){
				arbol->nodo_raiz = nodo_hijo;
				free(nodo_hijo);
				arbol->tamanio--;
				return elemento;
			} else if(nodo_padre->izquierda == nodo_actual){
				nodo_padre->izquierda = nodo_hijo;
				free(nodo_hijo);
				arbol->tamanio--;
				return elemento;
			} else {
				nodo_padre->derecha = nodo_hijo;
				free(nodo_hijo);
				arbol->tamanio--;
				return elemento;
			}	
		}
		nodo_padre = nodo_actual;
		if(comparador < 0)
			nodo_actual = nodo_actual->izquierda;
		else
			nodo_actual = nodo_actual->derecha;
	}

	return NULL;
// 	nodo_abb_t *nodo_padre = NULL;

// 	while(nodo_actual){
// 		int comparador = arbol->comparador(elemento, nodo_actual->elemento);
// 		if(comparador == 0){
// 			if(nodo_actual->izquierda != NULL && nodo_actual->derecha != NULL){
// 			// 	nodo_abb_t *predecesor = buscar_predecesor(arbol, nodo_actual);
// 			// 	nodo_actual->elemento = predecesor->elemento;
// 			// 	if (nodo_actual->izquierda == predecesor) {
//             //         nodo_actual->izquierda = predecesor->izquierda;
//             //     } else {
//             //         nodo_actual->derecha = predecesor->izquierda;
//             //     }
//             //     nodo_actual = predecesor;
// 				free(nodo_actual);
// 				arbol->tamanio--;
//             	return elemento;
// 			}

// 			//sin hijos
// 			if(nodo_actual->derecha == NULL && nodo_actual->izquierda == NULL){
// 				printf("SIN HIJOS\n");
// 				printf("Nodo raiz: %p\n", (void *)arbol->nodo_raiz);
// 				printf("Nodo actual: %p\n", (void *)nodo_actual);
// 				printf("Nodo padre: %p\n", (void *)nodo_padre);
// 				if(nodo_padre == NULL){
// 					arbol->nodo_raiz = NULL;
// 					printf("Nodo padre: NULL\n");
// 					printf("Nodo raiz: %p\n", (void *)arbol->nodo_raiz);
// 				} else if (nodo_padre->izquierda == nodo_actual) {
// 					nodo_padre->izquierda = NULL;
// 				} else {
// 					nodo_padre->derecha = NULL;
// 				}
// 				free(nodo_actual);
// 				arbol->tamanio--;
// 				printf(arbol->nodo_raiz == NULL ? "Nodo raiz: NULL\n" : "Nodo raiz: %p\n", (void *)arbol->nodo_raiz);
// 				return elemento;
// 			}

// 			//con un hijo
// 			if (!nodo_actual->izquierda || !nodo_actual->derecha) {
// 				printf("UN HIJO\n");
//                 nodo_abb_t *nodo_hijo = nodo_actual->izquierda ? nodo_actual->izquierda : nodo_actual->derecha;
//                 if (!nodo_padre) {
//                     arbol->nodo_raiz = nodo_hijo;
//                 } else if (nodo_padre->izquierda == nodo_actual) {
//                     nodo_padre->izquierda = nodo_hijo;
//                 } else {
//                     nodo_padre->derecha = nodo_hijo;
//                 }
// 				free(nodo_actual);
// 				arbol->tamanio--;
// 				return elemento;
// 			}
// 		}
// 		nodo_padre = nodo_actual;
// 		if(comparador < 0)
// 			nodo_actual = nodo_actual->izquierda;
// 		else
// 			nodo_actual = nodo_actual->derecha;
// 	}
// 	return NULL;
}

bool abb_vacio(abb_t *arbol)
{
	if(!arbol)
		return true;

	return arbol->nodo_raiz == NULL;
}

size_t abb_tamanio(abb_t *arbol)
{
	if(!arbol)
		return 0;

	return arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
	if(!arbol) return;

	nodo_destruir(arbol->nodo_raiz);
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if(!arbol) return;

	nodo_destruir(arbol->nodo_raiz);
	if(destructor){
		destructor(arbol->nodo_raiz->elemento);
	}
	free(arbol);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	return 0;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	return 0;
}
