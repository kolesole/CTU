module Knights (isValid) where 

data Piece = Nil | Knight deriving Eq

isOnBoard :: Int -> Int -> Int -> Int -> Bool
isOnBoard mrow mcol nrow ncol = (nrow >= 0) && (nrow < mrow) &&
                                (ncol >= 0) && (ncol < mcol)

genPositions :: Int -> Int -> [(Int, Int)]
genPositions row col = let deltas  = [(-1, 2), (-1, -2), (1, 2), (1, -2),
                                      (2, -1), (-2, -1), (2, 1), (-2, 1)]
                           genFunc = \(nrow, ncol) -> (row + nrow, col + ncol)
                        in map genFunc deltas  

check :: [[Piece]] -> Int -> Int -> [(Int, Int)] -> Bool
check board mrow mcol positions = let checkFunc = \(row, col) -> not (isOnBoard mrow mcol row col)
                                                                 || (((board !! row) !! col) /= Knight)
                                    in all checkFunc positions

isValid :: [[Piece]] -> Bool
isValid board = let mrow = length board
                    mcol = length $ board !! 0
                    chck (r,c) = check board mrow mcol (genPositions r c) 
                    positions = [(row, col) | row <- [0..mrow-1], col <- [0..mcol-1], (board !! row) !! col == Knight]
                in all chck positions

-- isValid [[Knight, Nil, Nil ,Nil], [Nil, Nil, Nil, Knight], [Knight, Nil, Nil, Nil], [Nil, Knight, Nil, Nil]]
-- isValid [[Nil, Knight, Nil, Nil],[Nil, Nil, Nil, Knight],[Knight, Nil, Nil, Nil],[Nil, Nil, Knight, Nil]]