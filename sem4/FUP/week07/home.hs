-- comment

{-
    block
-}

x :: Int
x = 3

{-
    "a" ++ "b"
    "ab"
    it :: [Char]
-} 

-- :{
factorial :: Int -> Int
factorial 0 = 1
factorial n = n * factorial (n - 1)
-- :}

-- :{
power :: Int -> (Int -> Int)
power _ 0 = 1
power n k = n * power n (k - 1)
-- :}

x +/+ y = 2*x + y

{-
    a +/+ b
    (+/+) a b
-}

{- 
    elem 1 [2, 1, 3]
    1 `elem` [2, 1, 3]
-}    

-- :{
discr1 :: Float -> Float -> Float -> Float
discr1 a b c =
    let x = b * b
        y = 4 * a * c
    in x - y 
-- :}

discr2 :: Float -> Float -> Float -> Float
discr2 a b c = x - y
    where x = b * b
          y = 4 * a * c


abs n = if n>=0 then n else -n

signum n = if n<0 then -1 else 
             if n == 0 then 0 else 1

abs2 n | n >= 0 = n
       | otherwise = -n


signum2 n | n < 0     = -1
          | n == 0    = 0
          | otherwise = 1

-- 1:2:3:4:5:[]

-- [1..10]

-- ['a'..'z']

-- [10,9..1]

-- [1,3..]

-- take, length, ++, reverse

head (x:_) = x

tail (_:xs) = xs

copyfirst s@(x:xs) = x:s

first (x,_,_) = x
second (_,x,_) = x
third (_,_,x) = x

f :: (Int, [Char], (Int, Char)) -> [Char]
f (1, (x:xs), (2,y)) = x:y:xs

-- [x^2 | x <- [1..5]]




