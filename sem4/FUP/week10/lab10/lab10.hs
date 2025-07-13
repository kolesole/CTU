-- :{
interleave :: a -> [a] -> [[a]]
interleave x [] = [[x]]
interleave x (y : ys) = (x:y:ys) : [y:xs | xs <- interleave x ys]

permutations :: [a] -> [[a]]
permutations [] = [[]]
permutations (x:xs) = concat [interleave x p | p <- permutations xs]
-- :}

-- :{
type Edge a = (a,a)
data Graph a = Graph {vertices :: [a], edges :: [Edge a]} deriving Show

gr :: Graph Int
gr = Graph {vertices=[1..6], edges=[(1, 2), (1, 5), (2, 3), (2, 5), (3, 4), (4, 5), (4, 6)]}

isEdge :: Eq a => Edge a -> Graph a -> Bool
isEdge (a, b) g = (a, b) `elem` edgs || (b, a) `elem` edgs where edgs = edges g 

{-isPath :: Eq a => [a] -> Graph a -> Bool
isPath vs g = and [ isEdge pair g | pair <- zip vs (tail vs) ]

findHamiltonian :: Eq a => Graph a -> [[a]]
findHamiltonian g = [p | p <- perms, isPath p g] where perms = permutations (vertices g)
-}

-- :}

merge :: Ord b => (a -> b) -> [a] -> [a] -> [a]
merge _ [] [] = []
merge _ [] b = b
merge _ a [] = a
merge f a@(a1:as) b@(b1:bs) = if (f a1) <= (f b1) then
                            [a1] ++ (merge f as b)
                        else
                            [b1] ++ (merge f a bs)

subseqs :: [a] -> [[a]]
subseqs [] = [[]]
subseqs a@(x:xs) = merge length (subseqs xs) [x:ys | ys <- subseqs xs] 
