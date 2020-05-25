#!/usr/bin/env python3

from bs4 import BeautifulSoup

from urllib.request import urlopen

import requests

#html = urlopen('http://forecast.weather.gov/MapClick.php?lat=37.7772&lon=-122.4168')
#bs = BeautifulSoup(html.read(), 'html.parser')
#print(bs.h1)

page = requests.get('http://forecast.weather.gov/MapClick.php?lat=37.7772&lon=-122.4168')
soup = BeautifulSoup(page.content, 'html.parser')
seven_day = soup.find(id="seven-day-forecast")
forecasts = seven_day.find_all(class_="tombstone-container")
tonight = forecasts[0]
for forecast in forecasts:
    print(forecast.prettify())
