package main

import (
	"math"
//	"fmt"
)

type CryptoBuffer struct {
	capacity uint
	size uint
	data []byte
}

func MakeCryptoBuffer(capacity uint) *CryptoBuffer {
	res := new(CryptoBuffer)
	bytesCap := int(math.Ceil(float64(capacity)*5/8))
	res.data = make([]byte, bytesCap)
	res.capacity = capacity
	res.size = 0
	return res
}

func (b *CryptoBuffer) Write5Bits(value byte) {
	startByte := b.size * 5 / 8
	var startOffset uint = b.size * 5 % 8
	value = value & 31
	usesNextByte := startOffset > 3
	if !usesNextByte {
		b.data[startByte] |= value << (3-startOffset)
	} else {
		b.data[startByte] |= value >> (startOffset-3)
		b.data[startByte+1] |= value << (11-startOffset)
	}
	b.size += 1
}
