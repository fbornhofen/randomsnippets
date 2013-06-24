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
