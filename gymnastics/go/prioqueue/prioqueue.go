package main

import "fmt"
import "time"
import "math/rand"

func main() {
	s := 10
	h := NewIntHeap(s)
	Populate(h, s)
	h.Print()
	for i := 0; i < s; i++ {
		fmt.Println(h.Dequeue())
	}
}

func Populate(q PriorityQueue, n int) {
	rand.Seed(time.Now().UnixNano()) 	
	for i := 0; i < n; i++ {
		q.Enqueue(rand.Intn(100))
	}
}

type PriorityQueue interface {
	Enqueue(Elem interface{}) bool
	Dequeue() interface{}
	Print()
}

type Heap interface {
	PriorityQueue
	Swap(Idx1 int, Idx2 int)
	Bubble(Idx int)
	Sink(Idx int)
}

type IntHeap struct {
	Elems []int
	Size int
	Capacity int
}

func NewIntHeap(Cap int) *IntHeap {
	h := new(IntHeap)
	h.Size = 0
	h.Capacity = Cap
	h.Elems = make([]int, Cap + 1)
	return h
}

func (h *IntHeap) Enqueue(Elem interface{}) bool {
	if h.Size == h.Capacity {
		return false
	}
	fmt.Println("Insert ", Elem)
	h.Size++
	h.Elems[h.Size] = Elem.(int)
	h.Bubble(h.Size)
	return true
}

func (h *IntHeap) Dequeue() interface{} {
	if h.Size < 1 {
		return 99999
	}
	res := h.Elems[1]
	h.Swap(1, h.Size)
	h.Size--
	h.Sink(1)
	return res
}

func (h *IntHeap) Print() {
	fmt.Println("Size is ", h.Size)
	for i := 1; i <= h.Size; i++ {
		fmt.Print(" ", h.Elems[i])
	}
	fmt.Println()
}

func (h *IntHeap) Swap(Idx1 int, Idx2 int) {
	tmp := h.Elems[Idx1]
	h.Elems[Idx1] = h.Elems[Idx2]
	h.Elems[Idx2] = tmp
}

func (h *IntHeap) Bubble(Idx int) {
	p := Idx / 2
	if p < 1 {
		return
	}
	if h.Elems[Idx] < h.Elems[p] {
		h.Swap(Idx, p)
		h.Bubble(p)
	}
}

func (h *IntHeap) Sink(Idx int) {
	c1 := Idx * 2
	c2 := Idx * 2 + 1
	next := c1 
	if c1 > h.Size {
		return
	}
	if c2 <= h.Size && h.Elems[c2] < h.Elems[c1]  {
		next = c2
	}
	if h.Elems[next] < h.Elems[Idx] {
		h.Swap(next, Idx)
		h.Sink(next)
	}
}
