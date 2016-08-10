program f_prog
    integer :: i,j(2)
    real :: r
    character(len=10) :: str
    i = 4711
    j = (/13, 14/)
    r = 4712.0
    str = "hello"
    print *, str, r, i, j
end program f_prog

