package main

import (
	"fmt"
	"os"
	"flag"
	"sort"
)

type FreqTuple struct {
	character byte
	count int
	percentage float32
}

type FreqTuples []*FreqTuple

func (f FreqTuples) Less(i int, j int) bool {
	// Sort in reverse order
	return f[i].count > f[j].count
}

func (f FreqTuples) Swap(i int, j int) {
	f[i], f[j] = f[j], f[i]
}

func (f FreqTuples) Len() int {
	return len(f)
}

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

func makeFrequencyTable(dict map[byte]int) FreqTuples {
	l := len(dict)
	fs := make(FreqTuples, l)
	i := 0
	for k, v := range dict {
		fs[i] = new(FreqTuple)
		fs[i].character = k
		fs[i].count = v
		fs[i].percentage = float32(v)/float32(l)
		i++
	}
	sort.Sort(fs)
	return fs
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
	sorted := makeFrequencyTable(freq)
	for _, v := range sorted {
		fmt.Printf("%c - %d (%f)\n", v.character, v.count, v.percentage)
	}
}