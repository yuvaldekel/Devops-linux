SELECT * FROM shows JOIN genres ON shows.id = genres.show_id GROUP BY title ORDER BY title LIMIT 10;
SELECT * FROM shows JOIN genres ON shows.id = genres.show_id ORDER BY title LIMIT 10;
SELECT * FROM shows JOIN ratings ON shows.id = ratings.show_id WHERE title = 'The Office' ORDER BY rating DESC LIMIT 10;

SELECT title, rating FROM people 
JOIN stars ON people.id = stars.person_id
JOIN shows ON stars.show_id = shows.id
JOIN ratings ON shows.id = ratings.show_id WHERE name = 'Steve Carell' ORDER BY rating DESC;

SELECT title FROM people, stars, shows
WHERE people.id = stars.person_id
AND start.show_id = shows.idgenres ON shows
AND people.name = 'Steve Carell';