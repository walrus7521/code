! http://www.fortrantutorial.com/
!
program f_prog
    integer :: i,j(2)
    real :: r
    character(len=10) :: str

    integer   :: pounds,pence,total
    character :: name*10

    name = "bart"
    print *, "Hello: ", name, "Please enter pounds and pence"
    read *, pounds,pence
    total = pounds + pence
    if (total < 2) then
        print *, 'less than 2', total
    else if (total < 7) then
        print *, 'less than 7', total
    else
        print *, 'greater than 7', total
    end if
    i = 4711
    j = (/13, 14/)
    r = 4712.0
    str = "hello"
    print *, str, r, i, j
    print *, "Name:   ", " Lbs:   ", " Pence:   ", "Tot:  "
    print *, name, pounds, pence, total
end program f_prog

