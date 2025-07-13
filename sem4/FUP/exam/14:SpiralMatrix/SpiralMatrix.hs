module SpiralMatrix ( spiralMatrix ) where
type Matrix = [[Int]]

addMat :: Matrix -> Int -> Matrix
addMat m n = (map . map) (+ n) m 

wrap :: Int -> [Int] -> Int -> [Int]
wrap x y z = x : y ++ [z]

spiralMatrix :: Int -> Matrix
spiralMatrix 1 = [[1]]
spiralMatrix n = let smaller = addMat (spiralMatrix (n - 2)) (4 * n - 4)
                     firstl  = [1,2..n]
                     lastl   = [(3*n-2),(3*n-3)..(2*n-1)]
                     leftl   = [(4*n-4),(4*n-5)..(3*n-1)]
                     rightl  = [(n+1),(n+2)..(2*n-2)]
                     ext     = zipWith3 wrap leftl smaller rightl
                  in [firstl] ++ ext ++ [lastl]  