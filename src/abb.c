#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if(comparador == NULL)
		return NULL;

	abb_t *arbol = malloc(sizeof(abb_t));

	if (arbol == NULL)
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
		if (arbol->comparador(elemento, nodo_actual->elemento) <= 0){
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

	free(nodo);
	return arbol;
}

nodo_abb_t *buscar_nodo(nodo_abb_t *nodo, abb_t *arbol, void *elemento)
{
	if(nodo == NULL)
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

void *buscar_predecesor(nodo_abb_t *nodo_actual)
{
	if (!nodo_actual || !nodo_actual->izquierda)
        return NULL;

    nodo_abb_t *nodo_predecesor = nodo_actual->izquierda;

    while (nodo_predecesor->derecha) {
        nodo_predecesor = nodo_predecesor->derecha;
    }

    return nodo_predecesor->elemento;
}

nodo_abb_t *nodo_quitar(nodo_abb_t *nodo_actual, void *elemento){
	if(nodo_actual == NULL)
		return NULL;

	if(nodo_actual->derecha != NULL && nodo_actual->izquierda){
		void *predecesor = buscar_predecesor(nodo_actual);
		nodo_actual->elemento = predecesor;
		nodo_actual->izquierda = nodo_quitar(nodo_actual, predecesor);
		return nodo_actual->elemento;
	}

	nodo_abb_t *siguiente;
	if(nodo_actual->derecha != NULL){
		siguiente = nodo_actual->derecha;
	}
	else{
		siguiente = nodo_actual->izquierda;
	}

	free(nodo_actual);
	return siguiente->elemento;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if(arbol == NULL)
		return NULL;
	
	nodo_abb_t *nodo = buscar_nodo(arbol->nodo_raiz, arbol, elemento);

	if(nodo == NULL)
		return NULL;
	
	nodo_abb_t *nodo_quitado = nodo_quitar(nodo, elemento);
	if(nodo_quitado != NULL){
		arbol->tamanio--;
		return nodo_quitado->elemento;
	}

	return NULL;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if(arbol == NULL)
		return NULL;
	
	nodo_abb_t *nodo = buscar_nodo(arbol->nodo_raiz, arbol, elemento);
	return nodo != NULL ? nodo->elemento : NULL;
}

bool abb_vacio(abb_t *arbol)
{
	if(arbol == NULL)
		return true;

	if(arbol->nodo_raiz == NULL)
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
