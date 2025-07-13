#lang racket

(define (my-even? n)
    (cond
        [(= n 0) #t]
        [(= n 1) #f]
        [(<= n 0) (my-even? (- n))]
        [else (my-even? (- n 2))]
    )    
)

(my-even? 10)

(define (string-repeat n str)
    (if (<= n 0)
        ""
        (string-append str (string-repeat (- n 1) str))
    )    
)

(string-repeat 10 "abc")

(define (string-repeat2 n str [acc ""])
    (if (<= n 0)
        acc
        (string-repeat2 (- n 1) str (string-append acc str))
    )
)

(string-repeat2 10 "abc")

(define (integer->string i)
    (string (integer->char i))
)

(define (char-inclusive-range fst lst)
    (define indx1 (char->integer fst))
    (define indx2 (char->integer lst))
    (define step (if (< indx1 indx2) 1 -1))
    
    (define (iter k acc)
        (if (= k indx2)
            (string-append acc (integer->string k))
            (iter (+ k step) (string-append acc (integer->string k)))
        )
    )    
    
    (iter indx1 "")
)

(char-inclusive-range 'a' 'z')

(define (num-of-digits n [acc 0])
    (define q (quotient n 10))
    (if (= q 0) 
        acc
        (num-of-digits q (+ acc 1))
    )
)

(num-of-digits 123455644432)

(define (num->str n [radix 10])
    (define rem (remainder n radix))
    
    (define init 
        (if (< rem 10)
            (char->integer #\0)
            (- (char->integer #\A) 10)
        )
    )

    (define ret-str
        (string (integer->char (+ init rem)))
    )

    (if (< n radix)
        ret-str
        (string-append (num->str (quotient n radix) radix) ret-str)
    )
)

(num->str 255 16)

