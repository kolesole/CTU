#lang racket
(provide spiral-matrix)

(define (add-mat m n)
    (map (curry map (curry + n)) m)
)

(define (wrap x lst z)
    (cons x (append lst (list z)))
)

(define (spiral-matrix n)
    (if (equal? n 1) 
        '((1)) 
        (let*([smaller (add-mat (spiral-matrix (- n 2)) (- (* 4 n) 4))]
              [first-line (range 1 (+ n 1))]
              [last-line  (range (- (* 3 n) 2) (- (* 2 n) 2) -1)]
              [left-line  (range (- (* 4 n) 4) (- (* 3 n) 2) -1)]
              [right-line (range (+ n 1) (- (* 2 n) 1))]
              [ext-smaller (map wrap left-line smaller right-line)])
            (append (list first-line) ext-smaller (list last-line))
        ))
)

(define mat '((1 2 3) (8 9 4) (7 6 5)))