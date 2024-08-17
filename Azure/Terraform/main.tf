resource "azurerm_resource_group" "rg" {
  location = "east us"
  name     = "rg1"
}

resource "azurerm_resource_group" "second" {
  location = "east us"
  name     = "rg2"
}