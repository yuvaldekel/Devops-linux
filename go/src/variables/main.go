package main

import (
	"fmt"
	"math"
	"strconv"
)

func main() {
	firstName, lastName := "John", "Doe"
	age := 32

	fmt.Printf("%s %s age is %d\n", firstName, lastName, age)

	fmt.Println(math.MaxFloat32, math.MaxFloat64)

	i, _ := strconv.Atoi("-42")
	s := strconv.Itoa(-42)
	fmt.Println(i, s)
}
