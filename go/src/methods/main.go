package main

import "fmt"

type triangle struct {
	size int
}

func (t triangle) perimeter() int {
	return t.size * 3
}

func doubleSize(t *int) {
	*t *= 2
}

func main() {
	//t := triangle{3}
	var1 := 4
	doubleSize(&var1)

	fmt.Println(var1)
}
