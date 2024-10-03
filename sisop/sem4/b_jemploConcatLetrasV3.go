package main

import (
	"fmt"
	"sync"
)

var (
	wg sync.WaitGroup
	ch1 chan int = make(chan int, 1)
	ch2 chan struct{} = make(chan struct{}, 1)
	ch3 chan struct{} = make(chan struct{}, 1)
	ch4 chan struct{} = make (chan struct{}, 1)
)

//controlamos el tipo de impresion dependiendo del estado del canal
func worker1(){
     x := <- ch1
     if x == 1{
	fmt.Printf("A")
     }else{
	fmt.Printf("B")
     }
     ch2 <- struct{}{} 
     wg.Done()	
}

func worker2(){
     <- ch2
     fmt.Printf("C")
     ch3 <- struct{}{}
     wg.Done()
}

func worker3(){
     <- ch3
     fmt.Printf("D")
     ch4 <- struct{}{}
     wg.Done()
}

func worker4(){
    <- ch4
    fmt.Printf("E")
    wg.Done()
}

//Main thread signal when i % 5 == 0. This way we can change to the next type.
func main(){
	cycle := 0
	for i := 0; i < 16; i++{
            if i % 2 == 0 {
		ch1 <- 1
	    }else{
		ch1 <- 0
	    }
	    cycle = (cycle + 1) % 4
	    wg.Add(4)
	    go worker1()
	    go worker2()
	    go worker3()
	    go worker4()
	    wg.Wait()
	}
	fmt.Printf("\n")
	close(ch1)
	close(ch2)
	close(ch3)
	close(ch4)
}