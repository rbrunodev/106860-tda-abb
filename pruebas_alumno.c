#include "src/abb.h"
#include <stdlib.h>
#include <stdio.h>
#include "src/abb_estructura_privada.h"
#include "pa2m.h"

static nodo_abb_t *buscar_predecesor(nodo_abb_t *nodo)
{
	while (nodo->derecha != NULL) {
		nodo = nodo->derecha;
	}
	return nodo;
}

int comparar_enteros(void *a, void *b)
{
	int valor_a = *((int *)a);
	int valor_b = *((int *)b);

	if (valor_a < valor_b)
		return -1;
	if (valor_a > valor_b)
		return 1;
	return 0;
}

void crear_abb(void)
{
	printf("\nPruebas de creacion\n");
	abb_t *arbol = abb_crear(comparar_enteros);

	pa2m_afirmar(arbol != NULL, "Puedo crear un árbol");
	pa2m_afirmar(arbol->nodo_raiz == NULL, "El árbol se crea vacío");
	pa2m_afirmar(arbol->tamanio == 0, "La cantidad de elementos es cero");
	pa2m_afirmar(arbol->nodo_raiz == NULL, "El elemento raíz es NULL");

	abb_destruir(arbol);
}

void insertar_abb()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elemento1 = 10;
	int elemento2 = 5;
	int elemento3 = 15;
	int elemento4 = 3;

	pa2m_afirmar(abb_insertar(arbol, &elemento1) != NULL,
		     "Puedo insertar un elemento en el árbol");
	pa2m_afirmar(*(int *)(arbol->nodo_raiz->elemento) == elemento1,
		     "El elemento queda como valor raíz");
	pa2m_afirmar(arbol->nodo_raiz != NULL, "El árbol ya no está vacío");
	pa2m_afirmar(arbol->tamanio == 1, "La cantidad de elementos es 1");

	pa2m_afirmar(abb_insertar(arbol, &elemento2) != NULL,
		     "Puedo insertar un elemento menor que el primero");
	pa2m_afirmar(arbol->nodo_raiz->izquierda != NULL,
		     "El árbol tiene un hijo izquierdo");
	pa2m_afirmar(arbol->nodo_raiz->derecha == NULL,
		     "El árbol no tiene hijo derecho");
	pa2m_afirmar(*(int *)(arbol->nodo_raiz->izquierda->elemento) ==
			     elemento2,
		     "El elemento queda a la izquierda de la raíz");
	pa2m_afirmar(arbol->tamanio == 2, "La cantidad de elementos es 2");

	pa2m_afirmar(abb_insertar(arbol, &elemento3) != NULL,
		     "Puedo insertar un elemento mayor que el primero");
	pa2m_afirmar(arbol->nodo_raiz->izquierda != NULL &&
			     arbol->nodo_raiz->derecha != NULL,
		     "El árbol tiene dos hijos");
	pa2m_afirmar(arbol->tamanio == 3, "La cantidad de elementos es 3");

	pa2m_afirmar(abb_insertar(arbol, &elemento4) != NULL,
		     "Puedo insertar un elemento menor a los que estaban");
	pa2m_afirmar(
		arbol->nodo_raiz->izquierda->izquierda != NULL,
		"El hijo izquierdo de la raiz ahora tiene un hijo izquierdo");
	pa2m_afirmar(arbol->tamanio == 4, "La cantidad de elementos es 4");

	abb_destruir(arbol);
}

void busqueda_abb()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elemento1 = 10;
	int elemento2 = 5;
	int elemento3 = 15;
	int elemento4 = 3;
	int elemento5 = 18;
	int elemento_inexistente = 4;

	abb_insertar(arbol, &elemento1);
	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	abb_insertar(arbol, &elemento5);

	pa2m_afirmar(*(int *)abb_buscar(arbol, &elemento1) == elemento1,
		     "Puedo buscar un elemento en el árbol (raíz)");
	pa2m_afirmar(*(int *)abb_buscar(arbol, &elemento2) == elemento2,
		     "Puedo buscar un elemento en el árbol (izquierda)");
	pa2m_afirmar(*(int *)abb_buscar(arbol, &elemento3) == elemento3,
		     "Puedo buscar un elemento en el árbol (derecha)");
	pa2m_afirmar(abb_buscar(arbol, &elemento_inexistente) == NULL,
		     "Puedo buscar un elemento que no está en el árbol");
	pa2m_afirmar(*(int *)abb_buscar(arbol, &elemento5) == elemento5,
		     "Puedo buscar otro elemento en el árbol (derecha)");

	abb_destruir(arbol);
}

void quitar_abb()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elemento1 = 10;
	int elemento2 = 5;
	int elemento3 = 15;
	int elemento4 = 3;
	int elemento5 = 2;
	int elemento6 = 18;

	abb_insertar(arbol, &elemento1);
	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	abb_insertar(arbol, &elemento5);
	abb_insertar(arbol, &elemento6);

	nodo_abb_t *predecesor_inorden = buscar_predecesor(arbol->nodo_raiz);

	pa2m_afirmar(abb_quitar(arbol, &elemento4) == &elemento4,
		     "Puedo quitar un elemento del árbol (nodo sin hijos)");
	pa2m_afirmar(abb_buscar(arbol, &elemento4) == NULL,
		     "El elemento eliminado ya no está en el árbol");

	pa2m_afirmar(abb_quitar(arbol, &elemento2) == &elemento2,
		     "Puedo quitar un elemento del árbol (nodo con un hijo)");
	pa2m_afirmar(abb_buscar(arbol, &elemento2) == NULL,
		     "El elemento eliminado ya no está en el árbol");

	pa2m_afirmar(abb_quitar(arbol, &elemento1) == &elemento1,
		     "Puedo quitar un elemento del árbol (nodo con dos hijos)");
	pa2m_afirmar(abb_buscar(arbol, &elemento1) == NULL,
		     "El elemento eliminado ya no está en el árbol");

	pa2m_afirmar(abb_quitar(arbol, &elemento6) == &elemento6,
		     "Puedo quitar un elemento del árbol (nodo con dos hijos)");
	pa2m_afirmar(abb_buscar(arbol, &elemento6) == NULL,
		     "El elemento eliminado ya no está en el árbol");

	pa2m_afirmar(abb_quitar(arbol, &elemento3) == &elemento3,
		     "Puedo quitar un elemento del árbol (raíz)");
	pa2m_afirmar(abb_buscar(arbol, &elemento3) == NULL,
		     "El elemento eliminado ya no está en el árbol");

	pa2m_afirmar(abb_quitar(arbol, &elemento5) == &elemento5,
		     "Puedo quitar un elemento del árbol (nodo sin hijos)");
	pa2m_afirmar(abb_buscar(arbol, &elemento5) == NULL,
		     "El elemento eliminado ya no está en el árbol");
	pa2m_afirmar(
		comparar_enteros(arbol->nodo_raiz->izquierda->derecha->elemento,
				 predecesor_inorden->elemento) == 0,
		"El nodo que queda en su lugar es el predecesor inorden");

	abb_destruir(arbol);
}

void abb_vacio_y_tamanio()
{
	abb_t *arbol = abb_crear(comparar_enteros);
	pa2m_afirmar(abb_vacio(arbol), "El árbol está vacío al crearlo");
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "El tamaño del árbol es 0 al crearlo");

	int elemento = 42;
	abb_insertar(arbol, &elemento);
	pa2m_afirmar(
		!abb_vacio(arbol),
		"El árbol ya no está vacío después de insertar un elemento");
	pa2m_afirmar(
		abb_tamanio(arbol) == 1,
		"El tamaño del árbol es 1 después de insertar un elemento");

	abb_destruir(arbol);
}

int main(void)
{
	pa2m_nuevo_grupo("------------ PRUEBAS DEL TDA ABB ------------");

	pa2m_nuevo_grupo("\n======================== Pruebas de creacion "
			 "========================");

	crear_abb();

	pa2m_nuevo_grupo("\n======================== Pruebas de insercion "
			 "========================");
	insertar_abb();

	pa2m_nuevo_grupo("\n======================== Pruebas de busqueda "
			 "========================");
	busqueda_abb();

	pa2m_nuevo_grupo("\n======================== Pruebas de eliminacion "
			 "========================");
	quitar_abb();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de arbol vacio y tamaño "
		"========================");
	abb_vacio_y_tamanio();

	return pa2m_mostrar_reporte();
}
