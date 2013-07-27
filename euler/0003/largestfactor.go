package main

import (
	"fmt"
	"math"
)

func main() {
	n := int64(600851475143)
	root := int64(math.Sqrt(float64(n)))
	largestFactor := n
	for i := int64(2); i < root; i++ {
		done := false
		for ; n % i == 0 && !done; {
			n /= i
			largestFactor = i
			if n == 1 {
				done = true
			}
		}
	}
	fmt.Printf("%d\n", largestFactor)
}
