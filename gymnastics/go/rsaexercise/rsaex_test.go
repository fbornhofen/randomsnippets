package main

import "testing"

func TestGetSet(t *testing.T) {
	tr := new(LetterTriplet)
	tr.Set(0, 'A')
	tr.Set(1, 'B')
	tr.Set(1, 'C')
	tr.Set(2, 'D')
	expect := []byte{'A', 'C', 'D'}
	for i := range(expect) {
		idx := uint(i)
		if tr.Get(idx) != expect[i] {
			t.Errorf("tr.Get(%d) is %d\n", i, tr.Get(idx))
		}
	}
}

func TestModPow(t *testing.T) {
	var r uint64 = modPow(5623, 4421, 6000)
	if r != 3223 {
		t.Errorf("expected r is %d, not 3223", r)
	}
}

func TestText(t *testing.T) {
	txt := MakeText(10)
	txt.SetText("HALLO WELT")
	if txt.GetText() != "HALLO WELT" {
		t.Errorf("expected 'HALLO WELT', got '%s'", txt.GetText())
	}
}
