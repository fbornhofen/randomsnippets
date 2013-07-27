package main

import (
	"fmt"
	"strconv"
)

func isPalindrome(s string) bool {
	for i := 0; i < len(s)/2; i++ {
		if s[i] != s[len(s)-i-1] {
			return false
		}
	}
	return true
}


func main() {
	maxPal := 0
	for i := 100; i < 1000; i++ {
		for j := i; j < 1000; j++ {
			p := i*j
			s := strconv.Itoa(p)
			if isPalindrome(s) {
				if p > maxPal {
					maxPal = p
				}
			}
		}

	}
	fmt.Printf("%d\n", maxPal)
}


