function imagem()
  p = 500;
  A = ones(p, p, 3);
  k = 2.069e-3;
  fMin = 0; fMax = 1;

  for x=1 : p
    for y=1 : p
      A(x, y, 1) = floor(((sin(x * k) - fMin)/(fMax - fMin)) * 256);
      A(x, y, 2) = floor((((sin(y * k) + sin(x * k))/2 - fMin)/(fMax - fMin)) * 256);
      A(x, y, 3) = floor(((sin(x * k) - fMin)/(fMax - fMin)) * 256);
    endfor
  endfor

  imwrite(uint8(A), "pdf.png", 'Quality', 100);
endfunction

function imagem5()
  p = 500;
  A = ones(p, p, 3);
  k = 2.069e-3;

  for x=1 : p
    for y=1 : p
      A(x, y, 1) = floor( ( sin(x * k) ) * 256);
      A(x, y, 2) = floor( ( sin(x * k) ) * 256);
      A(x, y, 3) = floor( ( sin(x * k) ) * 256);
    endfor
  endfor

  imwrite(uint8(A), "peb.png", 'Quality', 100);
endfunction

function imagem4()
  p = 500;
  A = ones(p, p, 3);

  for x=1 : p
    for y=1 : p
      A(x, y, 1) = floor( (256/x+y) );
      A(x, y, 2) = floor( (256/y*x) );
      A(x, y, 3) = floor( (256/x+y) );
    endfor
  endfor

  imwrite(uint8(A), "colorido.png", 'Quality', 100);
endfunction

function imagem3()
  p = 500;
  A = ones(p, p, 3);

  for x=1 : p
    for y=1 : p
      A(x, y, 1) = floor( (256*x)/280 );
      A(x, y, 2) = floor( (256*y)/280 );
      A(x, y, 3) = floor( (256*x)/280 );
    endfor
  endfor

  imwrite(uint8(A), "c1.png", 'Quality', 100);
endfunction






