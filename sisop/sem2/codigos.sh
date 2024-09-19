#!/bin/bash

# Función para verificar si un número es par
es_par() {
    local num=$1
    if (( num % 2 == 0 )); then
        echo "$num es par."
    else
        echo "$num es impar."
    fi
}

# Función para verificar si un número es primo
es_primo() {
    local num=$1
    if (( num <= 1 )); then
        echo "$num no es primo."
        return
    fi

    for (( i = 2; i * i <= num; i++ )); do
        if (( num % i == 0 )); then
            echo "$num no es primo."
            return
        fi
    done

    echo "$num es primo."
}

# Función para imprimir la sucesión de Fibonacci hasta n términos
fibonacci() {
    local n=$1
    a=0
    b=1

    echo "Sucesión de Fibonacci hasta $n términos:"
    for (( i = 0; i < n; i++ )); do
        echo -n "$a "
        fn=$((a + b))
        a=$b
        b=$fn
    done
    echo
}

# Función para imprimir los primeros n números primos
primeros_primos() {
    local n=$1
    count=0
    num=2

    echo "Primeros $n números primos:"
    while (( count < n )); do
        if es_primo $num; then
            echo -n "$num "
            (( count++ ))
        fi
        (( num++ ))
    done
    echo
}

# Verificar que se han pasado los parámetros necesarios
if [ "$#" -ne 2 ]; then
    echo "Uso: $0 <número> <número de términos>"
    exit 1
fi

# Leer parámetros
numero=$1
n_terminos=$2

# Verificar si el número es par o impar
es_par $numero

# Verificar si el número es primo
es_primo $numero

# Imprimir la sucesión de Fibonacci hasta n términos
fibonacci $n_terminos

# Imprimir los primeros n números primos
primeros_primos $n_terminos

exit 0
