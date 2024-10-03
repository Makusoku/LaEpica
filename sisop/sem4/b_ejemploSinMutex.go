
package main

import(
	"fmt"
	"sync"
)

var(
	wg sync.WaitGroup
	ch1 chan struct{} = make(chan struct{}, 1)
	ch2 chan struct{} = make(chan struct{}, 1)
	ch3 chan struct{} = make(chan struct{}, 1)
	ch4 chan struct{} = make(chan struct{}, 1)
	ch5 chan struct{} = make(chan struct{}, 1)
	ch6 chan struct{} = make(chan struct{}, 1)
	x int
)

func caracter1(){
	for{
		<- ch1
		<- ch6 
		fmt.Printf("A")
		ch3 <- struct{}{}
		ch2 <- struct{}{}
	}
	wg.Done()
	
}

func caracter2(){
	for{
		<- ch2
		<- ch6
		fmt.Printf("B")
		ch3 <- struct{}{}
		ch1 <- struct{}{}
	}
	wg.Done()
}

func caracter3(){
	for{
		<- ch3
		fmt.Printf("C")
		ch4<-struct{}{}
	}
	wg.Done()
}

func caracter4(){
	for{
		<- ch4
		fmt.Printf("D")
		ch5<-struct{}{}
	}
	wg.Done()
}

func caracter5(){
	for{
		<- ch5
		fmt.Printf("E")
		ch6 <- struct{}{}
	}
	wg.Done()
}

func main(){
	wg.Add(5)
	ch1 <- struct{}{}
	ch6 <- struct{}{}
	go caracter1()
	go caracter2()
	go caracter3()
	go caracter4()
	go caracter5()
	wg.Wait()
	fmt.Println()
}