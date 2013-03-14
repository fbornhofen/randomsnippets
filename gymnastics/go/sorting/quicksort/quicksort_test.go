package main

import "testing"

func TestSwap(t *testing.T) {
	a := []int{1,2,3,4}
	swap(a, 0, 2)
	if a[0] != 3 {
		t.Errorf("a[0] = %d, want 3", a[0])
	}
	if a[2] != 1 {
		t.Errorf("a[2] = %d, want 1", a[2])
	}
}

func TestPartition(t *testing.T) {
	a := []int{23, 25, 99, 55, 34, 72, 12}
	// p = 55
	// want {23, 25, 12, 34, 55, 72, 99}
	m := partition(a, 0, len(a)-1)
	if m != 4 {
		t.Errorf("m = %d, want 4", m)
	}
	if a[3] != 34 {
		t.Errorf("a[3] = %d, want 34", a[3])
	}
}

func assertSorted(a []int, t *testing.T) {
	for i := 0; i < len(a)-1; i++ {
		if a[i] > a[i+1] {
			t.Errorf("a is not sorted")
		}
	}
}

func TestQuicksortSorted(t *testing.T) {
	a := []int{1,2,3,4,5}
	Quicksort(a, 0, len(a)-1)
	assertSorted(a, t)
}

func TestQuicksortReversed(t *testing.T) {
	a := []int{5,4,3,2,1}
	Quicksort(a, 0, len(a)-1)
	assertSorted(a, t)
}

func TestQuicksort3(t *testing.T) {
	a := []int{1,2,1,1,1}
	Quicksort(a, 0, len(a)-1)
	assertSorted(a, t)
}