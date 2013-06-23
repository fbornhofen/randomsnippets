package main

import "testing"

func TestMakeCrypotBuffer(t *testing.T) {
	b := MakeCryptoBuffer(10)
	if 7 != len(b.data) {
		t.Errorf("expected len(data) to be 7, not %d", len(b.data))
	}
}

func TestWrite5Bits(t *testing.T) {
	b := MakeCryptoBuffer(10)
	b.Write5Bits(0)
	b.Write5Bits(31)
	if b.data[0] != 7 || b.data[1] != 192 {
		t.Errorf("expected first 2 bytes to be 7,192 (actual %d, %d)",
			b.data[0], b.data[1])
	}
}
