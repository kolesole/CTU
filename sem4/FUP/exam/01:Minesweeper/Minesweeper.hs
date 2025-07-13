-- for converting ints to chars
import Data.Char (intToDigit)

slice:: Int -> Int -> [a] -> [a]
slice start end lst = drop start $ take end lst

neighbours :: Int -> Int -> [String] -> String
neighbours row col board = slice (row - 1) (row + 2) board >>= slice (col - 1) (col + 2)

finalize :: Char -> Int -> Char
finalize '*' _ = '*'
finalize  _  0 = '.'
finalize  _  n = intToDigit n

sweep :: [String] -> [String]
sweep board = let count neis        = length $ filter (=='*') neis
                  mines row col     = count $ neighbours row col board
                  fin field row col = finalize field $ mines row col
                  boardMap f        = zipWith (\row -> zipWith (\col field -> f field row col) [0..]) [0..]
               in boardMap fin board 

main = do
  input <- getContents
  mapM_ putStrLn (sweep (lines input))


test_board = ["..."
             ,".**"
             ,"..."]