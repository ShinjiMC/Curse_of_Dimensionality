package main

import (
	"fmt"
	"log"
	"math"
	"os"
	"regexp"
	"strconv"
	"strings"

	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/vg"
)

func SplitLogLine(text string) (int, []float64) {
	re := regexp.MustCompile(`\s+`)
	parts := re.Split(text, -1)
	var numbers []float64
	var dims int
	for i, part := range parts {
		part = strings.TrimSpace(part)
		if part != "" {
			number, err := strconv.ParseFloat(part, 64)
			if err != nil {
				fmt.Printf("Error al analizar número '%s': %v\n", part, err)
			} else {
				if i == 0 {
					dims = int(number)
				} else {
					numbers = append(numbers, number)
				}
			}
		}
	}
	return dims, numbers
}

func getMaxValueX(distances []float64) int {
	maxValue := math.Inf(-1)
	for _, value := range distances {
		if value > maxValue {
			maxValue = value
		}
	}
	return int(math.Ceil(maxValue))
}

func getMinValueX(distances []float64) int {
	minValue := math.Inf(1)
	for _, value := range distances {
		if value < minValue {
			minValue = value
		}
	}
	return int(math.Floor(minValue))
}

func Ploteo(distances []float64, dim int) {

	p := plot.New()

	hist := plotter.Values(distances)
	bins := 10

	histogram, err := plotter.NewHist(hist, bins)
	if err != nil {
		log.Fatal(err)
	}
	p.Add(histogram)

	maxX := float64(getMaxValueX(distances))
	minX := float64(getMinValueX(distances))
	p.X.Min = minX
	p.X.Max = maxX
	p.Y.Max = 1600
	p.X.Label.Text = "Distancias"
	p.Y.Label.Text = "Frecuencia"
	p.Title.Text = fmt.Sprintf("Histograma de las distancias entre puntos con dimension %d", dim)
	p.Y.Tick.Marker = plot.ConstantTicks([]plot.Tick{
		{Value: 0.0, Label: "0"},
		{Value: 200.0, Label: "200"},
		{Value: 400.0, Label: "400"},
		{Value: 600.0, Label: "600"},
		{Value: 800.0, Label: "800"},
		{Value: 1000.0, Label: "1000"},
		{Value: 1200.0, Label: "1200"},
		{Value: 1400.0, Label: "1400"},
		{Value: 1600.0, Label: "1600"},
	})
	numDivisions := 8
	xDivisions := make([]plot.Tick, numDivisions)
	for i := 0; i < numDivisions; i++ {
		value := minX + (float64(i) * (maxX - minX) / float64(numDivisions-1))
		label := fmt.Sprintf("%.1f", value)
		xDivisions[i] = plot.Tick{Value: value, Label: label}
	}
	p.X.Tick.Marker = plot.ConstantTicks(xDivisions)
	if err := p.Save(6.0*vg.Inch, 6.0*vg.Inch, "histogram.png"); err != nil {
		log.Fatal(err)
	}
	fmt.Println("Histograma guardado en 'histogram.png'")
}

func main() {
	data, err := os.ReadFile("Histogram/distances")
	if err != nil {
		fmt.Println("Error reading pipe:", err)
		return
	}
	//fmt.Println("Received:", string(data))
	dim, distances := SplitLogLine(string(data))
	Ploteo(distances, dim)
}
