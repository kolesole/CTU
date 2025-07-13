#lang racket

(provide grid)

(define (abs-diff a b) (abs (- a b)))

(define (manh x y) (apply + (map abs-diff x y)))

(define/match (nearest group dists)
    (((list (cons ch _)) 0) ch)
    (((list (cons ch _)) _) (char-downcase ch))
    ((_ _) #\.)
)

(define (get-symb points cur)
    (define (keyfunc pnt) (manh cur (cdr pnt)))
    (define groups (group-by keyfunc (sort points < #:key keyfunc)))
    (nearest (car groups) (keyfunc (caar groups)))
)

(define (help-grid points)
    (define rows (apply max (map caddr points)))
    (define cols (apply max (map cadr points)))
    (for/list ([crow (add1 rows)])
        (for/list ([ccol (add1 cols)])
            (get-symb points (list ccol crow))))
)

(define (grid points)
    (map list->string (help-grid points))
)

(define points
 '((#\A 1 1)
   (#\B 1 6)
   (#\C 8 3)
   (#\D 3 4)
   (#\E 5 5)
   (#\F 8 9)))
