<p align="center" style="font-size:24pt; font-bold:true">Análisis de Algoritmos</p>
<p align="center" style="font-size:20pt; font-bold:true">Proyecto 3</p>
<p align="center" style="font-size:14pt; font-bold:true">Rodrigo Alexander Richards Valenzuela</p>
<p align="center" style="font-size:14pt; font-bold:true">Matrícula: 2016404813</p>
<p align="center" style="font-size:14pt; font-bold:true">Felipe Alejandro Cerda Saavedra</p>
<p align="center" style="font-size:14pt; font-bold:true">Matrícula: 2019060121</p>

<div style="page-break-after: always;"></div>

# Descripción

Este proyecto consiste en aplicar las técnicas de programación dinámica y aproximación para resolver el problema de la mochila 0-1. Este problema es NP-Complete en general, aunque usando programación dinámica se considera pseudo-polinomial.

Considere una mochila 0-1 con capacidad máxima $C$ con $n$ objetos posibles de agregar los cuales son identificados mediante un número $i\in N = \{1, 2, 3, ...,  n\}$. Además, cada objeto tiene un peso $p_{i}$ y un valor $v_{i}$. El problema de la mochila consiste en elegir el subconjunto de los $n$ objetos que maximiza el valor acumulado o ganancia de los objetos cuyo peso acumulado no supera la capacidad $C$ de la mochila, tal como se expresa a continuación:

$M(C) = max \Sigma_{i \in N}x_{i}v_{i}$
tal que  $\Sigma_{i \in N}x_{i}v_{i} \leq C$
$x_{i} \in {0, 1} \forall i \in N$

Asuma que $v_{i} \in N$ y $p_{i} \in N$


**a) Describa y proporcione una solución usando programación dinámica y establezca su complejidad asintótica del tiempo de ejecución.**

Resolveremos el problema siguiendo esta estrategia

1. Proporcionaremos una solución recursiva
2. Mejoramos lo anterior memorizando algunos de los resultados intermedios   

Consideremos el siguiente algoritmo:
```kotlin
// n numero de items a considerar
// C capacidad de la mochila
// p[] arreglo con los pesos
// v[] arreglo con los valores
fun KS(n, C)
    if (n == 0 || c == 0)
        result = 0
    else if (p[n] > C)
        result = KS(n-1, C)
    else
        tmp1 = KS(n-1, C)
        tmp2 = v[n] + KS(n-1, C - p[n])
        result = max(tmp1, tmp2)
    return result
```

Es sencillo notar que este algoritmo resuelve el problema de la mochila. Sin embargo, es muy ineficiente. A continuación veremos por qué:

Para una mochila de Capacidad $C = 10$ y considerando la siguiente tabla con pesos y valores. 


|Item| It1 | It2 | It3 | It4 | It5 |
|--|--|--|--|--|--|
| Peso | 1 | 2 | 3 | 2 | 5 |
| Valor | 5 | 1 | 3 | 4 | 2 |

Partiendo desde 5, analicemos el árbol de decisiones que representa el algoritmo. Este árbol se genera por las llamadas recursivas:

```kotlin
tmp1 = KS(n-1, C) // No se incluye item n en la mochila
tmp2 = v[n] + KS(n-1, C - p[n]) // Si se incluye item n en la mochila
```

![alt image](./img/mochila_sin_memoization.png)

Como vemos, la complejidad de este algoritmo es $O(2^n)$. 

Ahora modificaremos el algoritmo para hacerlo más eficiente mediante memorización.

```kotlin
// n numero de items a considerar
// C capacidad de la mochila
// p[] arreglo con los pesos
// v[] arreglo con los valores
// mem[n][C] arreglo donde guardamos los resultados parciales

// inicializamos el arreglo mem[n][C] con null para cada elemento
fun KS(n, C)
    if (mem[n][C] != null)
        return mem[n][C]
    if (n == 0 || c == 0)
        result = 0
    else if (p[n] > C)
        result = KS(n-1, C)
    else
        tmp1 = KS(n-1, C)
        tmp2 = v[n] + KS(n-1, C - p[n])
        result = max(tmp1, tmp2)
    mem[n][C] = result // El máximo número de veces que tenemos que hacer esta operación es (n*C)
    return result
```
Ahora calcularemos el valor de cada uno una sola vez y las siguientes veces obtendremos su valor desde la memoria. Con esto logramos que el algoritmo se ejecute en $O(n*C)$. Esto es mucho mejor que el resultado anterior.

**b) ¿Qué puede decir respecto al tiempo de ejecución? Observa alguna diferencia a la forma en la cual hemos analizado el tiempo de ejecución en unidades anteriores? Establezca de que manera la complejidad obtenida para el problema puede incidir en la complejidad en términos de tiempo de ejecución. La complejidad asociada a la solución obtenida normalmente se conoce como pseudo polinomial. Investigue y comente por qué la solución para la mochila 0-1 se dice que es pseudo polinomial.** 

En el ejemplo anterior utilizamos un arreglo para guardar resultados intermedios y luego concluimos que el tiempo de ejecución es $O(n*C)$. Esto parece ser linear, sin embargo podemos encontrar casos en que esto no se cumple. Supongamos que $C = n!$, en este caso la complejidad de nuestro algoritmo es pero que cuando lo hicimos por fuerza bruta. De esta forma la complejidad del problema puede afectar la complejidad en términos de tiempo de ejecución, convirtiendo en una peor una solución teóricamente mejor.

**c) Implemente el algoritmo usando el enfoque bottom-up mediante tabulación.**

**d) Ahora, resuelva el problema de programación dinámica usando tabulación, pero esta vez en lugar de usar el peso en las columnas use los valores de los objetos. Describa la solución usando programación dinámica para este enfoque de solución.**

**e) Considere el mismo algoritmo anterior, pero ahora asuma que puede aceptar algo de error y no requiere obtener el óptimo. En este caso analice el caso en el cual los objetos se pueden agrupar por valor $\lfloor \frac{v_{i}}{x} \rfloor$, donde $x = (1 − \beta) \frac{V}{n}$ y $0 < \beta < 1$, y $V = \Sigma_{i}^{n}vi$. Esta solución conlleva a un algoritmo aproximado. Para este caso, implemente el algoritmo, analice el tiempo de ejecución asintótico del algoritmo en el peor caso, el error absoluto máximo y el factor de aproximación $ \rho (n) = \frac{V^*}{V_a}$, donde $V^*$ es la solución óptima y $V_a$ la solución aproximada.**

**f) Considere que la entrada se proporciona en un archivo de entrada donde cada linea contiene el siguiente formato:**
**$<n> <C> <lista$  $p_i$  $v_i>$**
**Y la salida asociada a cada Instancia de entrada debe ser:**
**$<n> <C> <lista$ $x_i>$** 
**Donde $n$ es el número de objetos, $C$ es la capacidad de la mochila, $p_i$ peso de objeto $i$, $v_i$ valor de objeto $i$, y $x_i \in \{0, 1\}$.**

**Ejemplo:** 
**Entrada** 
**4 100 34 169 23 152 62 44 2 224**

**Salida**
**4 545 1 1 0 1**