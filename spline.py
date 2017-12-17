from scipy.interpolate import UnivariateSpline
import numpy
#coeffs are stored in coeffs array with coeffs[i] being coeff of x^i
log_ic =[-2,-1,0,1,2]
curr_gain =[100,140,175,165,100]
z=UnivariateSpline(log_ic,curr_gain,k=3)
#print(z.__call__([0,3,4,6,7,9],nu=0,ext=None))
a=z.derivative()
b=a.derivative()
c=b.derivative()
coeffs=[0,0,0,0]
coeffs[0]=(z.__call__(0,nu=0,ext=None))
coeffs[1]=(a.__call__(0,nu=0,ext=None))
coeffs[2]=(b.__call__(0,nu=0,ext=None)/2)
coeffs[3]=(c.__call__(0,nu=0,ext=None)/6)
print(str(coeffs[3])+"*x^3+ "+str(coeffs[2])+"*x^2+ "+str(coeffs[1])+"*x^1+ "+str(coeffs[0]))
