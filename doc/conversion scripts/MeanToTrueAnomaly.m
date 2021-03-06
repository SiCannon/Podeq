## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, see
## <http://www.gnu.org/licenses/>.

## MeanToTrueAnomaly - converts mean anomaly to true anomaly
##
## Inputs:
##   e = eccentricity
##   M = mean anomaly (rad)
## Outputs:
##   f = true anomaly (rad)

## Author: Luis Baars <orbitnerd@gmail.com>
## Created: 2012-02-14

function [ f ] = MeanToTrueAnomaly (e, M)
  if (e >= 1.0)
    error("MeanToTrueAnomaly does not support parabolic or hyperbolic orbits!")
  endif

  E = MeanToEccenAnomaly(e, M);
  f = EccenToTrueAnomaly(e, E);
endfunction
