package main

import "fmt"
import "math/rand"
import "time"

func main() {
	rand.Seed(time.Now().UnixNano())
	a := make([]int, 16)
	for i := 0; i < len(a); i++ {
		a[i] = rand.Intn(100)
	}
	printit(a)
	Quicksort(a, 0, len(a)-1)
	printit(a)
}

func printit(a []int) {
	for i := 0; i < len(a); i++ {
		fmt.Printf("%d ", a[i])
	}
	fmt.Println()
}

func swap(a []int, n int, m int) {
	tmp := a[n]
	a[n] = a[m]
	a[m] = tmp
}

func Quicksort(a []int, l int, h int) {
	if (l >= h) {
		return
	}
	p := a[(l+h) / 2]
	i := l
	j := h
	for i < j {
		for a[i] < p {
			i++
		}
		for a[j] > p {
			j--
		}
		swap(a, i, j)
		i++
		j--
	}
	Quicksort(a, l, j)
	Quicksort(a, i, h)
}

