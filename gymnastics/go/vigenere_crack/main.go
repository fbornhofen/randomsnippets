package main

import (
	"fmt"
	"os"
	"flag"
)

func stripBuffer(b []byte) []byte {
	res := make([]byte, len(b))
	j := 0
	for _, c := range b {
		if c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' {
			res[j] = c
			j++
		}
	}
	return res[:j]
}

func collectNth(b []byte, n int) []byte {
	res := make([]byte, len(b)/n + 1)
	j := 0
	for i := 0; j < len(b); i++ {
		res[i] = b[j]
		j += n
	}
	return res
}

func main() {
	flag.Parse()
	args := flag.Args()
	if len(args) < 1 {
		fmt.Fprintf(os.Stderr, "missing filename\n")
		os.Exit(-1)
	}
	f, _ := os.Open(args[0])
	buf := make([]byte, 1024)
	freq := make(map[byte]int)
	r, _ := f.Read(buf)
	stripped := stripBuffer(buf[:r])
	for i := 0; i < len(stripped); i++ {
		freq[stripped[i]]++
	}
	for k, v := range freq {
		fmt.Printf("%c - %d\n", k, v)
	}
}