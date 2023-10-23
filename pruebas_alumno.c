#include "src/abb.h"
#include <stdlib.h>
#include <stdio.h>
#include "src/abb_estructura_privada.h"
#include "pa2m.h"

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

void destructor_entero(void *elemento)
{
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
	int elemento5 = 18;

	abb_insertar(arbol, &elemento1);
	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	abb_insertar(arbol, &elemento5);

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

	pa2m_afirmar(abb_quitar(arbol, &elemento5) == &elemento5,
		     "Puedo quitar un elemento del árbol (nodo con dos hijos)");
	pa2m_afirmar(abb_buscar(arbol, &elemento5) == NULL,
		     "El elemento eliminado ya no está en el árbol");

	pa2m_afirmar(abb_quitar(arbol, &elemento3) == &elemento3,
		     "Puedo quitar un elemento del árbol (raíz)");
	pa2m_afirmar(abb_buscar(arbol, &elemento3) == NULL,
		     "El elemento eliminado ya no está en el árbol");

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

void destruir_abb()
{
	abb_t *arbol_vacio = abb_crear(comparar_enteros);
	abb_destruir(arbol_vacio);
	pa2m_afirmar(1, "Árbol vacío destruido correctamente");

	abb_t *arbol_sin_destructor = abb_crear(comparar_enteros);
	int elemento1 = 42;
	abb_insertar(arbol_sin_destructor, &elemento1);
	abb_destruir(arbol_sin_destructor);
	pa2m_afirmar(1,
		     "Árbol no vacío sin destructor destruido correctamente");

	abb_t *arbol_con_destructor = abb_crear(comparar_enteros);
	int elemento2 = 10;
	abb_insertar(arbol_con_destructor, &elemento2);
	abb_destruir(arbol_con_destructor);
	pa2m_afirmar(1,
		     "Árbol no vacío con destructor destruido correctamente");

	abb_t *arbol_con_multiples_elementos = abb_crear(comparar_enteros);
	int elemento3 = 5;
	int elemento4 = 15;
	abb_insertar(arbol_con_multiples_elementos, &elemento3);
	abb_insertar(arbol_con_multiples_elementos, &elemento4);
	abb_destruir(arbol_con_multiples_elementos);
	pa2m_afirmar(
		1,
		"Árbol con múltiples elementos y destructor destruido correctamente");
}

void destruir_todo_abb()
{
	abb_t *arbol_vacio = abb_crear(comparar_enteros);
	abb_destruir_todo(arbol_vacio, destructor_entero);
	pa2m_afirmar(1, "Árbol vacío destruido completamente correctamente");

	abb_t *arbol_con_destructor = abb_crear(comparar_enteros);
	int elemento1 = 10;
	abb_insertar(arbol_con_destructor, &elemento1);
	abb_destruir_todo(arbol_con_destructor, destructor_entero);
	pa2m_afirmar(
		1,
		"Árbol no vacío con destructor destruido completamente correctamente");

	abb_t *arbol_con_multiples_elementos = abb_crear(comparar_enteros);
	int elemento2 = 5;
	int elemento3 = 15;

	abb_insertar(arbol_con_multiples_elementos, &elemento2);
	abb_insertar(arbol_con_multiples_elementos, &elemento3);
	abb_destruir_todo(arbol_con_multiples_elementos, destructor_entero);
	pa2m_afirmar(
		1,
		"Árbol con múltiples elementos y destructor destruido completamente correctamente");
}

void recorrido_abb()
{
	abb_t *arbol_vacio = abb_crear(comparar_enteros);
	int array_vacio[10];
	size_t cantidad_elementos_vacio =
		abb_recorrer(arbol_vacio, INORDEN, (void **)array_vacio, 10);
	pa2m_afirmar(cantidad_elementos_vacio == 0,
		     "Árbol vacío no tiene elementos para recorrer");

	abb_t *arbol_preorden = abb_crear(comparar_enteros);
	int elementos[] = { 10, 5, 15, 3, 7, 12, 18 };
	for (size_t i = 0; i < sizeof(elementos) / sizeof(int); i++) {
		abb_insertar(arbol_preorden, &elementos[i]);
	}

	//PREORDEN
	int array_preorden[10];
	int valor1 = 10;
	int valor2 = 5;
	int valor3 = 3;
	int valor4 = 7;
	int valor5 = 15;
	int valor6 = 12;
	int valor7 = 18;
	size_t cantidad_elementos_preorden = abb_recorrer(
		arbol_preorden, PREORDEN, (void **)array_preorden, 10);
	pa2m_afirmar(
		cantidad_elementos_preorden == 7,
		"Recorrido preorden en árbol no vacío devuelve la cantidad correcta de elementos");
	printf("Valor %d\n", comparar_enteros(&array_preorden[0], &valor1));
	pa2m_afirmar(
		arbol_preorden->comparador(&array_preorden[0], &valor1) == 0 &&
			comparar_enteros(&array_preorden[1], &valor2) == 0 &&
			comparar_enteros(&array_preorden[2], &valor3) == 0 &&
			comparar_enteros(&array_preorden[3], &valor4) == 0 &&
			comparar_enteros(&array_preorden[4], &valor5) == 0 &&
			comparar_enteros(&array_preorden[5], &valor6) == 0 &&
			comparar_enteros(&array_preorden[6], &valor7) == 0,
		"Recorrido preorden en árbol no vacío devuelve los elementos en el orden correcto");

	//INORDEN
	int array_inorden[10];
	size_t cantidad_elementos_inorden = abb_recorrer(
		arbol_preorden, INORDEN, (void **)array_inorden, 10);
	pa2m_afirmar(
		cantidad_elementos_inorden == 7,
		"Recorrido inorden en árbol no vacío devuelve la cantidad correcta de elementos");
	pa2m_afirmar(
		array_inorden[0] == 3 && array_inorden[1] == 5 &&
			array_inorden[2] == 7 && array_inorden[3] == 10 &&
			array_inorden[4] == 12 && array_inorden[5] == 15 &&
			array_inorden[6] == 18,
		"Recorrido inorden en árbol no vacío devuelve los elementos en el orden correcto");

	// POSTORDEN
	int array_postorden[10];
	size_t cantidad_elementos_postorden = abb_recorrer(
		arbol_preorden, POSTORDEN, (void **)array_postorden, 10);
	pa2m_afirmar(
		cantidad_elementos_postorden == 7,
		"Recorrido postorden en árbol no vacío devuelve la cantidad correcta de elementos");
	pa2m_afirmar(
		array_postorden[0] == 3 && array_postorden[1] == 7 &&
			array_postorden[2] == 5 && array_postorden[3] == 12 &&
			array_postorden[4] == 18 && array_postorden[5] == 15 &&
			array_postorden[6] == 10,
		"Recorrido postorden en árbol no vacío devuelve los elementos en el orden correcto");

	abb_destruir(arbol_vacio);
	abb_destruir(arbol_preorden);
}

bool funcion_visita(void *elemento, void *aux)
{
	int *contador = (int *)aux;
	(*contador)++;
	return true;
}

void con_cada_elemento_abb()
{
	abb_t *arbol_vacio = abb_crear(comparar_enteros);
	int contador_vacio = 0;
	size_t elementos_recorridos_vacio = abb_con_cada_elemento(
		arbol_vacio, INORDEN, funcion_visita, &contador_vacio);
	pa2m_afirmar(elementos_recorridos_vacio == 0,
		     "Árbol vacío no tiene elementos para recorrer");

	//INORDEN
	abb_t *arbol_inorden = abb_crear(comparar_enteros);
	int elementos_inorden[] = { 10, 5, 15, 3, 7, 12, 18 };
	for (size_t i = 0; i < sizeof(elementos_inorden) / sizeof(int); i++) {
		abb_insertar(arbol_inorden, &elementos_inorden[i]);
	}
	int contador_inorden = 0;
	size_t elementos_recorridos_inorden = abb_con_cada_elemento(
		arbol_inorden, INORDEN, funcion_visita, &contador_inorden);
	pa2m_afirmar(
		elementos_recorridos_inorden == 7,
		"Recorrido inorden en árbol no vacío devuelve la cantidad correcta de elementos");
	pa2m_afirmar(
		contador_inorden == 7,
		"Función auxiliar fue llamada la cantidad correcta de veces");

	//PREORDEN
	int contador_preorden = 0;
	size_t elementos_recorridos_preorden = abb_con_cada_elemento(
		arbol_inorden, PREORDEN, funcion_visita, &contador_preorden);
	pa2m_afirmar(
		elementos_recorridos_preorden == 7,
		"Recorrido preorden en árbol no vacío devuelve la cantidad correcta de elementos");
	pa2m_afirmar(
		contador_preorden == 7,
		"Función auxiliar fue llamada la cantidad correcta de veces");

	//POSTORDEN
	int contador_postorden = 0;
	size_t elementos_recorridos_postorden = abb_con_cada_elemento(
		arbol_inorden, POSTORDEN, funcion_visita, &contador_postorden);
	pa2m_afirmar(
		elementos_recorridos_postorden == 7,
		"Recorrido postorden en árbol no vacío devuelve la cantidad correcta de elementos");
	pa2m_afirmar(
		contador_postorden == 7,
		"Función auxiliar fue llamada la cantidad correcta de veces");

	abb_destruir(arbol_vacio);
	abb_destruir(arbol_inorden);
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

	pa2m_nuevo_grupo("\n======================== Pruebas de destruir arbol"
			 "========================");
	destruir_abb();

	pa2m_nuevo_grupo("\n======================== Pruebas de destruir todo"
			 "========================");
	destruir_todo_abb();

	pa2m_nuevo_grupo("\n======================== Pruebas de recorrido"
			 "========================");
	recorrido_abb();

	pa2m_nuevo_grupo("\n======================== Pruebas de iterador"
			 "========================");
	con_cada_elemento_abb();

	return pa2m_mostrar_reporte();
}
