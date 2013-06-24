package main

import (
	"fmt"
	"os"
	"flag"
	"crypto/sha1"
)

type ShaBuffer struct {
	data []byte
	originalLength int
	chunks []ShaChunk
}

type ShaChunk struct {
	data [512]byte
	words [80]uint32
}

/*
#define SHA1CircularShift(bits,word) \
                (((word) << (bits)) | ((word) >> (32-(bits))))
*/
func s(bits uint, word uint32) uint32 {
	return ((word << bits) | (word >> (32 - bits)))
}

func MakeShaBuffer(buf []byte) *ShaBuffer {
	shaBuf := new(ShaBuffer)
	shaBuf.originalLength = len(buf)
	newLen := len(buf) + 1
	if newLen % 64 != 56 {
		newLen = newLen + 56 - newLen % 64
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

func (b *ShaBuffer) chunkify() {
	numChunks := len(b.data)/64
	b.chunks = make([]ShaChunk, numChunks)
	for i := 0; i < numChunks; i++ {
		for j := 0; j < 64; j++ {
			b.chunks[i].data[j] = b.data[i*numChunks + j]
		}
		for j := 0; j < 16; j++ {
			bs := b.chunks[i].data[j*4 : j*4 + 4]
			b.chunks[i].words[j] = readBigEndianUInt(bs)
			fmt.Printf("%d: w[%d] = %s\n", i, j, HexString(bs))
		}
	}
}

func readBigEndianUInt(buf []byte) uint32 {
	var res uint32 = 0
	l := len(buf)
	for i := 0; i < l; i++ {
		res |= uint32(buf[l-i-1]) << (8*uint(i))
	}
	return res
}

func writeBigEndianUInt(n uint32, slice []byte) {
	for i := 0; i < 4; i++ {
		slice[3-i] = byte(n >> (8*uint(i)) & 0xFF)
	}
}

func ShaDigest(inbuf []byte) []byte {
	b := MakeShaBuffer(inbuf)
	//fmt.Printf("buffer %s\n", 
	//	HexString(b.data)) 
	dig := make([]byte, 20)
	fmt.Printf("%s\n", HexString(dig))
	h0 := uint32(0x67452301)
	h1 := uint32(0xefcdab89)
	h2 := uint32(0x98badcfe)
	h3 := uint32(0x10325476)
	h4 := uint32(0xc3d2e1f0)
	b.chunkify()
	bs := make([]byte, 4)
	for cidx := range b.chunks {
		ch := b.chunks[cidx]
		for i := 16; i < 80; i++ {
			ch.words[i] = s(1, (ch.words[i-3] ^
				ch.words[i-8] ^
				ch.words[i-14] ^
				ch.words[i-16]))
			writeBigEndianUInt(ch.words[i], bs)
			fmt.Printf("%d: w[%d] = %s\n", cidx, i, HexString(bs))
		}
		a := h0
		b := h1
		c := h2
		d := h3
		e := h4
		var f uint32
		var k uint32

		for i := 0; i < 80; i++ {
			if i < 20 {
				f = uint32((b & c) | ((^b) & d))
				k = 0x5a827999
			} else if i < 40 {
				f = uint32(b ^ c ^ d)
				k = 0x6ed9eba1
			} else if i < 60 {
				f = uint32((b & c) | (b & d) | (c & d))
				k = 0x8f1bbcdc
			} else {
				f = uint32(b ^ c ^ d)
				k = 0xca62c1d6
			}
			tmp := uint32(s(5, a) + f + e + k + ch.words[i])
			e = d
			d = c
			c = s(30, b)
			b = a
			a = tmp
		}
		h0 = h0 + a
		h1 = h1 + b
		h2 = h2 + c
		h3 = h3 + d
		h4 = h4 + e
	}
	writeBigEndianUInt(h0, dig[0:4])
	writeBigEndianUInt(h1, dig[4:8])
	writeBigEndianUInt(h2, dig[8:12])
	writeBigEndianUInt(h3, dig[12:16])
	writeBigEndianUInt(h4, dig[16:20])
	return dig
}

func HexString(bs []byte) string {
	res := ""
	for i := range(bs) {
		res += fmt.Sprintf("%02x", bs[i])
	}
	return res
}

func main() {
	flag.Parse()
	args := flag.Args()
	f, _ := os.Open(args[0])
	stat, _ := f.Stat()
	buffer := make([]byte, stat.Size())
	f.Read(buffer)
	dig := ShaDigest(buffer)
	fmt.Printf("%s\n", HexString(dig))

	d := sha1.New()
	d.Write(buffer)
	fmt.Printf("%s\n", HexString(d.Sum(nil)))

}
