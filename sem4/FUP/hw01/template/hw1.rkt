#lang racket

;;; Library for converting 2htdp/images into ascii-art strings
;;; Provides img->mat, ascii-art

(require 2htdp/image)
(provide/contract
 ; Ignore the contracts. They are here to catch errors.
 ; We will not discuss them further.
 [img->mat (image? . -> . (listof (listof number?)))]
 [ascii-art (fixnum? fixnum? string? . -> . (image? . -> . string?))])

(module+ test-support
  ; Use a submodule to export internal functions for unit testing.
  (provide color->gray index-formula))

; -----------------------------------------------------------------------------
;;; Converts an 8-bit RGB color into grayscale in [0,255].
(define (color->gray color)
  (+ (* 0.30 (color-red color))
     (* 0.59 (color-green color))
     (* 0.11 (color-blue color))))

;;; Takes a gray value in [0, 255] and maps it to an index in 0:len-1.
(define (index-formula len gray)
  (exact-floor (/ (* len (- 255 (floor gray))) 256)))

; -----------------------------------------------------------------------------
;                   START YOUR IMPLEMENTATION BELOW
; -----------------------------------------------------------------------------

;;; Converts a list of colors into a list of grayscale values
(define (color-list->grey-list lst [res '()])
  (if (null? lst)
    (reverse res)
    (color-list->grey-list (cdr lst) (cons (color->gray (car lst)) res))
  )
)

;;; Converts a list of colors into a list of grayscale values and appends it as a row in a matrix
(define (append-mat-with-color-list mat color-list)
  (append mat (list (color-list->grey-list color-list)))
)

;;; Converts an image into a matrix of grayscale values
(define (img->mat image)
  (define width (image-width image))
  (define (helper color-list cur-width mat cur-color-list)
    (cond 
      [(null? color-list) (append-mat-with-color-list mat (reverse cur-color-list))]
      [(zero? cur-width) (helper color-list width (append-mat-with-color-list mat (reverse cur-color-list)) '())]
      [else (helper (cdr color-list) (- cur-width 1) mat (cons (car color-list) cur-color-list))]
    )
  )

  (helper (image->color-list image) width '() '())
)

;;; Splits a list into blocks of size block-len and computes the sum of elements in each block
(define (list->sum-list lst block-len)
  (define (helper cur-list cur-list-len cur-block-len [sum-list '()] [cur-sum 0])
    (cond 
      [(< cur-list-len cur-block-len) (reverse sum-list)]
      [(zero? cur-block-len) (helper cur-list cur-list-len block-len (cons cur-sum sum-list) 0)]
      [else (helper (cdr cur-list) (- cur-list-len 1) (- cur-block-len 1) sum-list (+ cur-sum (car cur-list)))]
    )
  )

  (helper lst (length lst) block-len '() 0)
)

;;; Transposes a matrix
(define (mat->transp-mat mat)
  (apply map list mat)
)

;;; Applies function f to each element of the matrix with n as the second argument
(define (mat-op f n mat)
  (map (lambda (row) (map (lambda (i) (f i n)) row)) mat)
)

;;; Applies function f to each element of the matrix with n as the first argument
(define (conv-op f n mat)
  (map (lambda (row) (map (lambda (i) (f n i)) row)) mat)
)

;;; Scales a matrix to a new size and converts values into indxs(for charset)
(define (mat-scal charset-len block-width block-height mat)
  (define (helper cur-mat block-len [scal '()])
    (if (null? cur-mat)
      (reverse scal)
      (helper (cdr cur-mat) block-len (cons (list->sum-list (car cur-mat) block-len) scal))
    )
  )

  (mat->transp-mat 
    (conv-op index-formula charset-len 
      (mat-op / (* block-width block-height) 
                (helper (mat->transp-mat (helper mat block-width)) block-height))))
)

;;; Converts a matrix into a string using a given charset
(define (mat->ascii mat charset)
  (string-join (map list->string (conv-op string-ref charset mat)) "\n")
)

;;; First, takes a specification consisting of block-width, block-height and
;;; a character-set; then returns a new function which can convert any image
;;; into a 2D ascii-art string.
(define (ascii-art block-width block-height charset)
  (define (convert image)
    (mat->ascii (mat-scal (string-length charset) block-width block-height (img->mat image)) charset)
  )  
  
  convert
)
