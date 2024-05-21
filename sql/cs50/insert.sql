.mode table
SELECT genres, COUNT(*) FROM favorite WHERE genres = 'Comedy';
/*SELECT *, COUNT(*) FROM favorite WHERE title ='Kopa Rashit';*/
INSERT INTO favorite (title, genres) VALUES('Kopa Rashit', 'Comedy');
SELECT genres, COUNT(*) FROM favorite WHERE genres = 'Comedy';
/*SELECT *, COUNT(*) FROM favorite WHERE title ='Kopa Rashit';*/
DELETE FROM favorite WHERE title = 'Kopa Rashit';
SELECT genres, COUNT(*) FROM favorite WHERE genres = 'Comedy';
/*SELECT *, COUNT(*) FROM favorite WHERE title ='Kopa Rashit';*/