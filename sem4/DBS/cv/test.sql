SELECT *
FROM uzivatel
        INNER JOIN osobniudaje USING(id_uzivatel)
;

SELECT *
FROM uzivatel
        LEFT OUTER JOIN osobniudaje USING(id_uzivatel)
;

-- LIKE for strings ~ = , ale umoznuje %
-- = ... jeden vysledek
-- IN ... seznam vysledku
-- EXISTS
-- CONCAT
-- STRING_AGG
-- vse dotazy musi byt bez ID
