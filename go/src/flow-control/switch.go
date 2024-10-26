package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	FizzBuzz()
}

func FizzBuzz() {

	three, five := 3, 5

	for num := 1; num <= 100; num++ {

		three--
		five--

		if five != 0 && three != 0 {
			fmt.Print(num)
		}
		if three == 0 {
			fmt.Print("Fizz")
			three = 3
		}
		if five == 0 {
			fmt.Print("Buzz")
			five = 5
		}

		println()

		/*switch num % 15 {
		case 0:
			fmt.Println("FizzBuzz")
		case 5, 10:
			fmt.Println("Buzz")
		case 3, 6, 9, 12:
			fmt.Println("Fizz")
		default:
			fmt.Println(num)
		}*/
	}
}

func highlow(high int, low int) {
	if high < low {
		fmt.Println("Panic!")
		panic("highlow() low greater than high")
	}
	defer fmt.Println("Deferred: highlow(", high, ",", low, ")")
	fmt.Println("Call: highlow(", high, ",", low, ")")

	highlow(high, low+1)
}

func empty() {

	var num int64
	//rand.Seed(10)
	for num != 5 {
		num = rand.Int63n(15)
		fmt.Println(num)
	}
}

func omit() {
	rand.Seed(time.Now().Unix())

	for i := 0; i < 10; i++ {

		r := rand.Float64()
		fmt.Print(r)
		switch {
		case r > 0.1:
			fmt.Println(" Common case, 90% of the time")
		default:
			fmt.Println(" 10% of the time")

		}
	}
}

func fall() {

	switch num := 15; {
	case num < 50:
		fmt.Printf("%d is less than 50\n", num)
		//fallthrough
	case num > 100:
		fmt.Printf("%d is greater than 100\n", num)
		//fallthrough
	case num < 200:
		fmt.Printf("%d is less than 200\n", num)
	}
}
