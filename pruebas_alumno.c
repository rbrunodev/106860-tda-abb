#include "src/abb.h"
#include <stdlib.h>
#include <stdio.h>
#include "src/abb_estructura_privada.h"
#include "pa2m.h"

int comparar_enteros(void *a, void *b) {
    int valor_a = *((int *)a);
    int valor_b = *((int *)b);

    if (valor_a < valor_b) return -1;
    if (valor_a > valor_b) return 1;
    return 0;
}

void crear_abb(void)
{
	printf("\nPruebas de creacion\n");
	abb_t *arbol = abb_crear(comparar_enteros);

	pa2m_afirmar(arbol != NULL, "Puedo crear un arbol");

	abb_destruir(arbol);
}

int main(void)
{
	pa2m_nuevo_grupo("------------ PRUEBAS DEL TDA ABB ------------");

	pa2m_nuevo_grupo("\n======================== Pruebas de creacion "
			 "========================");

	crear_abb();

	return pa2m_mostrar_reporte();
}
