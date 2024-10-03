package main
import "fmt"
func main() {
    naturals := make(chan int)
    squares := make(chan int)
    // CONTADOR
    go func() {
        for x := 0; x < 20; x++ {
            naturals <- x
        }
        close(naturals)
    }()
    // CUADRADO
    go func() {
        for x := range naturals {
            squares <- x * x
        }
        close(squares)
    }()
    // Printer (in main goroutine)
    for x := range squares {
        fmt.Println(x)
    }
}
