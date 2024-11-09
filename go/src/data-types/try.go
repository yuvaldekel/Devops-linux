package main

import "fmt"

func main() {
	letters := [...]string{"A", "B", "C", "D", "E"}
	remove := 2

	if remove < len(letters) {

		fmt.Println("Before", letters, "Remove ", letters[remove])

		letters2 := append(letters[:remove], letters[remove+1:]...)

		fmt.Println("After", letters)
		fmt.Println("After", letters2)
	}

	for index, letter := range letters {
		fmt.Printf("%d, %s\n", index, letter)
	}
}
