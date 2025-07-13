module RPS (rps) where
import Data.List

isFinished xs = null xs || any null xs

currentStrategies = map head

futureStrategies = map tail

eliminated :: [Char] -> [Bool]
eliminated throws = let elim ['p', 'r'] = 'r'
                        elim ['p', 's'] = 'p'
                        elim ['r', 's'] = 's'
                        elim _          = ' '
                        e = elim $ sort $ nub throws
                    in map (/= e) throws 

filt :: [a] -> [Bool] -> [a]
filt names notelim = [n | (n, s) <- zip names notelim, s]


rps :: [String] -> [[Char]] -> [String]
rps players strategies | isFinished strategies = players
rps players strategies =
    let current = currentStrategies strategies
        future = futureStrategies strategies
        mask = eliminated current  
    in rps (filt players mask) (filt future mask) 

players = ["alice", "bob", "charlie"]
strategies = [['r', 'p', 'r'], ['p', 's', 'r'], ['s', 'r', 'p']]