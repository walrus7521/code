#!/usr/bin/env python3

import numpy as np 
import matplotlib.pyplot as plt 
import pandas as pd
import sklearn
import sklearn.linear_model

  
def estimate_coef(x, y): 
    # number of observations/points 
    n = np.size(x) 
  
    # mean of x and y vector 
    m_x, m_y = np.mean(x), np.mean(y) 
  
    # calculating cross-deviation and deviation about x 
    SS_xy = np.sum(y*x) - n*m_y*m_x 
    SS_xx = np.sum(x*x) - n*m_x*m_x 
  
    # calculating regression coefficients 
    b_1 = SS_xy / SS_xx 
    b_0 = m_y - b_1*m_x 
  
    return(b_0, b_1) 
  
def plot_regression_line(x, y, b): 
    # plotting the actual points as scatter plot 
    plt.scatter(x, y, color = "m", 
               marker = "o", s = 30) 
  
    # predicted response vector 
    y_pred = b[0] + b[1]*x 
  
    # plotting the regression line 
    plt.plot(x, y_pred, color = "g") 
  
    # putting labels 
    plt.xlabel('x') 
    plt.ylabel('y') 
  
    # function to show plot 
    plt.show() 
  
def main(): 
    # observations 
    x = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) 
    y = np.array([10, 13, 12, 15, 17, 18, 18, 19, 20, 22]) 

    X = x.reshape(-1,1)
    Y = y.reshape(-1,1)
  
    # estimating coefficients 
    b = estimate_coef(x, y) 
    print("Estimated coefficients:\n(offset) b_0 = {} \n (slope) b_1 = {}".format(b[0], b[1])) 
  
    # plotting regression line 
    plot_regression_line(x, y, b) 

    print("x: {0} {1}".format(len(X), X))
    print("y: {0} {1}".format(len(Y), Y))
  
    # select a linear model
    lin_reg_model = sklearn.linear_model.LinearRegression()
    lin_reg_model.fit(X,Y)

    X_new = [[33]] #[[22587]] # Cyprus GDP per capita
    print(lin_reg_model.predict(X_new)) # outputs [[ 5.96242338 ]



if __name__ == "__main__": 
    main()


