package main

import(
    "fmt"
    "sync"
)

var(
    wg sync.WaitGroup
    ch11 chan struct{}  =  make(chan struct{}, 1)
    ch12 chan struct{}  =  make(chan struct{}, 1)    
    ch2 chan struct{}  =  make(chan struct{}, 1)
    ch3 chan struct{}  =  make(chan struct{}, 1)
    ch4 chan struct{}  =  make(chan struct{}, 1)        
)

func worker1(){
    fmt.Printf("A")
    wg.Done()
    ch2 <- struct{}{}
}

func worker2(){
    fmt.Printf("B")
    wg.Done()
    ch2 <- struct{}{}
}

func worker3(){
    <- ch2
    fmt.Printf("C")
    wg.Done()
    ch3 <- struct{}{}
}

func worker4(){
    <- ch3
    fmt.Printf("D")
    wg.Done()
    ch4 <- struct{}{}
}

func worker5(){
    <- ch4
    fmt.Printf("E")
    wg.Done()
}

func main(){
    
    for i := 1; i < 10; i++{
        wg.Add(4)
        for x := 0; x != 1; {
            select {
            case <-ch11:
                go worker1()
                for len(ch12) > 0 {
                    <-ch12
                }
                x = 1
            case <-ch12:
                go worker2()
                for len(ch11) > 0 {
                    <-ch11
                }
                x = 1
            default:
                ch11 <- struct{}{}
                ch12 <- struct{}{}
            }
        }
        go worker3()
        go worker4()
        go worker5()
        wg.Wait()
    }
    fmt.Printf("\n")
}