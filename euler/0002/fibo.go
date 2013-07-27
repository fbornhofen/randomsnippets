package main

import "fmt"

func sumEvenFibos(a int32, b int32, max int32, sum int32) int32 {
	if a >= max {
		return sum
	}
	next := a + b
	newSum := sum
	if next & 1 == 0 {
		newSum += next
	}
	return sumEvenFibos(b, next, max, newSum) 
}

func main() {
	fmt.Printf("%d\n", sumEvenFibos(0, 1, 4000000, 0))
}