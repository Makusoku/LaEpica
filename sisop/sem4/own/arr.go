package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	var wg sync.WaitGroup
	var mu sync.Mutex

	arr := make([]int, 500)

	for i := 0; i < 500; i++ {
		arr[i] = -1
	}

	for id := 0; id < 20; id++ {
		wg.Add(1)
		go func(gorutinaID int) {
			defer wg.Done()
			for x := 0; x < 25; x++ {
				mu.Lock()
				for i := 0; i < 500; i++ {
					if arr[i] == -1 {
						arr[i] = gorutinaID
						break
					}
				}
				mu.Unlock()
				time.Sleep(100 * time.Millisecond)
			}

		}(id)
	}

	wg.Wait()

	for i := 0; i < 500; i++ {
		fmt.Printf("%d ", arr[i])
		if (i+1)%20 == 0 {
			fmt.Println()
		}
	}
}
