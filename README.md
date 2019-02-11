# amstel
## AMSTeL - the Adaptive MultiScale Template Library

AMSTeL is a C++ template library for the adaptive numerical solution of differential and singular integral equations by wavelet and multiscale techniques. This library provides the necessary infrastructure, a posteriori error estimation and basis-oriented refinement techniques to approximate the unknown solution up to a prescribed accuracy by finite linear combinations taken from a stable, countable dictionary (i.e., a Riesz basis or a frame) of the solution space.

On the one hand, the AMSTeL library provides reference implementations of various Riesz bases on bounded computational domains:
* orthogonal and biorthogonal wavelet bases on the interval
* anisotropic and isotropic tensor product wavelet bases on the cube
* biorthogonal wavelet bases on more complicated polyhedral domains
* orthogonal polynomial systems
* trigonometric polynomial systems
Moreover, the following redundant dictionaries are covered by AMSTeL:
* multilevel finite element frames
* hybrid frames
* quarklet frames

On the other hand, the AMSTeL library provides the following, partly generic, approximation algorithms:
* tree approximation of functions
* inexact matrix-vector multiplication (APPLY) routines for the application of differential and singular integral operators in compresssive Riesz basis or frame coordinates
* inexact evaluation of nonlinearities in compressive Riesz basis or frame coordinates
* adaptive wavelet-Galerkin algorithms
* adaptive matrix-free solution algorithms for linear and semilinear operator equations (Richardson iteration, steepest descent)
