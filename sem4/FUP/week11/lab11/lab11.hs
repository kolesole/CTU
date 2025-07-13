toUpper :: Char -> Char
toUpper c = case lookup c chars of
    Just upper -> upper
    Nothing -> c
    where 
        chars = zip ['a' .. 'z'] ['A' .. 'Z']

toCamelCase :: String -> String
toCamelCase str = concat $ map uppFirst (words str)    -- or concatMap uppFirst (words str)
    where 
        uppFirst (c:rest) = toUpper c : rest
        uppFirst "" = ""

toCamelCaseF :: Functor f => f String -> f String
toCamelCaseF = fmap toCamelCase 

-------------------------------------------

data Expr a = Atom a
            | Neg (Expr a)
            | And (Expr a) (Expr a)
            | Or (Expr a) (Expr a)
                deriving (Eq, Show)

expr :: Expr Bool
expr = Or (And (Atom True) (Neg (Atom False))) (Atom False)

fle :: Expr String
fle = And (Or (Neg (Atom "x")) (Atom "x")) (Atom "y")

getAtoms :: Expr a -> [a]
getAtoms (Atom a) = [a]
getAtoms (Neg a) = getAtoms a
getAtoms (And a1 a2) = (getAtoms a1) ++ (getAtoms a2)
getAtoms (Or a1 a2) = (getAtoms a1) ++ (getAtoms a2)

eval :: Expr Bool -> Bool
eval (Atom a) = a
eval (Neg a) = case eval a of
                True  -> False
                False -> True
eval (And a1 a2) = case (eval a1, eval a2) of
                (True, True) -> True
                (_, _)       -> False
eval (Or a1 a2) = case (eval a1, eval a2) of
                (False, False) -> False 
                (_, _)         -> True 

--------------------------------------------------------------------

data DFA a = Automaton (a->Char->a) a (a->Bool)

evalDFA :: DFA a -> String -> Bool
evalDFA (Automaton _ state fin) "" = fin state 
evalDFA (Automaton trans state fin) (c:rest) = 
    evalDFA (Automaton trans (trans state c) fin) rest

data State = Before | Digit | Dot | First | Second | Fail

isNum :: Char -> Bool
isNum c = c `elem` ['0'..'9']

final :: State -> Bool
final Second = True
final _ = False

delta :: State -> Char -> State
delta Before c | isNum c = Digit
               | otherwise = Fail
delta Digit c | isNum c = Digit
              | c == '.' = Dot
              | otherwise = Fail
delta Dot c | isNum c = First
            | otherwise = Fail
delta First c | isNum c = Second
              | otherwise = Fail
delta Second _ = Fail
delta Fail _ = Fail

automaton :: DFA State
automaton = Automaton delta Before final

parseNum :: String -> Maybe Float
parseNum w = if evalDFA automaton w then Just (read w)
             else Nothing

parseNumF :: Functor f => f String -> f (Maybe Float)
parseNumF = fmap parseNum


--------------------------------------------------------------------

instance Functor Expr where
    fmap f (Atom c) = Atom (f c)
    fmap f (Neg e) = Neg (fmap f e)
    fmap f (And e1 e2) = And (fmap f e1) (fmap f e2)
    fmap f (Or e1 e2) = Or (fmap f e1) (fmap f e2)

subst :: Functor f => [String] -> f String -> f Bool
subst vars = fmap (`elem` vars)

subseqs :: [a] -> [[a]]
subseqs [] = [[]]
subseqs (x:xs) = subseqs xs ++ [x:ys | ys <- subseqs xs]

isTaut :: Expr String -> Bool
isTaut a = let subseq = subst (subseqs (getAtoms a))

            in 

