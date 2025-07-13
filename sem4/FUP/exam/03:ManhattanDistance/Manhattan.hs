module Manhattan (grid) where
import Data.Char
import Data.List

getChar (x, _, _) = x
getCol (_, x, _) = x  
getRow (_, _, x) = x

manh :: (Int, Int) -> (Int, Int) -> Int
manh (x1, y1) (x2, y2) = abs (x1 - x2) + abs (y1 - y2)

sortDists :: [(Char, Int)] -> [(Char, Int)]
sortDists = sortBy (\(_, x) (_, y) -> compare x y)

dists :: [(Char, Int, Int)] -> (Int, Int) -> [(Char, Int)]
dists points (x, y) = map (\(c, a, b) -> (c, manh (x, y) (a, b))) points 

finalize :: [(Char, Int)] -> Char
finalize ((ch, 0):_) = ch 
finalize ((ch, _):[]) = toLower ch 
finalize ((ch1, d1):(ch2, d2):_) = if d1 == d2 then '.' else toLower ch1 

grid :: [(Char,Int,Int)] -> [[Char]]
grid points = let fin  = finalize . sortDists . dists points
                  rows = maximum (map getRow points)
                  cols = maximum (map getCol points)
                in [[fin (col, row) | col <- [0..cols]] | row <- [0..rows]] 

points :: [(Char, Int, Int)]
points = [
       ('A', 1, 1),
       ('B', 1, 6),
       ('C', 8, 3),
       ('D', 3, 4),
       ('E', 5, 5),
       ('F', 8, 9)]
