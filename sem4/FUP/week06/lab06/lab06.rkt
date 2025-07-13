#lang rakcet

(require racket/trace) 

(define SIZE 10)
(define (run-prg prg input)
    (eval-prg prg input (fresh-tape SIZE))
)

(define add-prg
  '(@ > @ [- < + >] < *))

(define mul-prg
  '(@ > @ < [- > [- > + > + < <] > [- < + >] < <] > > > *))

(struct tape (left val right) #:transparent)

(define (fresh-tape size)
  (tape '() 0 (make-list (- size 1) 0)))

(define (change op t)
    (tape (tape-left t)
          (op (tape-val t) 1)
          (tape-right t))    
) 

(define (move dir t)
    (match (cons dir t)
        [(cons 'left (tape '() _ _)) (error "Outside tape!")]
        [(cons 'right (tape '() _ _)) (error "Outside tape!")]
        [(cons 'left (tape left val right)) (tape (cdr left) (car left) (cons val right))]
        [(cons 'right (tape left val right)) (tape (cons val left) (car right) (cdr right))]
    )
)

(define (eval-comma prg input t)
    (cond
        ([null? input] error "Empty input!")
        (else eval-prg prg (cdr input) (tape (tape-left t) (car input) (tape-right t)))
    )
)

(define (eval-prg prg input t)
    (match prg
        ['() (list input t)]
        [(list @ rest ...) (eval-comma rest input t)]
        [(list (? list? cmd) rest ...) (eval-cycle cmd rest input t)]
        [(list cmd rest ...) (eval-cmd cmd prg input t)]
    )
)

(trace eval-prg)

(define (eval-cycle cycle prg input t)
    (if (= (tape-val t) 0) 
        (eval-prg prg input t)
        (begin 
            (let* ([cycle-result (eval-prg cycle input)]
                   [new-input (car cycle-result)]
                   [new-t (cadr cycle-result)])           
                (eval-prg cycle prg new-input new-t))
        )

    )
)

(define (eval-cmd cmd prg input t)
    (let ([new-t
            (match cmd
            ['+ (change + t)]
            ['- (change - t)]
            ['< (move 'left t)]
            ['> (move 'right t)]
            ['* (printf "~a " (tape-val t)) t]
            [_ (error "Unexpected cmd!")])]) 
        (eval-prg prg input new-t))
)