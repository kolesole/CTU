module Hw4 where

import Control.Applicative
import Data.Char
import Parser
import Hw3  -- you need this import to pass tests on BRUTE

var :: [(String, Expr)] -> Parser Expr 
var defs = do x <- some alphaNum
              case lookup x defs of
                Nothing -> return $ Var x 
                Just x' -> return $ x'


expr :: [(String, Expr)] -> Parser Expr
expr defs = var defs 
        <|> do string "(\\"
               x <- some alphaNum
               char '.'
               xs <- expr defs
               char ')'
               return $ Lambda x xs
        <|> do char '('
               e <- expr defs
               sep
               e' <- expr defs
               char ')'
               return $ App e e' 


definition :: [(String, Expr)] -> Parser [(String, Expr)] 
definition defs = do x <- some alphaNum
                     sep
                     string ":="
                     sep
                     e <- expr defs 
                     sep
                     return $ defs ++ [(x, e)] 

definitions :: [(String, Expr)] -> String -> ([(String, Expr)], String)
definitions defs prg = case parse (definition defs) prg of
                    Nothing -> (defs, prg)
                    Just (defs', prg') -> let (defs'', prg'') = (definitions defs' prg')
                                           in (defs'', prg'')

readPrg :: String -> Maybe Expr
readPrg prg = case definitions [] prg of 
                (_, "") -> Nothing 
                (defs, prg') -> case parse (expr defs) prg' of 
                                  Nothing -> Nothing
                                  Just (res, "") -> Just res 
                                  _ -> Nothing    










                


