package main

import (
	"fmt"
	"os"
	"sync"
)

var (
	 wg sync.WaitGroup
	chA chan struct{} = make(chan struct{}, 1)
	chB chan struct{} = make(chan struct{}, 1)
	chC chan struct{} = make(chan struct{}, 1)
	chD chan struct{} = make(chan struct{}, 1)
	chE chan struct{} = make(chan struct{}, 1)
	sequence []string	
	adminChan chan struct{}  = make(chan struct{}, 1)
)


func admin(){
	for{
		for _, letra := range sequence{
			switch letra{
			case "A":
				chA  <- struct{}{}
				<-adminChan
			case "B":
				chB <- struct{}{}
				<- adminChan
			case "C":
				chC <- struct{}{}
				<- adminChan
			case "D":
				chD <- struct{}{}
				<- adminChan
			case "E":
				chE <- struct{}{}
				<- adminChan
			}
		}
	}
}

func worker1(){
	for{
		<- chA
		fmt.Printf("A")
		adminChan <- struct{}{}
	}
	wg.Done()
}

func worker2(){
	for{
		<- chB
		fmt.Printf("B")
		adminChan <- struct{}{}
	}
	wg.Done()
}

func worker3(){
	for{
		<- chC
		fmt.Printf("C")
		adminChan <- struct{}{}
	}
	wg.Done()
}

func worker4(){
	for{
		<- chD
		fmt.Printf("D")
		adminChan <- struct{}{}
	}
	wg.Done()
}

func worker5(){
	for{
		<- chE
		fmt.Printf("E")
		adminChan <- struct{}{}
	}
	wg.Done()
}

func main(){
	
	var cadena string
	for i := 1; i < len(os.Args); i++{
		cadena = os.Args[i]
		switch cadena{
		case "A":
			fmt.Println(cadena)
		case "B":
			fmt.Println(cadena)
		case "C":
			fmt.Println(cadena)
		case "D":
			fmt.Println(cadena)
		case "E":
			fmt.Println(cadena)
		}
		sequence = append(sequence, os.Args[i])
	}
	wg.Add(5)
	go admin()
	go worker1()
	go worker2()
	go worker3()
	go worker4()
	go worker5()
	wg.Wait()
}