from sqlite3 import connect


def main():        
    db = connect("../cs50/db/favorite.db")

    rows = db.execute("SELECT COUNT(*) AS n FROM favorite")
    for row in rows:
        print(f"count = {row[0]}")

    favorite_title = input("Favorite: ")

    if not favorite_title.endswith("'"):
        rows = db.execute(f"SELECT COUNT(*) FROM favorite WHERE title = '{favorite_title}'")
        for row in rows:
            print(f"count = {row[0]}")


if __name__ == "__main__":
    main()