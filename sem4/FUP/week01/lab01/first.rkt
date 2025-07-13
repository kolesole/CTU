#lang racket

(define (my-even? n)
    (cond 
        [(= n 0) #t]
        [(= n 1) #f]
        [(< n 0) (my-even? (- n))]
        [else (my-even? (- n 2))]
    )
)

(define (string-repeat n str)
    (if (<= n 0) 
        ""
        (string-append str (string-repeat (- n 1) str))
    )
)

(define (string-repeat2 n str [acc ""])
    (if (<= n 0)
        acc
        (string-repeat2 (- n 1) str (string-append acc str))
    )
)

(define (integer->string i) 
    (string (integer->char i))
)

(define (char-inclusive-range fst lst)
    (define first-index (char->integer fst))
    (define last-index (char->integer lst))
    (define step (if (< first-index last-index) 1 -1))
    (define (iter k acc)
        (if (= k last-index)
            (string-append acc (integer->string k)) 
            (iter (+ k step) (string-append acc (integer->string k)))
        )       
    )
    (iter first-index "")
)

(define (num-of-digits n [acc 1])
    (if (< n 10)
        acc
        (num-of-digits (quotient n 10) (+ acc 1))
    )     
)

(define hex_nums "0123456789ABCDEF")

(define (num->str n [radix 10])
    (define (init r)
        (if (< r 10)
            (char->integer #\0)
            (- (char->integer #\A) 10)   
        )    
    )
)

(define (num n))