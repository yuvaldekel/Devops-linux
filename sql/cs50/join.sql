SELECT * FROM shows JOIN genres ON shows.id = genres.show_id GROUP BY title ORDER BY title LIMIT 10;
SELECT * FROM shows JOIN genres ON shows.id = genres.show_id ORDER BY title LIMIT 10;
