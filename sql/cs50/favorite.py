from cs50 import SQL # type: ignore


def main():        
    db = SQL("sqlite:///db/favorite.db")

    rows = db.execute("SELECT COUNT(*) AS n FROM favorite")
    for row in rows:
        print(f"count = {row['n']}")

    favorite_title = input("Favorite: ")
    rows = db.execute(f"SELECT COUNT(*) AS n FROM favorite WHERE title = ?", favorite_title)
    for row in rows:
        print(f"count = {row['n']}")


if __name__ == "__main__":
    main()