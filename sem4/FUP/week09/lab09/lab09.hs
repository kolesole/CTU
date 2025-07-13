data Tree a = Leaf a 
            | Node (Tree a) (Tree a)

tree :: Tree Char
tree = Node (Node (Leaf 'a') (Node (Leaf 'b') (Leaf 'c'))) (Leaf 'd')        

-- :{
-- instance (Show a, Ord a) => Show (Tree a) where
instance (Show a) => Show (Tree a) where
    show (Leaf x) = "<Leaf " ++ (show x) ++ "/>"
    show (Node left right) = "<Node>" ++ (show left) ++ (show right) ++  "</Node>" 
-- :}

-- :{
treeDepth :: Tree a -> Int
treeDepth (Leaf _) = 1
treeDepth (Node left right) = 1 + ((treeDepth left) `max` (treeDepth right)) 
-- :}

-- :{
labelHlp :: Tree a -> Int -> (Tree (a, Int), Int)
labelHlp (Leaf x) n = (Leaf (x, n), n + 1)
labelHlp (Node left right) n = let (left', n')   = labelHlp left n
                                   (right', n'') = labelHlp right n'
                               in (Node left' right', n'')

labelTree :: Tree a -> Tree (a, Int)
labelTree t = fst (labelHlp t 0)
-- :}

type Monomial a = (a, Int)

data Polynomial a = Null
                  | Pol (Monomial a) (Polynomial a)

-- :{
format :: (Show a, Ord a, Num a) => Monomial a -> String
format (c, e) | e == 0    = display c
              | otherwise = display c ++ "*x^" ++ show e
              where display k | k >= 0    = show k
                              | otherwise = "(" ++ show k ++ ")"

instance (Show a, Ord a, Num a) => Show (Polynomial a) where
    show Null = ""
    show (Pol m Null) = (format m)
    show (Pol m p) = (format m) ++ " + " ++ show p  
-- :}

-- :{
getDegree :: Polynomial a -> Int
getDegree Null = -1
getDegree (Pol (c, e) p) = max e (getDegree p) 
-- :}
