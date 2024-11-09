package main

import (
	"fmt"
)

func main() {

	master := make([]int, 4, 5)
	master[0] = 0
	master[1] = 1
	master[2] = 2
	master[3] = 3

	var slice1 []int
	slice1 = append(master, 4)
	slice1[0] = 0
	fmt.Println(slice1)
	fmt.Println(master)
}

func fibonacci() []int {

	var n int
	fmt.Scanf("%d", &n)

	if n < 2 {
		return make([]int, 0)
	}

	sequence := make([]int, n)

	sequence[0], sequence[1] = 1, 1

	for i := 2; i < n; i++ {
		sequence[i] = sequence[i-1] + sequence[i-2]
	}

	return sequence
}

func romanToArabic(numeral string) int {
	romanMap := map[rune]int{
		'M': 1000,
		'D': 500,
		'C': 100,
		'L': 50,
		'X': 10,
		'V': 5,
		'I': 1,
	}

	arabicVals := make([]int, len(numeral)+1)

	for index, digit := range numeral {
		if val, present := romanMap[digit]; present {
			arabicVals[index] = val
		} else {
			fmt.Printf("Error: The roman numeral %s has a bad digit: %c\n", numeral, digit)
			return 0
		}
	}

	total := 0

	fmt.Println(arabicVals)

	for index := 0; index < len(numeral); index++ {
		if arabicVals[index] < arabicVals[index+1] {
			arabicVals[index] = -arabicVals[index]
		}
		total += arabicVals[index]
	}

	return total
}
