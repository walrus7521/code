echo "Running unit tests:"

for i in tests/*_tests
do
	echo "do this one"
    if test -f $i
    then
		echo "here do: $i"
        if $VALGRIND ./$i 2>> tests/tests.log
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            exit 1
        fi
    fi
done

echo ""
