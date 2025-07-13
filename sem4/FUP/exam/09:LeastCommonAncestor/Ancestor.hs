module Ancestor (findPath, commonAncestor, Tree(..)) where

data Tree a = Leaf a
            | Node a (Tree a) (Tree a) deriving (Eq,Show)

findPath :: Eq a => a -> Tree a -> [a]
findPath x (Leaf v)     = if x == v then [v] else []
findPath x (Node v l r) = if x == v then [v] 
                          else let lpath = findPath x l 
                                   rpath = findPath x r
                                   bpath = lpath ++ rpath
                                in if bpath == [] then []
                                   else [v] ++ bpath  

commonAncestor :: Eq a => a -> a -> Tree a -> Maybe a
commonAncestor x y tree = let px = findPath x tree
                              py = findPath y tree
                              common = [x | (x, y) <- zip px py, x == y]
                           in if common == [] then Nothing
                              else return $ last common 

tree2 = Node 1 (Node 2 (Leaf 3)
                       (Node 4 (Leaf 5)
                               (Leaf 6)))
               (Node 7 (Leaf 8)
                       (Leaf 9))