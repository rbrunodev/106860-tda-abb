#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if(!comparador)
		return NULL;

	abb_t *arbol = malloc(sizeof(abb_t));

	if (!arbol)
		return NULL;

	arbol->nodo_raiz = NULL;
	arbol->comparador = comparador;
	arbol->tamanio = 0;

	return arbol;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if(!arbol)
		return NULL;

	nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t));

	if (!nodo)
		return NULL;

	if(!arbol->nodo_raiz){
		nodo->elemento = elemento;
		nodo->izquierda = NULL;
		nodo->derecha = NULL;
		arbol->nodo_raiz = nodo;
		arbol->tamanio++;
		return arbol;
	}

	nodo_abb_t *nodo_actual = arbol->nodo_raiz;

	while (nodo_actual) {
		if (arbol->comparador(elemento, nodo_actual->elemento) <= 0){
			if(!nodo_actual->izquierda){
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
			if(!nodo_actual->derecha){
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

	free(nodo);
	return arbol;
}

nodo_abb_t *buscar_nodo(nodo_abb_t *nodo, abb_t *arbol, void *elemento)
{
	if(!nodo)
		return NULL;

	int comparador = arbol->comparador(elemento, nodo->elemento);
	if(comparador == 0)
		return nodo;

	if(comparador < 0)
		return buscar_nodo(nodo->izquierda, arbol, elemento);
	else 
		return buscar_nodo(nodo->derecha, arbol, elemento);
	
	return NULL;
}

void *buscar_predecesor(nodo_abb_t *nodo)
{
    while (nodo->derecha != NULL) {
        nodo = nodo->derecha;
    }
    return nodo;
}

void *abb_quitar_recursivo(nodo_abb_t *nodo, void *elemento, abb_comparador comparador, size_t *tamanio) {
    if (!nodo)
        return NULL;

    int comparacion = comparador(elemento, nodo->elemento);

    if (comparacion < 0) {
        nodo->izquierda = abb_quitar_recursivo(nodo->izquierda, elemento, comparador, tamanio);
    } else if (comparacion > 0) {
        nodo->derecha = abb_quitar_recursivo(nodo->derecha, elemento, comparador, tamanio);
    } else {
        if (!nodo->izquierda) {
            nodo_abb_t *temp = nodo->derecha;
            free(nodo);
            (*tamanio)--;
            return temp; 
        } else if (!nodo->derecha) {
            nodo_abb_t *temp = nodo->izquierda;
            free(nodo);
            (*tamanio)--;
            return temp; 
        } else {
            nodo_abb_t *predecesor = buscar_predecesor(nodo->izquierda);
            nodo->elemento = predecesor->elemento;
            nodo->izquierda = abb_quitar_recursivo(nodo->izquierda, predecesor->elemento, comparador, tamanio);
        }
    }
    return nodo;
}

void *abb_quitar(abb_t *arbol, void *elemento) {
    if (!arbol || !arbol->nodo_raiz) {
        return NULL;
    }

	nodo_abb_t *nodo = buscar_nodo(arbol->nodo_raiz, arbol, elemento);
	if(!nodo)
		return NULL;

	if (arbol->comparador(elemento, arbol->nodo_raiz->elemento) == 0) {
        void *elemento_eliminado = arbol->nodo_raiz->elemento;
        nodo_abb_t *nuevo_raiz = abb_quitar_recursivo(arbol->nodo_raiz, elemento, arbol->comparador, &(arbol->tamanio));
        arbol->nodo_raiz = nuevo_raiz;
        return elemento_eliminado;
    }

    nodo_abb_t *nuevo_raiz = abb_quitar_recursivo(arbol->nodo_raiz, elemento, arbol->comparador, &(arbol->tamanio));
	
	if(!nuevo_raiz)
		return NULL;

    if (nuevo_raiz != arbol->nodo_raiz) {
        arbol->nodo_raiz = nuevo_raiz; 
    }

    return nuevo_raiz ? elemento : NULL;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if(!arbol)
		return NULL;
	
	nodo_abb_t *nodo = buscar_nodo(arbol->nodo_raiz, arbol, elemento);
	return nodo != NULL ? nodo->elemento : NULL;
}

bool abb_vacio(abb_t *arbol)
{
	if(!arbol)
		return true;

	if(!arbol->nodo_raiz)
		return true;

	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if(!arbol)
		return 0;

	return arbol->tamanio;
}

void nodo_destruir(nodo_abb_t *nodo, void (*destructor)(void *) ) {
    if (!nodo) return;

    nodo_destruir(nodo->izquierda, destructor);
    nodo_destruir(nodo->derecha, destructor);
	if (destructor && nodo->elemento) {
        destructor(nodo->elemento);
    }
    free(nodo);
}

void abb_destruir(abb_t *arbol)
{
	if(!arbol) return;

	if(abb_tamanio(arbol) == 0){
		free(arbol);
		return;
	}

	nodo_destruir(arbol->nodo_raiz, NULL);
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if(!arbol) return;

	if(abb_tamanio(arbol) == 0){
		free(arbol);
		return;
	}

	nodo_destruir(arbol->nodo_raiz, destructor);
	free(arbol);
}

size_t recorrer_preorden_fun(nodo_abb_t *actual, bool (*funcion)(void *, void *), void *aux, size_t *iterados)
{
	if(!actual)
		return true;

	(*iterados)++;
	if (!funcion(actual->elemento, aux)) {
		return false;
	}

	bool izquierda = recorrer_preorden_fun(actual->izquierda, funcion, aux, iterados);
	if(!izquierda)
		return false;

	bool derecha = recorrer_preorden_fun(actual->derecha, funcion, aux, iterados);
	if(!derecha)
		return false;
	
	return true;
}

bool recorrer_inorden_fun(nodo_abb_t *actual, bool (*funcion)(void *, void *), void *aux, size_t *iterados)
{
	if(!actual)
		return true;

	bool izquierda = recorrer_inorden_fun(actual->izquierda, funcion, aux, iterados);
	if(!izquierda)
		return false;

	(*iterados)++;
	if (!funcion(actual->elemento, aux)) {
		return false;
	}

	bool derecha = recorrer_inorden_fun(actual->derecha, funcion, aux, iterados);
	if(!derecha)
		return false;

	return true;
}

bool recorrer_postorden_fun(nodo_abb_t *actual, bool (*funcion)(void *, void *), void *aux, size_t *iterados)
{
	if(!actual)
		return true;

	bool izquierda = recorrer_postorden_fun(actual->izquierda, funcion, aux, iterados);
	if(!izquierda)
		return false;
	bool derecha = recorrer_postorden_fun(actual->derecha, funcion, aux, iterados);
	if(!derecha)
		return false;

	(*iterados)++;
	if (!funcion(actual->elemento, aux)) {
		return false;
	}

	return true;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!arbol || !arbol->nodo_raiz || !funcion) {
        return 0;
    }

	size_t funcion_invocada = 0;
	if (recorrido == INORDEN) {
		recorrer_inorden_fun(arbol->nodo_raiz, funcion, aux, &funcion_invocada);
	} else if (recorrido == PREORDEN) {
		recorrer_preorden_fun(arbol->nodo_raiz, funcion, aux, &funcion_invocada);
	} else if (recorrido == POSTORDEN) {
		recorrer_postorden_fun(arbol->nodo_raiz, funcion, aux, &funcion_invocada);
	}

	return funcion_invocada;
}

size_t recorrer_preorden(nodo_abb_t *actual, void **array, size_t tamanio_array, size_t indice)
{
	if (!actual|| indice >= tamanio_array) {
        return indice;
    }

	if (indice < tamanio_array) {
        array[indice] = actual->elemento;
        indice++;
    }

	if(actual->izquierda)
		indice = recorrer_preorden(actual->izquierda, array, tamanio_array, indice);

	if(actual->derecha)
		indice = recorrer_preorden(actual->derecha, array, tamanio_array, indice);

	return indice;
}

size_t recorrer_inorden(nodo_abb_t *actual, void **array, size_t tamanio_array, size_t indice)
{
	if(!actual || indice >= tamanio_array)
		return indice;

	if(actual->izquierda)
		indice = recorrer_inorden(actual->izquierda, array, tamanio_array, indice);

	if(indice < tamanio_array){
		array[indice] = actual->elemento;
		indice++;
	}

	if(actual->derecha)
		indice = recorrer_inorden(actual->derecha, array, tamanio_array, indice);

	return indice;
}

size_t recorrer_postorden(nodo_abb_t *actual, void **array, size_t tamanio_array, size_t indice)
{
	if(!actual || indice >= tamanio_array)
		return indice;

	if(actual->izquierda)
		indice = recorrer_postorden(actual->izquierda, array, tamanio_array, indice);

	if(actual->derecha)
		indice = recorrer_postorden(actual->derecha, array, tamanio_array, indice);

	if(indice < tamanio_array){
		array[indice] = actual->elemento;
		indice++;
	}
	return indice;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (!arbol || !arbol->nodo_raiz) {
        return 0;
    }

    size_t indice = 0;

    if (recorrido == INORDEN) {
        indice = recorrer_inorden(arbol->nodo_raiz, array, tamanio_array, indice);
    } else if (recorrido == PREORDEN) {
        indice = recorrer_preorden(arbol->nodo_raiz, array, tamanio_array, indice);
    } else if (recorrido == POSTORDEN) {
        indice = recorrer_postorden(arbol->nodo_raiz, array, tamanio_array, indice);
    }

    return indice;
}
