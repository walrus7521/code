Sub CreateChart()
'PURPOSE: Create a chart (chart dimensions are not required)

Dim rng As Range
Dim cht As Object

'Your data range for the chart
  Set rng = ActiveSheet.Range("$B$9212:$B$10000,$D$9212:$D$10000")

'Create a chart
  Set cht = ActiveSheet.Shapes.AddChart2

'Give chart some data
  cht.Chart.SetSourceData Source:=rng

'Determine the chart type
  cht.Chart.ChartType = xlXYScatterLines

End Sub

