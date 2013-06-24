package main

import (
	"fmt"
)

type LetterTriplet struct {
	data uint16
}

func MakeLetterTriplet() *LetterTriplet {
	res := new(LetterTriplet)
	res.data = 0
	return res
}

func (t *LetterTriplet) Set(idx uint, value byte) {
	if value == ' ' {
		value = 0
	} else {
		value = value - 'A' + 1
	}
	v := uint16(value % 32)
	shift := idx * 5
	v <<= shift
	m := ^uint16(31<<shift)
	t.data &= m
	t.data |= v
}

func (t *LetterTriplet) Get(idx uint) byte {
	shift := idx * 5
	v := byte((t.data & (31 << shift)) >> shift)
	if v == 0 {
		return ' '
	}
	return v + 'A' - 1
}

func main() {

	fmt.Printf("%d\n", ^uint16(31<<2))
}
