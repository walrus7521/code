#!/usr/bin/env python3

# Python program using Pandas for  
# arranging a given set of data  
# into a  table 
  
# importing pandas as pd 
import pandas as pd 
  
data = { "country"   : ["Brazil",   "Russia", "India",     "China",   "South Africa" ],
         "capital"   : ["Brasilia", "Moscow", "New Dehli", "Beijing", "Pretoria"     ],
         "area"      : [8.516,      17.10,    3.286,       9.597,     1.221          ],
         "population": [200.4,      143.5,    1252,        1357,      52.98          ],
         "douchiness": [10.4,       7.5,      3,           4,         8.6            ]
       } 
  
data_table = pd.DataFrame(data) 
print(data_table) 