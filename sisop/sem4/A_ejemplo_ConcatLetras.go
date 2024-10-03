package main

import (
	"fmt"
	"sync"
	"time"
)

var (
	wg sync.WaitGroup
	ch1 chan struct {} = make(chan struct{},1)
	ch2 chan struct {} = make(chan struct{},1)
	ch3 chan struct {} = make(chan struct{},1)
	ch4 chan struct {} = make(chan struct{},1)
	ch5 chan struct {} = make(chan struct{},1)
)

func A_letter(){
	<-ch5
	fmt.Printf("A")
	wg.Done()
	ch1<-struct{}{}
}

func B_letter(){
	<-ch1
	fmt.Printf("B")
	wg.Done()
	ch2<-struct{}{}
}

func C_letter(){
	<-ch2
	fmt.Printf("C")
	wg.Done()
	ch3 <- struct{}{}
}

func D_letter(){
	<-ch3
	fmt.Printf("D")
	wg.Done()
	ch4<-struct{}{}
}

func E_letter(){
	<-ch4
	fmt.Printf("E")
	wg.Done()
	ch5<-struct{}{}
}

func main(){
	ch5 <- struct{}{}
	for{
		wg.Add(5)
		go A_letter()
		go B_letter()
		go C_letter()
		go D_letter()
		go E_letter()
		wg.Wait()
		time.Sleep(time.Second) //para demorar la ejecucion debido a que imprime demasiado rapido
	}
}