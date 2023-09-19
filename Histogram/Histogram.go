package main

import (
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
	"strings"

	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/vg"
)

func SplitLogLine(text string) []float64 {
	re := regexp.MustCompile(`\s+`)
	parts := re.Split(text, -1)
	var numbers []float64
	for _, part := range parts {
		part = strings.TrimSpace(part)
		if part != "" {
			number, err := strconv.ParseFloat(part, 64)
			if err != nil {
				fmt.Printf("Error al analizar número '%s': %v\n", part, err)
			} else {
				numbers = append(numbers, number)
			}
		}
	}
	return numbers
}

func Ploteo(distances []float64) {

	p := plot.New()

	hist := plotter.Values(distances)
	bins := 10

	histogram, err := plotter.NewHist(hist, bins)
	if err != nil {
		log.Fatal(err)
	}
	p.Add(histogram)
	p.X.Min = 0.0
	p.X.Max = 14
	p.Y.Min = 0
	p.Y.Max = 1400

	if err := p.Save(4.0*vg.Inch, 4.0*vg.Inch, "histogram.png"); err != nil {
		log.Fatal(err)
	}
	fmt.Println("Histograma guardado en 'histogram.png'")
}

func main() {
	data, err := os.ReadFile("distances")
	if err != nil {
		fmt.Println("Error reading pipe:", err)
		return
	}
	//fmt.Println("Received:", string(data))
	distances := SplitLogLine(string(data))
	//fmt.Println(distances)
	Ploteo(distances)
}
