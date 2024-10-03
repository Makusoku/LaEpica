package main

import (
	"fmt"
	"sync"
	"math/rand"
	"time"
)

var (
	wg            sync.WaitGroup
	mutex         sync.Mutex
	MAPA_DE_RANAS []int
	FIN_DE_juego  []int
)

func puedeMoverse(id_rana int, pos int) bool {
	if pos < 0 || pos >= len(MAPA_DE_RANAS) { // si se selecciona algún punto fuera de los límites
		return false
	}
	if id_rana <= len(MAPA_DE_RANAS)/2 { // Ranas verdes (mueven a la derecha)
		if pos == len(MAPA_DE_RANAS)-1 {
			return false
		}
		if pos+1 < len(MAPA_DE_RANAS) && MAPA_DE_RANAS[pos+1] == -1 {
			MAPA_DE_RANAS[pos+1] = MAPA_DE_RANAS[pos]
			MAPA_DE_RANAS[pos] = -1
			return true
		}
		if pos+2 < len(MAPA_DE_RANAS) && MAPA_DE_RANAS[pos+2] == -1 {
			MAPA_DE_RANAS[pos+2] = MAPA_DE_RANAS[pos]
			MAPA_DE_RANAS[pos] = -1
			return true
		}
	} else { // Ranas marrones (mueven a la izquierda)
		if pos == 0 {
			return false
		}
		if pos-1 >= 0 && MAPA_DE_RANAS[pos-1] == -1 {
			MAPA_DE_RANAS[pos-1] = MAPA_DE_RANAS[pos]
			MAPA_DE_RANAS[pos] = -1
			return true
		}
		if pos-2 >= 0 && MAPA_DE_RANAS[pos-2] == -1 {
			MAPA_DE_RANAS[pos-2] = MAPA_DE_RANAS[pos]
			MAPA_DE_RANAS[pos] = -1
			return true
		}
	}
	return false
}

func objetivo() bool {
	for i := 0; i < len(MAPA_DE_RANAS); i++ {
		if MAPA_DE_RANAS[i] != FIN_DE_juego[i] {
			return false // No se ha alcanzado el objetivo
		}
	}
	return true // El objetivo fue alcanzado satisfactoriamente
}

func Saltarin(num_rana int) {
	defer wg.Done()

	for {
		mutex.Lock()
		pos := findRanaIndex(num_rana)

		if puedeMoverse(num_rana, pos) {
			fmt.Println("Rana", num_rana, "se movió:", MAPA_DE_RANAS)

			if objetivo() {
				fmt.Println("Objetivo alcanzado:", MAPA_DE_RANAS)
				mutex.Unlock()
				return
			}
		}

		mutex.Unlock()
	}
}

func findRanaIndex(id int) int {
	for i, v := range MAPA_DE_RANAS {
		if v == id {
			return i
		}
	}
	return -1
}

func main() {
	numeroRanas := 6 // debe ser par
	rand.Seed(time.Now().UnixNano())
	wg.Add(numeroRanas)
	// Inicializar MAPA_DE_RANAS
	for i := 1; i <= numeroRanas; i++ {
		MAPA_DE_RANAS = append(MAPA_DE_RANAS, i)
		if i == numeroRanas/2 {
			MAPA_DE_RANAS = append(MAPA_DE_RANAS, -1)
		}
	}

	// Inicializar FIN_DE_juego
	for i := len(MAPA_DE_RANAS)/2 + 1; i < len(MAPA_DE_RANAS); i++ {
		FIN_DE_juego = append(FIN_DE_juego, MAPA_DE_RANAS[i])
	}
	FIN_DE_juego = append(FIN_DE_juego, -1)
	for i := 0; i < len(MAPA_DE_RANAS)/2; i++ {
		FIN_DE_juego = append(FIN_DE_juego, MAPA_DE_RANAS[i])
	}

	fmt.Println("Estado inicial:", MAPA_DE_RANAS)
	fmt.Println("Estado objetivo:", FIN_DE_juego)
	rand.Intn(max-min+1) + min
	// Crear gorutinas para cada rana
	for i := 1; i <= numeroRanas; i++ {
		if objetivo(){
			break
		}else{
			go Saltarin(i)

		}
	}

	wg.Wait()
	fmt.Println("Fin del juego.")
}