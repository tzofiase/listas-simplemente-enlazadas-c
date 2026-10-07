# listas-simimplemente-enlazadas-c
# Sistema de Gestión y Despacho de Paquetes en C

Implementación de un sistema de administración y procesamiento de encomiendas utilizando **listas simplemente enlazadas dinámicas** y **algoritmos recursivos**. Desarrollado en el marco de la cursada de Algoritmos y Estructuras de Datos en la Universidad de Palermo.

---

## 📌 Características y Funcionalidades

- **Carga Dinámica y Recursiva:** Ingreso de paquetes por teclado con cálculo recursivo en tiempo real del costo promedio de envío.
- **Filtrado y Creación de Sublistas:**
  - Generación de lista secundaria para paquetes con peso superior a 10 kg.
  - Generación de lista secundaria para envíos con costo inferior al promedio general.
- **Inserción Ordenada Unificada:** Incorporación de nuevos paquetes manteniendo el ordenamiento por código de seguimiento (`cod_seg`), contemplando inserción en cabeza, cuerpo y fin de lista.
- **Eliminación Condicional:** Búsqueda y liberación de memoria (`free`) de nodos que cumplan criterios específicos de destino y costo.
- **Cierre y Consolidación:** Cálculo recursivo de totales acumulados (peso y costo total) e inserción de un nodo centinela de cierre.

---

## 🛠️ Conceptos Técnicos Aplicados

- **Gestión de Memoria Dinámica:** Uso de punteros y llamadas a `malloc` y `free` para evitar fugas de memoria (*memory leaks*).
- **Estructuras de Datos:** Definición y manejo de tipos abstractos (`typedef struct`) enlazados mediante punteros autorreferenciados.
- **Recursividad vs. Iteración:** Implementación de funciones recursivas para carga, recorrido, filtrado y cálculo de acumulados, combinadas con iteración clásica para manipulaciones de punteros en inserción y borrado.

---

## 🚀 Compilación y Ejecución

El código puede compilarse con cualquier compilador estándar de C (como `gcc` en Linux, macOS o Windows mediante MinGW/WSL):

```bash
# Compilar el archivo
gcc gestion_paquetes.c -o gestion_paquetes

# Ejecutar el binario
./gestion_paquetes
