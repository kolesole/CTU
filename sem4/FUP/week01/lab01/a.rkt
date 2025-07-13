#lang racket

(list 1 2 3 4)
(list "a" 1)

(define la (list "a" "b" "c"))
(define lb (list 1 2 3 4))

(cons "ha" empty)
(cons "ab" (list "cd" "ef"))
(list "ab" (list "cd" "ef"))

(length (list "a" "b" "c"))

(list-ref la 0)
(list-ref la 1)

