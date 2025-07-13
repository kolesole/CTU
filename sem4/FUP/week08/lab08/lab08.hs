-- :{
separate :: [Int] -> ([Int], [Int])
separate [] = ([], [])
separate [x] = ([x], [])
separate (x:y:xs) = (x:ods, y:evs) where (ods, evs) = separate xs 
-- :}

-- :{
numToStr :: Int -> Int -> String
numToStr n radix = if n < radix then [chars !! n]
                   else (numToStr d radix) ++ [chars !! r]
                   where chars = ['0'..'9'] ++ ['A'..'F']
                         d = n `div` radix
                         r = n `mod` radix
-- :} 

-- :{
split :: Int -> [Int] -> [[Int]]
split n xs | length xs <= n = [xs]
           | otherwise = take n xs : split n (drop n xs) 

average_n :: Int -> [Int] -> [Float]
average_n n ys = let xss = split n ys
                 in [fromIntegral (sum xs) / fromIntegral (length xs) | xs <- xss]
-- :}

-- :{
copy :: Int -> String -> String
copy n str | n == 0 = []
           | otherwise = str ++ (copy (n-1) str) 
-- :}

-- :{
luhnDouble :: Int -> Int
luhnDouble n = if n2 > 9 then n2 - 9  
               else n2
               where n2 = n * 2

luhn :: [Int] -> Bool
luhn lst = let (x, xs) = separate (reverse lst)
           in (sum (x ++ [luhnDouble xss | xss <- xs])) `mod` 10 == 0
-- :}
