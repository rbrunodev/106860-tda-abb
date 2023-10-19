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

nodo_abb_t *crear_nodo(void *elemento) {
    nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t));

    if (nodo == NULL) {
        return NULL;
    }

    nodo->elemento = elemento;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    return nodo;
}

nodo_abb_t *insertar_recur(nodo_abb_t *nodo_actual, void *elemento, abb_t *arbol)
{
	if(nodo_actual == NULL){
		arbol->nodo_raiz = crear_nodo(elemento);
		return nodo_actual;
	} else {
		if(arbol->comparador(elemento, nodo_actual->elemento) <= 0){
			nodo_actual->izquierda = insertar_recur(nodo_actual->izquierda, elemento, arbol);
		} else {
			nodo_actual->derecha = insertar_recur(nodo_actual->derecha, elemento, arbol);
		}
	}
	
	return nodo_actual;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if(arbol == NULL)
		return NULL;
	
	insertar_recur(arbol->nodo_raiz, elemento, arbol);

	arbol->tamanio++;
	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	return elemento;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	return elemento;
}

bool abb_vacio(abb_t *arbol)
{
	return true;
}

size_t abb_tamanio(abb_t *arbol)
{
	return 0;
}

void abb_destruir(abb_t *arbol)
{
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
