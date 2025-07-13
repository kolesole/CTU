module FTree (parse, exists) where
import Data.Map (Map)
import qualified Data.Map as Map

data FTree a = FNil | FNode (Map a (FTree a)) deriving (Eq)

files =  ["src/tree.hs"
         ,"src/complex.hs"
         ,"scripts/ex1/test.ss"
         ,"scripts/ex1/eval.ss"
         ,"scripts/emptydir"
         ,"scripts/ex2/test.ss"
         ,"tests/test_tree.hs"]
