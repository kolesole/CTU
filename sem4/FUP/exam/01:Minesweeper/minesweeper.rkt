#lang racket

(define board (map string->list (string-split "·*·*·\n··*··\n··*··\n·····")))

(define (int->digit i) (integer->char (+ 48 i)))

(define (finalize field mcount)
    (match (cons field mcount)
        [(cons #\* _) #\*]
        [(cons _ 0)   #\.]
        [(cons _ mcount) (int->digit mcount)]
    )
)

(define (neighbours board mrow mcol row col)
    (for*/list ([crow [range (max 0 (- row 1)) (min mrow (+ row 2))]]
                [ccol [range (max 0 (- col 1)) (min mcol (+ col 2))]])
            (list-ref (list-ref board crow) ccol)
    )    
)

(define (num field neis)
    (let* ([f (curry equal? #\*)]
           [n (length (filter f neis))])
        (finalize field n)
    )
)

(define (count board)
    (define max-row (length board))
    (define max-col (length (car board)))
    (define nei (curry neighbours board max-row max-col))
    (map (lambda (row)
         (map (lambda (col) 
                (let* ([field (list-ref (list-ref board row) col)]
                       [neis (nei row col)])
                    (num field neis))
              )
              (range 0 max-col))
          )
        (range 0 max-row))
)

(let* ((input-string (port->lines))
       (list-board (map string->list input-string))
       (counted-board (count list-board))
       (sn (map list->string counted-board)))
  (for ((l sn))
    (display l)
    (newline)))
































; ; for converting ints to chars.
; (define (int->digit i) (integer->char (+ 48 i)))

; (define (finalizer field n)
;     (match (cons field n)
;            [(cons #\* _) #\*]
;            [(cons _ 0)   #\.]
;            [(cons _ n)   (int->digit n)]
;     )
; )

; (define (neighbour board mrow mcol crow ccol)
;     (for*/list ((row (range (max 0 (- crow 1)) (min mrow (+ crow 2))))
;                 (col (range (max 0 (- ccol 1)) (min mcol (+ ccol 2)))))
;         (list-ref (list-ref board row) col)
;     )
; )

; (define (num field neis)
;     (let* ([f (curry equal? #\*)]
;            [fneis (filter f neis)]
;            [n (length fneis)])
;           (finalizer field n)
;     )
; )

; (define (count board)
;     (let* ([mrow (length board)]
;            [mcol (length (car board))]
;            [nei (curry neighbour board mrow mcol)])
;           (map (lambda (row)
;                     (map (lambda (col)
;                             (let* ([field (list-ref (list-ref board row) col)]
;                                    [neis (nei row col)])
;                                   (num field neis)))
;                     (range 0 mcol)))
;                     (range 0 mrow)))
; )

; (let* ((board-string (port->lines))
;        (board-list (map string->list board-string))
;        (counted-board (count board-list)) 
;        (sn (map list->string counted-board)))
;   (for ((l sn))
;     (display l)
;     (newline)))



