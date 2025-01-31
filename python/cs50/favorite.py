PATH = r"/home/yuval/Documents/yuval/Devops-linux/python/cs50/favorite.csv"

def main():
    show ={}
    genre = {}
    with open(PATH, 'r') as file:

        next(file)
        for line in file:

            s = line.split(',')[1]
            s = s.strip()


            if '"' in line:
                g = line[line.find('"'):-1]
                g = g[1:-1]            
            else:
                g = line.split(',')[2]
                g = g.strip()

            s = s.lower()
            g = g.lower()

            if s in show:
                show[s] += 1
            else:
                show[s] = 1

            if g in genre:
                genre[g] += 1
            else:
                genre[g] = 1

    genre = {k: v for k, v in sorted(genre.items(), key=lambda item: item[1], reverse = True)}
    show = {k: v for k, v in sorted(show.items(), key=lambda item: item[1], reverse= True)}

    print(f"The most loved genre is {list(genre.keys())[0]} with {list(genre.values())[0]} votes.")
    print(f"The most loved title is {list(show.keys())[0]} with {list(show.values())[0]} votes.")

    print(f"The second most loved genre is {list(genre.keys())[1]} with {list(genre.values())[1]} votes.")
    print(f"The second most loved title is {list(show.keys())[1]} with {list(show.values())[1]} votes.")


if __name__ == "__main__":
    main()