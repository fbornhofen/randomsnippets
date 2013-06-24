package main

import (
	"fmt"
	"math"
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
	shift := (2-idx) * 5
	v <<= shift
	m := ^uint16(31<<shift)
	t.data &= m
	t.data |= v
}

func (t *LetterTriplet) Get(idx uint) byte {
	shift := (2-idx) * 5
	v := byte((t.data & (31 << shift)) >> shift)
	if v == 0 {
		return ' '
	}
	return v + 'A' - 1
}

type Text struct {
	size uint
	capacity uint
	triplets []LetterTriplet
}

func MakeText(c uint) *Text {
	res := new(Text)
	res.capacity = c
	res.size = 0
	res.triplets = make([]LetterTriplet, int(math.Ceil(float64(c)/3.0)))
	return res
}

func MakeTextFromTriplets(xs []uint16) *Text {
	res := new(Text)
	res.capacity = uint(len(xs)) * 3
	res.size = res.capacity
	res.triplets = make([]LetterTriplet, len(xs))
	for i, v := range(xs) {
		res.triplets[i].data = v
	}
	return res
}

func (t *Text) SetText(s string) {
	for i, v := range(s) {
		t.triplets[i/3].Set(uint(i%3), byte(v))
	}
	t.size = uint(len(s))
}

func (t *Text) GetText() string {
	res := ""
	var l uint = 0
	for i, _ := range(t.triplets) {
		for j := 0; j < 3; j++ {
			if l == t.size {
				return res
			}
			l += 1
			res += string(rune(t.triplets[i].Get(uint(j))))
		}
	}
	return res
}

func (t *Text) Encrypt(e uint64, m uint64) {
	for i, v := range(t.triplets) {
		t.triplets[i].data = uint16(modPow(uint64(v.data), uint64(e), m))
	}
}

func modPow(b uint64, e uint64, m uint64) uint64 {
	var res uint64 = 1
	for e > 0 {
		if e % 2 == 1 {
			res = (res * b) % m
		}
		e = e >> 1
		b = (b * b) % m
	}
	return res
}

func main() {

	var m uint64 = 55189
	var e uint64 = 91
	var d uint64 = 41491

	msg := []uint16 {39491, 2899, 44184, 42704}
	txt := MakeTextFromTriplets(msg)
	txt.Encrypt(d, m)
	fmt.Printf("%s\n", txt.GetText())
	
	s := "MORGEN UNTER DER BRUECKE"
	txt = MakeText(uint(len(s)))
	txt.SetText(s)
	txt.Encrypt(e, m)
	for _, v := range(txt.triplets) {
		fmt.Printf("%d ", v.data)
	}
	fmt.Printf("\n")

	txt = MakeTextFromTriplets([]uint16{19382, 36564, 28624, 129, 20649, 9040, 319, 1409})
	txt.Encrypt(d, m)
	fmt.Printf("%s\n", txt.GetText())

}
