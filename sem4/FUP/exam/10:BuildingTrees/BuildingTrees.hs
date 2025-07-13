module BuildingTrees (addEdge, buildTree, Tree(..)) where
import Data.List

data Tree a = Leaf { val :: a }
            | Node { val :: a,
                     kids :: [Tree a] } deriving (Eq,Show)

type Edge a = (a,a)

addEdge :: (Eq a, Ord a) => Tree a -> Edge a -> Tree a
addEdge (Leaf v) (s, t) = if v == s then Node v [Leaf t] else Leaf v
addEdge (Node v kids) (s, t) = if v == s then Node v (sortOn val ((Leaf t):kids))
                               else Node v [addEdge n (s, t) | n <- kids]

buildTree :: (Eq a, Ord a) => Tree a -> [Edge a] -> Tree a
buildTree init edges = foldl addEdge init edges