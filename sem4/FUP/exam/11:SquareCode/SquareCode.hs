module SquareCode ( encode ) where
import Data.Char
import Data.List 

normalize :: String -> String
normalize str = [toLower c | c <- str, isAlpha c]

getNumCols :: String -> Int
getNumCols str = ceiling $ sqrt $ fromIntegral $ length str

genRows :: String -> Int -> [String]
genRows str n | str == ""   = []
              | len < n     = [str ++ replicate (n - len) ' ']
              | otherwise   = take n str:genRows (drop n str) n
            where len = length str

encode :: String -> String
encode str = let norm  = normalize str
                 n     = getNumCols norm
                 rows  = transpose $ genRows norm n
                in unwords rows  