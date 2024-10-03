package main

import (
	"fmt"
	"time"
)

func rutina (n int){
	fmt.Printf("Soy gorutina %d \n",n)
}

func main(){
	for x:=0 ; x<5;x++{
		go rutina(x)
	}
	time.Sleep(1*time.Second)
}