module Skyscrapers (bestView) where
import Data.Foldable (maximumBy)
import Data.Ord (comparing)
import Data.List (transpose)

wcity, ecity, ncity, scity :: [[Int]] -> [[Int]]
wcity city = city 
ecity city = fmap reverse city
ncity city = transpose city 
scity city = ecity $ ncity city

countRoofs :: [[Int]] -> Int
countRoofs city = let countInRow []      _ n = n
                      countInRow (x:xs) mh n = if x > mh then countInRow xs x (n+1)
                                                         else countInRow xs mh n
                   in sum $ map (\row -> countInRow row (-1) 0) city

bestView :: [[Int]] -> (Char, Int)
bestView city = let wnum = ('W', countRoofs $ wcity city)
                    enum = ('E', countRoofs $ ecity city)
                    nnum = ('N', countRoofs $ ncity city)
                    snum = ('S', countRoofs $ scity city)
                 in maximumBy (comparing snd) [wnum, enum, nnum, snum]

city :: [[Int]]
city = [[3, 3, 3],
        [1, 2, 3],
        [1, 2, 3]]
