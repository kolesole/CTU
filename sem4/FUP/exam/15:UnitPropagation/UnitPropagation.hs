module UnitPropagation ( propagateUnits, Literal (..) ) where
import Data.List -- for delete, nub functions

type Variable = String
data Literal = Neg { variable :: Variable }
             | Pos { variable :: Variable } deriving (Eq, Ord)

type Clause = [Literal]

instance Show Literal where
  show (Neg x) = "-" ++ x
  show (Pos x) = x

inv :: Literal -> Literal
inv (Pos v) = Neg v 
inv (Neg v) = Pos v 

getUnit :: [Clause] -> Maybe Literal 
getUnit cls = let units = concat $ filter ((==1) . length) cls
                in case units of 
                    []     -> Nothing
                    (u:us) -> Just u 

filt :: Literal -> Clause -> Clause
filt u cl = let iu = inv u 
             in filter (/=iu) cl 

propagateUnits :: [Clause] -> [Clause]
propagateUnits cls = let u = getUnit cls
                      in case u of 
                            Nothing -> nub cls 
                            Just v  -> let filtred1 = map (filt v) cls 
                                           filtred2 = filter (notElem v) filtred1
                                        in propagateUnits filtred2
