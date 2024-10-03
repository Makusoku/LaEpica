package main

import (
    "fmt"
    "sync"
    "time"
)

func ranaSalta(arr []int, id int, wg *sync.WaitGroup, mu *sync.Mutex, n int) {
    defer wg.Done()
    for {
        mu.Lock()
        pos := -1
        for i := 0; i < n; i++ {
            if arr[i] == id {
                pos = i
                break
            }
        }
        posVacio := -1
        for i := 0; i < n; i++ {
            if arr[i] == -1 {
                posVacio = i
                break
            }
        }
        if posVacio == pos+1 || posVacio == pos-1 {
            arr[pos], arr[posVacio] = arr[posVacio], arr[pos]
            fmt.Println("Intercambio", arr)
        } else if posVacio == pos+2 && arr[pos+1] != -1 {
            arr[pos], arr[posVacio] = arr[posVacio], arr[pos]
            fmt.Println("Salto", arr)
        } else if posVacio == pos-2 && arr[pos-1] != -1 {
            arr[pos], arr[posVacio] = arr[posVacio], arr[pos]
            fmt.Println("Salto", arr)
        }
        if arr[0] == 4 && arr[1] == 5 && arr[2] == 6 && arr[4] == 1 && arr[5] == 2 && arr[6] == 3 {
            mu.Unlock()
            break
        }
        mu.Unlock()
        time.Sleep(100 * time.Millisecond)
    }
}

func main() {
    var wg sync.WaitGroup
    var mu sync.Mutex
    n := 7
    arr := []int{1, 2, 3, -1, 4, 5, 6}
    fmt.Println("Estado inicial:", arr)
    for id := 1; id <= 6; id++ {
        wg.Add(1)
        go ranaSalta(arr, id, &wg, &mu, n)
    }
    wg.Wait()
    fmt.Println("Estado final:", arr)
}