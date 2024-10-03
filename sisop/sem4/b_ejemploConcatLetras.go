package main

import (
	"fmt"
	"sync"
	"time"
)

var (
	wg    sync.WaitGroup
	mutex sync.Mutex
	step  int
	paso int
)

func A_letter() {
	defer wg.Done()
	mutex.Lock()
	if step == 0 {
		fmt.Printf("A")
		step++
	}
	mutex.Unlock()
}

func B_letter() {
	defer wg.Done()
	mutex.Lock()
	if step == 4 { // Después de "E", puede ir "B"
		fmt.Printf("B")
		step = 1 // Reiniciar para la secuencia "BCDE"
	}
	mutex.Unlock()
}

func C_letter() {
	defer wg.Done()
	mutex.Lock()
	if step == 1 { // Después de "A" o "B"
		fmt.Printf("C")
		step++
	}
	mutex.Unlock()
}

func D_letter() {
	defer wg.Done()
	mutex.Lock()
	if step == 2 { // Después de "C"
		fmt.Printf("D")
		step++
	}
	mutex.Unlock()
}

func E_letter() {
	defer wg.Done()
	mutex.Lock()
	if step == 3 { // Después de "D"
		fmt.Printf("E")
		if paso%2 == 0{
			step = 0 // Cambiar a B
		}else{
			step = 4 // Cambiar a A
		}
		paso++
	}
	mutex.Unlock()
}

func main() {
	step = 0 // Inicializamos el primer paso en 0 para comenzar con A
	paso = 1
	for {
		wg.Add(5)
		go A_letter()
		go B_letter()
		go C_letter()
		go D_letter()
		go E_letter()
		wg.Wait()
		time.Sleep(time.Second) // Pausa para mejor visibilidad de las salidas
	}
}