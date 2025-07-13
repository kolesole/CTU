#lang racket
(require racket/match)

(define img-zero
  '(".##."
    "#..#"
    "#..#"
    ".##."))

(define img-one
  '("...#"
    "..##"
    "...#"
    "...#"))

(define/match (digit->img d)
    ([0] img-zero)
    ([1] img-one)
)

(define (number->digits n radix)
    (define (help num acc)
        (if (< num radix) 
            (reverse (cons num acc))
            (let* ([q (quotient num radix)]
                   [r (remainder num radix)])
                (help q (cons r acc))))
    )
    (help n '())
)

(define (concat-imgs imgs)
    (define (help img1 img2)
        (map (lambda (i1 i2) (string-append i1 "." i2)) img1 img2)
    )
    (foldl help (first imgs) (rest imgs))
)

(define (main)
    (displayln "Enter integer:")
    (define n (read))
    (define digits (number->digits n 2))
    (define imgs (map digit->img digits))
    (displayln (string-join (concat-imgs imgs) "\n"))
)

(main)