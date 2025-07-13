#lang racket

;--------------------------------------------------------------------

(define (mult-all-pairs lst1 lst2)
    (apply append (map (lambda(x) (map ((curry *) x) lst2)) lst1))
)

(define (f-all-pairs f lst1 lst2)
    (apply append (map (lambda(x) (map ((curry f) x) lst2)) lst1))
)

;--------------------------------------------------------------------

(define (get-coef m) (car m)) ; first component

(define (get-exp m) (cadr m)) ; second component

(define (add-mon m1 m2)
    (list (+ (get-coef m1) (get-coef m2)) (get-exp m1))
)

(define (mult-mon m1 m2)
    (list (* (get-coef m1) (get-coef m2)) (+ (get-exp m1) (get-exp m2)))
)

(define (add-mon-pol mon pol)
    (define (same-exp? m) (= (get-exp mon) (get-exp m)))
    (define same-mon (filter same-exp? pol))
    (define rest (filter (compose not same-exp?) pol))

    (if (null? same-mon)
        (cons mon rest)
        (cons (add-mon mon (car same-mon)) rest)
    )
)

(define (normalize p)
    (define (non-zero-coef? m) (not (= 0 (get-coef m))))
    (sort (filter non-zero-coef? p) (lambda (m1 m2) (< (get-exp m1) (get-exp m2))))    
)

(define (add-pol p1 p2)
    (normalize (foldl add-mon-pol p1 p2))
)

(define (mult-pol p1 p2)
    (normalize foldl add-mon-pol '() (f-all-pairs mult-mon p1 p2))
)

;---------------------------------------------------------------------------------------

(define (mult-coef-vect v c)
    (map ((curry *) c) v)
)

(define (linear-combination m v) 
    (apply map + (map mult-coef-vect v m))
)

;---------------------------------------------------------------------------------------

(define (matrix-mult m1 m2)
    (map ((curry linear-combination m2) m1)
)

