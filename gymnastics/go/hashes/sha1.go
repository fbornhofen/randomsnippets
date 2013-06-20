package main

import (
	"fmt"
)

type ShaBuffer struct {
	data []byte
	originalLength int
}

func MakeShaBuffer(buf []byte) *ShaBuffer {
	shaBuf := new(ShaBuffer)
	shaBuf.originalLength = len(buf)
	newLen := len(buf) + 1
	if newLen % 512 != 0 {
		newLen = newLen + 512 - newLen % 512
	}
	newLen += 8 // original length
	fmt.Printf("newLen is %d\n", newLen)
	shaBuf.data = make([]byte, newLen)
	shaBuf.data[shaBuf.originalLength] = 0x80
	copy(shaBuf.data, buf)
	for i := shaBuf.originalLength + 1; i < newLen; i++ {
		shaBuf.data[i] = 0x0;
	}
	lenBits := shaBuf.originalLength * 8
	var start uint = uint(newLen) - 8
	var i uint
	for i = 0; i < 8; i++ {
		shaBuf.data[start+7-i] = byte((lenBits >> (8*i)) & 0xFF)
	}
	return shaBuf
}

func ShaDigest(inbuf []byte) []byte {
	b := MakeShaBuffer(inbuf)
	dig := make([]byte, 20)
	h0 := int64(0x67452301)
	h1 := int64(0xefcdab89)
	h2 := int64(0x98badcfe)
	h3 := int64(0x10325476)
	h4 := int64(0xc3d2e1f0)
	// do stuff
	return dig
}

func main() {
	buf := make([]byte, 512)
	buf[0] = 5
	sbuf := MakeShaBuffer(buf[:])
	fmt.Printf("%x\n", sbuf.data[0])
}
