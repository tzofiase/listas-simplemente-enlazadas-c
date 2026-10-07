#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- Estructuras --- */
typedef struct paquetes {
    int cod_seg;
    char destino[40];
    int peso;
    int costo;
    struct paquetes *sig;
} nodop;

typedef struct max {
    int cod_seg;
    char destino[40];
    struct max *sig;
} nodod;

typedef struct min {
    int cod_seg;
    char destino[40];
    int costo;
    struct min *sig;
} nodom;

/* --- Carga Recursiva y Promedio --- */
int carga(nodop *h, int cant, int cont) {
    printf("Ingrese el codigo de seguimiento (0 para finalizar): ");
    scanf("%d", &h->cod_seg);
    if (h->cod_seg == 0) {
        h->sig = NULL;
        return cont > 0 ? (cant / cont) : 0;
    } else {
        cont = cont + 1;
        printf("Ingrese el destino: ");
        scanf(" %[^\n]", h->destino);
        printf("Ingrese el peso del paquete: ");
        scanf("%d", &h->peso);
        printf("Ingrese el costo del envio: ");
        scanf("%d", &h->costo);
        cant = cant + h->costo;
        h->sig = (nodop *)malloc(sizeof(nodop));
        return carga(h->sig, cant, cont);
    }
}

/* --- Mostrar Listas Recursivamente --- */
void mostrar(nodop *p) {
    if (p == NULL || p->sig == NULL) {
        return;
    }
    printf("\nCodigo de seguimiento: %d | Destino: %s | Peso: %d kg | Costo: $%d", 
           p->cod_seg, p->destino, p->peso, p->costo);
    mostrar(p->sig);
}

/* --- Filtrado a lista Mayor a 10kg --- */
void cargard(nodop *p, nodod *d) {
    if (p->sig == NULL) {
        d->sig = NULL;
        return;
    }
    if (p->peso > 10) {
        d->cod_seg = p->cod_seg;
        strcpy(d->destino, p->destino);
        d->sig = (nodod *)malloc(sizeof(nodod));
        cargard(p->sig, d->sig);
    } else {
        cargard(p->sig, d);
    }
}

/* --- Filtrado a lista Menor al Costo Promedio --- */
void cargarm(nodop *p, nodom *m, int pro) {
    if (p->sig == NULL) {
        m->sig = NULL;
        return;
    }
    if (p->costo < pro) {
        m->cod_seg = p->cod_seg;
        strcpy(m->destino, p->destino);
        m->costo = p->costo;
        m->sig = (nodom *)malloc(sizeof(nodom));
        cargarm(p->sig, m->sig, pro);
    } else {
        cargarm(p->sig, m, pro);
    }
}

void mostrard(nodod *d) {
    if (d == NULL || d->sig == NULL) return;
    printf("\nCodigo: %d | Destino: %s", d->cod_seg, d->destino);
    mostrard(d->sig);
}

void mostrarm(nodom *m) {
    if (m == NULL || m->sig == NULL) return;
    printf("\nCodigo: %d | Destino: %s | Costo: $%d", m->cod_seg, m->destino, m->costo);
    mostrarm(m->sig);
}

/* --- Insercion Ordenada Unificada por Codigo --- */
nodop* insertar_ordenado(nodop *p, int cod, char dest[], int pes, int cost) {
    nodop *nuevo = (nodop *)malloc(sizeof(nodop));
    nuevo->cod_seg = cod;
    strcpy(nuevo->destino, dest);
    nuevo->peso = pes;
    nuevo->costo = cost;
    nuevo->sig = NULL;

    // Caso 1: Insercion al inicio (nueva cabeza)
    if (p == NULL || cod < p->cod_seg) {
        nuevo->sig = p;
        return nuevo;
    }

    // Caso 2: Insercion en el medio o al final
    nodop *act = p;
    while (act->sig != NULL && act->sig->cod_seg != 0 && act->sig->cod_seg < cod) {
        act = act->sig;
    }
    nuevo->sig = act->sig;
    act->sig = nuevo;

    return p;
}

/* --- Eliminaciones Condicionales (Destino Rosario y Costo > 5000) --- */
nodop* eliminar_condicion(nodop *p) {
    nodop *aux;

    // Eliminar desde la cabeza
    while (p != NULL && p->sig != NULL && strcmp(p->destino, "Rosario") == 0 && p->costo > 5000) {
        aux = p->sig;
        free(p);
        p = aux;
    }

    // Eliminar en el resto de la lista
    nodop *act = p;
    while (act != NULL && act->sig != NULL && act->sig->sig != NULL) {
        if (strcmp(act->sig->destino, "Rosario") == 0 && act->sig->costo > 5000) {
            aux = act->sig->sig;
            free(act->sig);
            act->sig = aux;
        } else {
            act = act->sig;
        }
    }
    return p;
}

/* --- Calculo y Nodo Resumen Final --- */
void final(nodop *p, int pesos, int costos) {
    if (p->sig == NULL) {
        p->cod_seg = 9999;
        strcpy(p->destino, "TOTAL ACUMULADO");
        p->peso = pesos;
        p->costo = costos;
        return;
    }
    pesos += p->peso;
    costos += p->costo;
    final(p->sig, pesos, costos);
}

void mostrarf(nodop *p) {
    if (p == NULL) return;
    printf("\nCodigo: %d | Destino: %s | Peso: %d kg | Costo: $%d", 
           p->cod_seg, p->destino, p->peso, p->costo);
    if (p->sig != NULL) {
        mostrarf(p->sig);
    }
}

int main() {
    int pro, cod, pes, cost;
    char dest[40];
    nodop *p = (nodop *)malloc(sizeof(nodop));
    nodod *d = (nodod *)malloc(sizeof(nodod));
    nodom *m = (nodom *)malloc(sizeof(nodom));

    printf("=== CARGA INICIAL DE PAQUETES ===\n");
    pro = carga(p, 0, 0);

    printf("\n--- LISTA PRINCIPAL CARGADA ---");
    mostrar(p);

    printf("\n\n--- PAQUETES MAYORES A 10 KG ---");
    cargard(p, d);
    mostrard(d);

    printf("\n\n--- PAQUETES CON COSTO MENOR AL PROMEDIO ($%d) ---", pro);
    cargarm(p, m, pro);
    mostrarm(m);

    printf("\n\n=== INSERCION DE NUEVO PAQUETE ===");
    printf("\nIngrese codigo de seguimiento: ");
    scanf("%d", &cod);
    printf("Ingrese destino: ");
    scanf(" %[^\n]", dest);
    printf("Ingrese peso: ");
    scanf("%d", &pes);
    printf("Ingrese costo: ");
    scanf("%d", &cost);

    p = insertar_ordenado(p, cod, dest, pes, cost);
    printf("\n--- LISTA TRAS INSERCION ORDENADA ---");
    mostrar(p);

    printf("\n\n--- APLICANDO FILTRO DE ELIMINACION (Rosario y Costo > 5000) ---");
    p = eliminar_condicion(p);
    mostrar(p);

    printf("\n\n--- LISTA FINAL CON NODO RESUMEN ---");
    final(p, 0, 0);
    mostrarf(p);

    printf("\n");
    return 0;
}