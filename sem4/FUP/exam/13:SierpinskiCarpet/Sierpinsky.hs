cut :: Int -> Int -> [a] -> [a]
cut st end = take (end-st) . drop st

genEmpty :: Int -> [String]
genEmpty n = replicate n $ replicate n ' '

genCarpet :: Int -> [String]
genCarpet 0 = ["#"]
genCarpet n = let prev   = genCarpet (n - 1)
                  size   = length prev 
                  helper = zipWith3 (\x y z -> x ++ y ++ z)
                  upper  = helper prev prev prev  
                  middle = helper prev (genEmpty size) prev 
               in upper ++ middle ++ upper 

{-main :: IO ()
main = do putStrLn "Enter n:"
          n <- read <$> getLine
          let carpet = genCarpet n 
          putStrLn "Enter row1 row2 col1 col2:"
          [r1, r2, c1, c2] <- map read . words <$> getLine
          mapM_ (putStrLn . cut c1 c2) $ cut r1 r2 carpet
-}

main :: IO ()
main = do putStrLn "Enter n:"
          n <- read <$> getLine 
          let carpet = genCarpet n
          putStrLn "Enter row1 row2 col1 col2"
          [r1, r2, c1, c2] <- map read . words <$> getLine
          mapM_ (putStrLn . cut c1 c2) $ cut r1 r2 carpet 
