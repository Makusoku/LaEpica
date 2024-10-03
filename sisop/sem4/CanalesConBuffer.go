package main

import (
	"fmt"
	"time"
)

func main() {
	// Crear un canal con buffer de tamaño 3
	ch := make(chan int, 3)

	// Función que envía datos al canal
	go func() {
		for i := 1; i <= 5; i++ {
			fmt.Printf("Enviando %d al canal...\n", i)
			ch <- i // Envía el valor al canal
			fmt.Printf("%d enviado al canal\n", i)
		}
		close(ch) // Cerramos el canal cuando terminamos de enviar los datos
	}()

	// Gorutina que recibe datos del canal
	go func() {
		for val := range ch {
			fmt.Printf("Recibiendo %d del canal\n", val)
			time.Sleep(1 * time.Second) // Simula un procesamiento lento
		}
	}()

	// Damos tiempo para que las gorutinas terminen
	time.Sleep(6 * time.Second)
}
