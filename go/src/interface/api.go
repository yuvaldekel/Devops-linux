package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
)

type dollars float32

type item struct {
	Name  string  `json:"Item"`
	Price dollars `json:"Price"`
}

func (d dollars) String() string {
	return fmt.Sprintf("$%.2f", d)
}

type database map[string]dollars

func (db database) ServeHTTP(w http.ResponseWriter, req *http.Request) {
	w.Header().Set("Content-Type", "application/json")

	items := make([]item, 0, len(db))

	for name, price := range db {

		items = append(items, item{name, price})
	}

	response, _ := json.Marshal(items)
	w.Write(response)
}

func main() {
	db := database{"Go T-Shirt": 25, "Go Jacket": 55}
	log.Fatal(http.ListenAndServe("localhost:8000", db))
}
