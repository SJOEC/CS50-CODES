-- In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Johnny Depp.

SELECT title FROM movies
    -- Movies where Johnny Deep starred
    WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name  = 'Johnny Depp'))
-- AND to compare both lists -- Movies where Helena Bonham Carter
        AND id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name  = 'Helena Bonham Carter'));
