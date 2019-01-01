package main;

import (
    "bufio"
    "fmt"
    "os"
    "regexp"
)

func main() {

    regex := *regexp.MustCompile(`(?s)(\d{4})-(\d{2})-(\d{2})`)

    input := bufio.NewScanner(os.Stdin)
    for input.Scan() {
        line := input.Text()
        res := regex.FindAllStringSubmatch(line, -1)

        for i := range res {
            fmt.Printf("year: %s, month: %s, day: %s\n",
                    res[i][1], res[i][2], res[i][3])
        }

    }

}
