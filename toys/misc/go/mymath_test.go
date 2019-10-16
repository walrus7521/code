package mymath_test

import (
    "testing"
    "pkg/mymath"
)

func TestAverage(t *testing.T) {
    v := mymath.Average([]float64{1,2})
    if v != 1.5 {
        t.Error("Expected 1.5, got ", v)
    }
}

