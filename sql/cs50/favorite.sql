.mode table
SELECT COUNT(*) FROM favorite;
SELECT COUNT(DISTINCT(title)) FROM favorite;
SELECT DISTINCT(title) FROM favorite LIMIT 10;
SELECT title, COUNT(*) FROM favorite GROUP BY title ORDER BY COUNT(*) DESC LIMIT 5;
SELECT title, COUNT(*) FROM favorite WHERE title ='The Office';