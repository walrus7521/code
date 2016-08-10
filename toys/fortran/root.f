program iterative_square_root

    real :: value, guess, next_guess
    real, parameter :: eps = 1.0e-5

    do      ! infinite loop until zero entered

        print *, "Enter a number, zero to stop:"
        read *, value

        if (value <= 0.0) then
          stop
        end if

        guess = value/2.0

        do
            next_guess = guess - (guess**2 - value)/(2*guess)
            print "(f14.8)", next_guess
            if (abs(guess - next_guess) > eps) then
                guess = next_guess
            else
                exit
            end if
        end do

        print *, "The square root of ", value, &
               " is approximately ", next_guess

    end do
end program iterative_square_root 
