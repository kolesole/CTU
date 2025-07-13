#lang racket

(provide best-view)

(define (visible-roofs city)
    (define (row-vis-rfs row [h -1] [acc 0])
        (if (empty? row) acc
                (let ([nh (car row)]
                      [nrow (cdr row)])
                    (if (> nh h) (row-vis-rfs nrow nh (add1 acc))
                        (row-vis-rfs nrow h acc) 
                    ))
        )
    )
    (apply + (map row-vis-rfs city))            
)

(define (wcity city)
    city
)

(define (ecity city)
    (map reverse city)
)

(define (ncity city)
    (apply map list city)
)

(define (scity city)
    (ecity (ncity city))
)

(define (best-view city)
    (define (more? n1 n2) (> (cdr n1) (cdr n2)))
    (let* ([wnum (cons 'W (visible-roofs (wcity city)))]
           [enum (cons 'E (visible-roofs (ecity city)))]
           [nnum (cons 'N (visible-roofs (ncity city)))]
           [snum (cons 'S (visible-roofs (scity city)))])
        (car (sort (list wnum enum nnum snum) more?)))
)

(define city
  '((3 3 3)
    (1 2 3)
    (1 2 3)))