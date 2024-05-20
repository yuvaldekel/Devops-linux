PATH = r"/home/yuval/Documents/yuval/Devops-linux/python/cs50/favorite.txt"

def main():
    show ={}
    genre = {}
    with open(PATH, 'r') as file:

        for line in file:
            if line == "Timestamp,title,genres":
                print(1)
                continue

            s = line.split(',')[1]

            if '"' in line:
                g = line[line.find('"'):-1]
                g = g[1:-1]
            else:
                g = line.split(',')[2]

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

    print(genre)
    print(show)


if __name__ == "__main__":
    main()