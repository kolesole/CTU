#lang racket
(provide valid?)

(define (on-board? mrow mcol crow ccol)
    (and (>= crow 0) (< crow mrow)
         (>= ccol 0) (< ccol mcol))
)

(define (check board mrow mcol positions)
    (define (check-pos pos)
        (and (on-board? mrow mcol (car pos) (cdr pos))
             (equal? (list-ref (list-ref board (car pos)) (cdr pos)) 1)))
    
    (not (ormap check-pos positions))
)    

(define (gen-positions crow ccol)
    (define deltas '((-1 .  2) (-1 . -2) (1 .  2) (1 . -2)
                     (2 .  1) (2 . -1) (-2 . 1) (-2 . -1)))
    (map (lambda (delta) 
                (cons (+ crow (car delta))
                      (+ ccol (cdr delta)))) deltas)
)                

(define (valid? board)
    (define mrow (length board))
    (define mcol (length (car board)))
    (define chck (curry check board mrow mcol))

    (define poss 
        (for*/list ([row (in-range mrow)]
                    [col (in-range mcol)]
                    #:when (equal? (list-ref (list-ref board row) col) 1))
                (gen-positions row col)))
    (andmap chck poss)
)