package main

import (
	"fmt"

	"github.com/yuvaldekel/manageAccounts"
)

func main() {
	employee := manageAccounts.Employee{manageAccounts.Account{"yuval", "dekel"}, 5.0}
	fmt.Printf("%s\n", employee)
}
