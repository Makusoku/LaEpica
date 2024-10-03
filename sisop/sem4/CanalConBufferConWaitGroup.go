package main

import (
	"fmt"
	"sync"
)

func main() {
	// Crear un canal con buffer de tamaño 3
	ch := make(chan int, 3)
	var wg sync.WaitGroup

	// Añadimos 1 al WaitGroup para la gorutina que envía datos
	wg.Add(1)

	// Gorutina que envía datos al canal
	go func() {
		defer wg.Done() // Avisa que ha terminado cuando finalice
		for i := 1; i <= 5; i++ {
			fmt.Printf("Enviando %d al canal...\n", i)
			ch <- i // Envía el valor al canal
			fmt.Printf("%d enviado al canal\n", i)
		}
		close(ch) // Cerramos el canal cuando terminamos de enviar los datos
	}()

	// Añadimos 1 al WaitGroup para la gorutina que recibe datos
	wg.Add(1)

	// Gorutina que recibe datos del canal
	go func() {
		defer wg.Done() // Avisa que ha terminado cuando finalice
		for val := range ch {
			fmt.Printf("Recibiendo %d del canal\n", val)
		}
	}()

	// Esperamos a que ambas gorutinas terminen
	wg.Wait()
	fmt.Println("Todas las gorutinas han terminado")
}
