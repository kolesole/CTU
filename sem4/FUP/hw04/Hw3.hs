module Hw3 where

type Symbol = String
data Expr = Var Symbol
          | App Expr Expr
          | Lambda Symbol Expr deriving Eq

instance Show Expr where
    show (Var x) = x
    show (App e1 e2) = "(" ++ show e1 ++ " " ++ show e2 ++ ")"
    show (Lambda x e) = "(\\" ++ x ++ "." ++ show e ++ ")"   


isFree :: Symbol -> Expr -> Bool
isFree v1 (Var v2) = v1 == v2
isFree v (App e1 e2) = isFree v e1 || isFree v e2
isFree v1 (Lambda v2 term) | v1 == v2  = False
                           | otherwise = isFree v1 term

genFreshVar :: Int -> Symbol
genFreshVar index = "a" ++ show index 

reduce :: Int -> Expr -> Symbol -> Expr -> (Expr, Int)
reduce index (Var v1) v2 term | v1 == v2  = (term, index)
                              | otherwise = (Var v1, index)
reduce index (App e1 e2) v term = let (e1', index')  = (reduce index e1 v term)
                                      (e2', index'') = (reduce index' e2 v term)
                                  in  (App e1' e2', index'')
reduce index (Lambda v1 term1) v2 term2 | v1 == v2              = (Lambda v1 term1, index)
                                        | not (isFree v1 term2) = let (term1', index') = (reduce index term1 v2 term2)
                                                                  in  (Lambda v1 term1', index')
                                        | otherwise             = let fresh =  genFreshVar index 
                                                                      (term1', index') = reduce (index + 1) term1 v1 (Var fresh)
                                                                      (term1'', index'') = (reduce index' term1' v2 term2)
                                                                  in  (Lambda fresh term1'', index'')       

isLambda :: Expr -> Bool
isLambda (Lambda _ _) = True
isLambda _            = False

evalHelp :: Int -> Expr -> Expr
evalHelp _ (Var v) = Var v
evalHelp depth (Lambda v e) | depth < 100 = (Lambda v (evalHelp (depth + 1) e))
                            | otherwise   = (Lambda v e)
evalHelp depth (App e1 e2)  | depth < 100 = let e1' = evalHelp (depth + 1) e1
                                                e2' = evalHelp (depth + 1) e2 
                                            in 
                                                if isLambda e1' then 
                                                   let Lambda v term = e1'
                                                       (new, _)      = (reduce 0 term v e2) 
                                                   in evalHelp (depth + 1) new
                                                else 
                                                    App e1' e2'
                            | otherwise  = (App e1 e2)                        
 
eval :: Expr -> Expr
eval exp = evalHelp 0 exp
