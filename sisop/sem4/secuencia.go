package main

import (
	"fmt"
	"sync"
	"time"
)

var (
	wg sync.WaitGroup
	c1 chan int = make(chan int, 1)
	c2 chan int = make(chan int, 1)
	c3 chan int = make(chan int, 1)
	c4 chan int = make(chan int, 1)
	c5 chan int = make(chan int, 1)
)

// grupo para AB
func worker1() {
	fmt.Printf("A")
	wg.Done()
	c1 <- 1
}

func worker2() {
	<-c1
	fmt.Printf("B")
	wg.Done()
	c2 <- 1
}

//FIN AB
//GRUPO PARA BA

func AUXILIAR_B() {
	fmt.Printf("B")
	wg.Done()
	c1 <- 1
}

func AUXILIAR_A() {
	<-c1
	fmt.Printf("A")
	wg.Done()
	c2 <- 1
}

// FIN BA
func worker3() {
	<-c2
	fmt.Printf("C")
	wg.Done()
	c3 <- 1
}

func worker4() {
	<-c3
	fmt.Printf("D")
	wg.Done()
	c4 <- 1
}

func worker5() {
	<-c4
	fmt.Printf("E")
	wg.Done()
	c5 <- 1
}

func main() {
	c5 <- 1
	i:=0
	for {
		wg.Add(5)
		if i%2 == 0{
			go worker1() // primer tipo de impresion con AB
			go worker2()
		}else{
			go AUXILIAR_B() //segundo tipo de impresion con BA
			go AUXILIAR_A()
		}
		go worker3()
		go worker4()
		go worker5()
		wg.Wait()
		time.Sleep(time.Second) // puesto para poder visualizar mejor la ejecucion y que no sea tan desordenada
		i++
	}
	fmt.Printf("\n")
}