package main

import (
	"fmt"
	"sync"
)

var(
	wg sync.WaitGroup
	ch1 chan struct {} = make(chan struct{},1) //Canales para pasar la continuidad de las secciones
	ch2 chan struct {} = make(chan struct{},1)
	ch3 chan struct {} = make(chan struct{},1)
)

func worker1(){
	<- ch1
	fmt.Printf("Sistemas ")
	wg.Done()
	ch2 <- struct{}{}
}
func worker2(){
	fmt.Printf("INF239 ")
	wg.Done()
	ch1 <- struct{}{} //No pasa parametro solo sirve para escribir la cadena
}
func worker3(){
	<-ch2
	fmt.Printf("OPERATIVOS ")
	wg.Done()
	ch3 <- struct{}{}
}
func worker4(){
	<-ch3
	fmt.Printf("\n")
	wg.Done()
}

func main(){
	wg.Add(4)
	go worker1()
	go worker2()
	go worker3()
	go worker4()
	wg.Wait()
}

