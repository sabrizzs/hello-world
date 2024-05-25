## Copyright (C) 2022 Heitor
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {} {@var{retval} =} decompress (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Heitor <heitor@pop-os>
## Created: 2022-05-28

function retval = decompress (compressedImg, method, k, h)
    compressedImg = imread(compressedImg); 
    n = size(compressedImg, 2);
    p = n + ((n - 1) * k);  
    D = zeros(p, p, 3);
    D = D - 1;
    for i=0:n-1
      for j=0:n-1 
        D(i*(k + 1) + 1, j*(k + 1) + 1, :) = compressedImg(i+1, j+1, :);
      endfor
    endfor
    
    if method == 1
    
      A = [1 0 0 0; 1 0 h 0; 1 h 0 0; 1 h h (h*h)];   
      B = zeros(4, 1, 3);
      for I=0:n-2
        for J=0:n-2
          for i=0:1
            for j=0:1
              B(i*2 + j + 1, :) = D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :);
            endfor
          endfor
          aux = B(2, :);
          B(2, :) = B(4, :);
          B(4, :) = aux;
          aux = B(1, :);
          B(1, :) = B(3, :);
          B(3, :) = aux;
          #B
          C = A\B;
          for l=0:k+1
            for q=0:k+1
              if D(I*(k + 1) + l + 1, J*(k + 1) + q + 1) == -1
                auxX = I*(k + 1) + l + 1;
                auxY = J*(k + 1) + q + 1;
                x = (h/(k+1))*(k + 1 - l);
                y = (h/(k+1))*q;
                #disp("D("), disp(auxX), disp(", "), disp(auxY), disp(") = "), disp(D(I*(k + 1) + p + 1, J*(k + 1) + q + 1));
                D(auxX, auxY, 1) = C(1) + C(2)*x + C(3)*y + C(4)*x*y;
                D(auxX, auxY, 2) = C(5) + C(6)*x + C(7)*y + C(8)*x*y;
                D(auxX, auxY, 3) = C(9) + C(10)*x + C(11)*y + C(12)*x*y;
              endif
            endfor
          endfor
        endfor
      endfor
      
      
      
      
      
    else
      A = [1 0 0 0; 1 h (h*h) (h*h*h); 0 1 0 0; 0 1 (2*h) (3*h*h)];
      B = zeros(4, 4, 3);
      for I=0:n-2
        for J=0:n-2
          for T=0:1
            for L=0:1
              for i=0:1
                for j=0:1
                  if (T == 0 && L == 0)
                    #f
                    B(T*2 + i + 1, L*2 + j + 1, :) = D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :);
                  elseif (T == 0 && L == 1)
                    #delf dely
                    if(J*(k + 1) + j*(k + 1) + 1 == p)
                      B(T*2 + i + 1, L*2 + j + 1, :) = (D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :) - D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/h;
                    elseif(J*(k + 1) + j*(k + 1) + 1 == 1)
                      B(T*2 + i + 1, L*2 + j + 1, :) = (D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :))/h;
                    else
                      B(T*2 + i + 1, L*2 + j + 1, :) = (D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/(2*h);
                    endif
                  elseif (T == 1 && L == 0)
                    #delf delx
                    if(I*(k + 1) + i*(k + 1) + 1 == p)
                      B(T*2 + i + 1, L*2 + j + 1, :) = (D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :) - D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :))/h;
                    elseif(I*(k + 1) + i*(k + 1) + 1 == 1)
                      B(T*2 + i + 1, L*2 + j + 1, :) = (D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :) - D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :))/h;
                    else
                      B(T*2 + i + 1, L*2 + j + 1, :) = (D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :) - D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :))/(2*h);
                    endif
                  else
                    #del2f delx dely
                    #calcular delf delx de delf dely
                    if(I*(k + 1) + i*(k + 1) + 1 == p)
                      #delf dely(xi, yj) - delf dely(x_{i-1}, yj) /h
                      #vamos calcular delf dely(xi, yj)
                      if(J*(k + 1) + j*(k + 1) + 1 == p)
                        d1 = (D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :) - D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/h;
                        d2 = (D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :) - D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/h;
                      elseif(J*(k + 1) + j*(k + 1) + 1 == 1)
                        d1 = (D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :))/h;
                        d2 = (D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :))/h;
                      else
                        d1 = (D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/(2*h);
                        d2 = (D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/(2*h);
                      endif
                      B(T*2 + i + 1, L*2 + j + 1, :) = (d2 - d1)/(h);                      
                    elseif(I*(k + 1) + i*(k + 1) + 1 == 1)
                    #vamos calcular dely(x_{i+1}, yj) - delf dely(x_i, yj) /h
                      if(J*(k + 1) + j*(k + 1) + 1 == p)
                        d1 = (D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :) - D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/h;
                        d2 = (D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :) - D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/h;
                      elseif(J*(k + 1) + j*(k + 1) + 1 == 1)
                        d1 = (D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :))/h;
                        d2 = (D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :))/h;
                      else
                        d1 = (D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/(2*h);
                        d2 = (D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + i*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/(2*h);
                      endif 
                      B(T*2 + i + 1, L*2 + j + 1, :) = (d2 - d1)/(h);                      
                    else
                    #vamos calcular dely(x_{i+1}, yj) - delf dely(x_{i-1}, yj) / 2h
                      if(J*(k + 1) + j*(k + 1) + 1 == p)
                        d1 = (D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :) - D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/h;
                        d2 = (D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :) - D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/h;
                      elseif(J*(k + 1) + j*(k + 1) + 1 == 1)
                        d1 = (D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :))/h;
                        d2 = (D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + j*(k + 1) + 1, :))/h;
                      else
                        d1 = (D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + (i + 1)*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/(2*h);
                        d2 = (D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + (j + 1)*(k + 1) + 1, :) - D(I*(k + 1) + (i - 1)*(k + 1) + 1, J*(k + 1) + (j - 1)*(k + 1) + 1, :))/(2*h);
                      endif                       
                      B(T*2 + i + 1, L*2 + j + 1, :) = (d2 - d1)/(2*h);
                    endif
                  endif
                endfor
              endfor
            endfor
          endfor
          #disp("A matriz B é igual a: ");
          #B
          for z=0:1
            for g=0:1
              aux2 = B(z*2 + 1, g*2 + 1, :);
              B(z*2 + 1, g*2 + 1, :) = B(z*2 + 2, g*2 + 1, :);
              B(z*2 + 2, g*2 + 1, :) = aux2;
              aux2 = B(z*2 + 2, g*2 + 2, :);
              B(z*2 + 2, g*2 + 2, :) = B(z*2 + 1, g*2 + 2, :);
              B(z*2 + 1, g*2 + 2, :) = aux2;
            endfor
          endfor
          #disp("A matriz dos del é: ");
          #B
          C1 = inv(A)*B(:,:,1)*inv(A');
          C2 = inv(A)*B(:,:,2)*inv(A');
          C3 = inv(A)*B(:,:,3)*inv(A');
          
          for l=0:k+1
            for q=0:k+1
              if D(I*(k + 1) + l + 1, J*(k + 1) + q + 1) == -1
                auxX = I*(k + 1) + l + 1;
                auxY = J*(k + 1) + q + 1;
                x = (h/(k+1))*(k + 1 - l);
                y = (h/(k+1))*q;
                #disp("D("), disp(auxX), disp(", "), disp(auxY), disp(") = "), disp(D(I*(k + 1) + p + 1, J*(k + 1) + q + 1));
                #D(auxX, auxY, 1) = C(1) + C(2)*x + C(3)*y + C(4)*x*y;
                #D(auxX, auxY, 2) = C(5) + C(6)*x + C(7)*y + C(8)*x*y;
                #D(auxX, auxY, 3) = C(9) + C(10)*x + C(11)*y + C(12)*x*y;
                D(auxX, auxY, 1) = [1 x x**2 x**3]*C1*[1; y; y**2; y**3];
                D(auxX, auxY, 2) = [1 x x**2 x**3]*C2*[1; y; y**2; y**3];
                D(auxX, auxY, 3) = [1 x x**2 x**3]*C3*[1; y; y**2; y**3];
              endif
            endfor
          endfor
        endfor
      endfor  
    endif
    imwrite(uint8(D), "decompressed.png"); 
    retval = D;
    

   

endfunction
