#!/usr/bin/env python2.7

# https://plot.ly/python/gantt/
# C:\code\toys\misc\tasks\gantt.py

import plotly.figure_factory as ff
import pandas as pd


df = pd.read_csv('tasks2.csv')

colors = ['#7a0504', (0.2, 0.7, 0.3), 'rgb(210, 60, 180)']
fig = ff.create_gantt(df, colors=colors, index_col='Resource',
                      show_colorbar=True, bar_width=0.2, showgrid_x=True, showgrid_y=True)
fig.show()


