#lang racket

(provide accepts lwords (struct-out transition) (struct-out automaton))

(struct transition (from-state symbol to-state))

(struct automaton (trans init-state final-states))

(define (accepts automaton word))

(define (lwords alphabet automaton n))



(define nfa
  (automaton
   (list (transition 1 #\a 2)
         (transition 2 #\b 2)
         (transition 1 #\a 3)
         (transition 3 #\b 4)
         (transition 4 #\a 3)
         (transition 2 #\a 4))
   1
   (list 2 3)))