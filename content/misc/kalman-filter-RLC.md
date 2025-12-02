---
title: "Kalman Filter RLC"
date: 2020-06-01T12:04:32+02:00
tags: []
draft: false
---

<!-- The Kalman filter combines measurements and a theoretical model to best estimate the state of a system. The example below is a simple RLC circuit, which is a second order system. If we imagine an ADC is measuring the  potential difference over the circuit, which will be noisy and for the Kalman filter to work this must be gaussian 
 -->


<style>
  code.has-jax {
    -webkit-font-smoothing: antialiased;
    background: inherit !important;
    border: none !important;
    font-size: 100%;
}  

</style>


<p align="center"> 
<img src="/misc/images/RLC_circuit.svg" alt="RLC" width = 500px>
</p>

The RLC circuit above can be expressed by the following equation 
<div>
$$ \ddot{I}_{L} = -\frac{\dot{I}_{L}}{RC}  -\frac{I_L}{LC} + \frac{I}{LC} $$

The equation can be expressed as two first order differential equations using the following method.

$$ x_{1} = I_{L} $$

$$ x_{2} = \dot{I}_{L}$$
</div>
so 

<div>
$$ 
\dot{x}_{2} = \ddot{I}_{L} = -\frac{\dot{I}_{L}}{RC} -\frac{I_{L}}{LC} + \frac{I}{LC}
$$
</div>

and
<div>
$$\dot{x}_{1} =\dot{I}_{L} =  x_{2}$$
</div>

Replacing variables with state variables $\bf{X}$
<div>
$$ \dot{x}_{2} = - \frac{x_{2}}{RC} - \frac{x_{1}}{LC} + \frac{I}{LC} $$
</div>
Using the formula below the derivative can be discretised.  
$$  \dot{x} = \frac{x_{k+1}  - x_k   }{\Delta t} $$



$$ \frac{x_{1_{k+1}} - x_{1_{k}}}   {\Delta t} = x_{2_{k}}$$

rearranging gives the future value for $x_{1}$

$$ x_{1_{k+1}}  = \Delta t x_{2_{k}} + x_{1_{k}} $$ 

The same method is then applied to $x_{2}$

$$
\frac{x_{2_{k+1}}- x_{2_k}}{\Delta t}  = -\frac{x_{1_k}} {LC}  -\frac{x_{2_{k}}}{RC} + \frac{I_k}{LC}
$$

Giving the future value for $x_{2}$


$$
x_{2_{k+1}} = -\frac{\Delta t x_{1_k}} {LC} -  x_{2_{k}}\left (1- \frac{\Delta t}{RC} \right) + \frac{\Delta t I_k}{LC}
$$

<!-- 
The two equations can then be displayed in state space formalism. I have shifted the time step of the system by -1. The predicted value $x_{1_{k+1}} $ is now predicting the current state of the system as $x_{1_{k}}$ From here on, a hat above a variable indicates a predicted state and a tilde is a measured variable. -->

The two equations can now be expressed in state space formalism. I have shifted the time step by -1 so $x_{1_{k+1}} $ is now $x_{1_{k}}$. This is done to maintain accordance with the kalman filter framework as shown below by the state transition model. 
<div>
$$
\hat{X}_k = F_k X_{k-1} + B_{k} U_{k}
$$
</div>


where


* $\hat{\bf{X}}$ - estimated state
* $\bf{X_{k-1}}$ - previous time steps estimated true state (combination of estimate and measurement)  
* $\bf{F}$ - state transition model 
* $\bf{B}$ - control input model
* $\bf{U}$ - control input

From here on, a hat above a variable indicates a predicted state and a tilde is a measured variable.

<div>
\begin{align}
\newcommand{\xoverbrace}[2][\vphantom{\dfrac{A}{A}}]{\overbrace{#1#2}}
\newcommand{\pder}[2]{\frac{\partial#1}{\partial#2}}
\overbrace{
\begin{bmatrix}
\hat{x}_{1_{k}}\\ 
\hat{x}_{2_{k}}
\end{bmatrix}
}^\mathbf{\hat{X}_k}
=
\overbrace{
\begin{bmatrix}
1 & \Delta t \\ 
 -\frac{\Delta t}{LC} &  1 - \frac{\Delta t}{RC}
\end{bmatrix} 
}^\mathbf{F_k}
\:
\overbrace{
\begin{bmatrix}
x_{1_{k-1}}\\  
x_{2_{k-1}}
\end{bmatrix}
}^\mathbf{\hat{{X}}_{k-1}}
+ 
\overbrace{
\begin{bmatrix}
0\\ 
\frac{\Delta t}{LC}
\end{bmatrix}
}^{\mathbf{B_{k}}}
\:
\xoverbrace{
I_{k-1}
}^\mathbf{U_{k}}
\end{align}
</div>

The voltage induced across an inductor is equal to the rate of change of current passing through it multiplied by its inductance. 

<div>
$$
\tilde{v}(t) = L\dot{I}_{L}
$$
</div>

<!-- The correction matrix is then equal to the prediction minus the measurement multiplied by the Kalman gain of the system.  -->
The correction matrix takes the predicted value and adjusts it based on a measurement. How much the measurement is incorporated into the prediction is dependent on the Kalman gain. 

<div>
$$
\begin{bmatrix}
x_{1_{k}}\\ 
x_{2_{k}}
\end{bmatrix}
= 
\overbrace{
\begin{bmatrix}
\hat{x}_{1_{k}}\\ 
\hat{x}_{2_{k}}
\end{bmatrix}
}^\mathbf{\hat{X}} +
K \left(
\tilde{v}_k -
\overbrace{
\begin{bmatrix}
0 & L
\end{bmatrix} 
}^\textbf{H}
\begin{bmatrix}
\hat{x}_{1_{k}}\\ 
\hat{x}_{2_{k}}
\end{bmatrix}
\right )
$$
</div>


This is all that is needed in terms of design. The rest of the algorithm follows the formula below taken from Wikipedia.

<p align="center"> 
<img src="/misc/images/Kalman_Design_wiki.png" alt="RLC" width = 550px>
</p>

### Results 

<p align="center"> 
<img src="/misc/images/Inductor_current.png" alt="RLC" width = 800px>
</p>
<p align="center"> 
<img src="/misc/images/Inductor_current_deriv.png" alt="RLC" width = 800px>
</p>
<p align="center"> 
<img src="/misc/images/Inductor_voltage.png" alt="RLC" width = 800px>
</p>





## Python Implementation 

The implementation is made in a jupyter notebook which can be downloaded here.
For ease of viewing I have pasted the code segments here - 
<!-- <a href="/docs/kalman_RLC.ipynb" download class="download-link">Kalman RLC Notebook
  <i data-feather="download" style="margin-left:6px;"></i>
</a>
 -->
<a href="/docs/kalman_RLC.ipynb" download="Kalman_RLC.ipynb" class="download-link">
  Kalman RLC Notebook
  <i data-feather="download" style="margin-left:6px;"></i>
</a>


#### Requirements 

```python 
%matplotlib qt
import numpy as np
import matplotlib.pyplot as plt
from numpy.linalg import inv
import copy
```

####  Transition Model 
<div>
$$
\hat{X}_k = F_k X_{k-1} + B_{k} U_{k}
$$

</div>

```python 
def prediction(Il,Ildot,I,t):
    
    L = 5
    C = 500e-9
    R = 50e3
    
    A = np.array([[1, t],
                  [-t/(L*C), 1 - (t/(R*C))]])
    
    X = np.array([[Il],
                 [Ildot]])
    
    B = np.array([[0],
                  [t/(L*C)]])
    
    U = I
    
    X_prediction = A.dot(X) + B.dot(U)

    
    return X_prediction

```

```python 
#time 
T = 0.14
t = np.linspace(0,T,100e3*T)

#initialise inductor current and its derivertive
Il_true = np.zeros(len(t))
Ildot_true = np.zeros(len(t))

#cicuit component definitions
L = 5
C = 500e-9
R = 50e3
#create input signal 
wr = 1/np.sqrt(L*C)

I_true = 25e-6 * np.sin(wr * t)

#time step
dt = t[1] - t[0]

#create True data 
I = np.zeros((2,len(t)))

for i in range(1,len(t)):
    a =  prediction(I[0][i-1],I[1][i-1],I_true[i-1],dt).T
    I[:,i] = a

Il_true = I[0]
Ildot_true = I[1]
    
V_true = L*Ildot_true
noise = np.random.normal(loc=0, scale=0.5, size=len(t))
V_meas = V_true + noise
```

```python 
#state transition model 
A = np.array([[1, dt],
              [-dt/(L*C), (1 - (dt/(R*C)))]],dtype='float')

#process noise(model noise)
Q = np.array([[4e-9, 0],
              [0, 4e-9]])

#measurement noise
R = np.array([[4]])

#Initial Predicted (a priori) estimate
P=Q
#store values for plotting
Il_a = np.zeros([len(t)])
Ildot_a = np.zeros([len(t)])

#initial values
Il_a[0]    = 0
Ildot_a[0] = 0

#set the input matrix to be the true input
I_a = I_true

# for i in range(1,len(t)):
for i in range(len(t)):
    #prediction
    X_hat = prediction(Il_a[i-1], Ildot_a[i-1], I_a[i-1],dt)

    #predicted estimate covariance
    P_hat = np.diag(np.diag(A.dot(P).dot(A.T))) + Q

    #observation matrix v(t) = Ldi/dt
    H = np.array([[0,L]])
    
    #innovation covariance
    S = H.dot(P_hat).dot(H.T) + R
    
    # Kalman Gain
    K = P_hat.dot(H.T).dot(inv(S))

    #measurement - prediction 
    y = V_meas[i] - H.dot(X_hat)   

    #updated state estimate
    X = X_hat + K.dot(y)
    
    #Updated (a posteriori) estimate covariance
    P = (np.identity(2) - K.dot(H)).dot(P_hat)
    
    #update values
    Il_a[i]    = X[0]
    Ildot_a[i] = X[1]
```


