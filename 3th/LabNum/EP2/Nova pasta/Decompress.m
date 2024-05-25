#iniciar as variaveis como default
x=y=z=M=k=h=0;
#M: matriz decompress, (x,y) coordenadas
function resultado = derivate_fx(x,y,z,M,k,h)
  x_p1=x+k+1;
  x_n1=x-k-1;
  resultado = (M(x_p1,y,z)-M(x_n1,y,z))/(2*h);
endfunction

function resultado = derivate_fy(x,y,z,M,k,h)
  y_p1=y+k+1;
  y_n1=y-k-1;
  resultado = (M(x,y_p1,z)-M(x,y_n1,z))/(2*h);
endfunction

function resposta = Pij(A,x,xi,y,yj)
    a = x-xi;
    PX = [1, a, a^2, a^3];
    b= y-yj;
    PY = [1;
         b;
         b^2;
         b^3];
    resposta = PX * A * PY;
endfunction

#derivadas para as bordas da matriz
#valores da primeira linha
function resultado = board_derivate_fx0(x0,yj,z,M,k,h)
    x1=x0+k+1;#segunda linha
    resultado = (M(x1,yj,z)-M(x0,yj,z))/h;
endfunction

#valores da ultima linha
function resultado = board_derivate_fxp1(xp_n1,yj,z,M,k,h)
  xp2 = xp_n1; #ultima linha
  xp1 = xp_n1-k-1; #penultima linha
  resultado = (M(xp1,yj,z)-M(xp2,yj,z))/h;
endfunction

#valores da primeira coluna
function resultado = board_derivate_fy0(xi,y0,z,M,k,h)
  y1=y0+k+1; #segunda coluna com os valores conhecidos
  resultado = (M(xi,y1,z)-M(xi,y0,z))/h;
endfunction

#valores da ultima coluna
function resultado = board_derivate_fyp1(xi,yp_n1,z,M,k,h)
  yp2 = yp_n1; #ultima coluna
  yp1 = yp_n1-k-1; #penultima coluna conhecida
  resultado = (M(xi,yp1,z)-M(xi,yp2,z))/h;
endfunction

#nao sei se vai dar certo, testar
function resultado = derivate_fxy(x,y,z,M,k,h)
  [row,col,nz] = size(M);
  if(x=1)
    a = board_derivate_fx0(x,y,z,M,k,h);
  elseif(x==row)
    a = board_derivate_fxp1(x,y,z,M,k,h);
  else
    a = derivate_fx(x,y,z,M,k,h);
  endif

  if(y=1)
    b = board_derivate_fy0(x,y,z,M,k,h);
  elseif(y==col)
    b = board_derivate_fyp1(x,y,z,M,k,h);
  else
    b = derivate_fy(x,y,z,M,k,h);
  endif

  resultado = (a-b)/(2*h);
endfunction

#RESOLVER O UNDEFINED A PARTIR DAQUI
function  finalImg = decompress(compressedImg, method, k, h)
    [a, b, c]=size(compressedImg);

    aq = zeros(a + (a-1)*k, b + (b-1)*k, c);

    #cria a imagem decompressed
    for h=1:c
        for i=1:a
            for j=1:b
                      aq(1+(i-1)*(k+1), 1+(j-1)*(k+1), h) = compressedImg(i,j,h);
            endfor
        endfor
    endfor

    M = aq;
    [nrow,ncol,nz]=size(M);


    #display(aq);

    #(xi,yi)      (xi,yi_p1)
    #
    #(xi_p1,yi)      (xi_p1,yi_p1)
    #procura um quadrado (pequeno) para ser preenchido
    i = 1; #linha
    j = 1; #coluna

    #para encontrar os coeficientes da matriz é preciso resolver uma equaçaõ de multiplicação de matrizes
    B = [1, 0, 0, 0;
         1, h, h^2, h^3;
         0, 1, 0, 0;
         0, 1, 2*h, 3*(h^2)];
    #B transposta
    B_t = transpose(B);
    #matrizes invertidas
    B_inv = inv(B);
    B_t_inv = inv(B_t);
    for t=1:nz
      #percorre as linhas da matriz descompress e vai completando-a
      while (i<nrow)
        #percorre as colunas
        while(j<ncol)
          xi=i;
          xi_p1=i+k+1;
          yj=j;
          yj_p1=j+k+1;

          f1 = aq(xi,yj,t);
          f2 = aq(xi,yj_p1,t);
          f5 = aq(xi_p1,yj,t);
          f6 = aq(xi_p1,yj_p1,t);

          #calcular valores da primeira coluna
          if(yj==1)
            f3 = board_derivate_fy0(xi,yj,t,M,k,h);
            f7 = board_derivate_fy0(xi_p1,yj,t,M,k,h);
          else
            f3 = derivate_fy(xi,yj,t,M,k,h);
            f7 = derivate_fy(xi_p1,yj,t,M,k,h);
          endif

          #calcular valores da ultima coluna
          if(yj_p1==ncol)
            f4 = board_derivate_fyp1(xi,yj_p1,t,M,k,h);
            f8 = board_derivate_fyp1(xi_p1,yj_p1,t,M,k,h);
          else
            f4 = derivate_fy(xi,yj_p1,t,M,k,h);
            f8 = derivate_fy(xi_p1,yj_p1,t,M,k,h);
          endif

          if(xi==1)
            f9 = board_derivate_fx0(xi,yj,t,M,k,h);
            f10 = board_derivate_fx0(xi,yj_p1,t,M,k,h);
          else
            f9 = derivate_fx(xi,yj,t,M,k,h);
            f10 = derivate_fx(xi,yj_p1,t,M,k,h);
          endif

          if(xi_p1==nrow)
            f13 = board_derivate_fxp1(xi_p1,yj,t,M,k,h);
            f14 = board_derivate_fxp1(xi_p1,yj_p1,t,M,k,h);
          else
            f13 = derivate_fx(xi_p1,yj,t,M,k,h);
            f14 = derivate_fx(xi_p1,yj_p1,t,M,k,h);
          endif

          f11 = derivate_fxy(xi,yj,t,M,k,h);
          f12 = derivate_fxy(xi,yj_p1,t,M,k,h);
          f15 = derivate_fxy(xi_p1,yj,t,M,k,h);
          f16 = derivate_fxy(xi_p1,yj_p1,t,M,k,h);

          F=[f1,f2,f3,f4;
             f5,f6,f7,f8;
             f9,f10,f11,f12;
             f13,f14,f15,f16];

          #fazendo as contas da equação: B_inv * F * B_t_inv = A
          #A: matriz das incognitas
          A = B_inv * F * B_t_inv;

          #completa o quadrado pequeno
          for ii=i:i+k+1
            for jj=j:j+k+1
              if(M(ii,jj,t)==0)
                M(ii,jj,t) = Pij(A,ii,xi,jj,yj);
              endif
            endfor
          endfor
          j=j+k+1; #depois de preenchido, passa para o quadrado à direita
        endwhile
        j=1;
        i=i+k+1;
      endwhile
      i=1;
      j=1;
    endfor

    finalImg = M;
    imwrite(uint8(M), "decompressed.png");

endfunction

A=[1,1,1,1,1,1,1,1,1,1;
   2,2,2,2,2,2,2,2,2,2;
   3,3,3,3,3,3,3,3,3,3;
   4,4,4,4,4,4,4,4,4,4;
   5,5,5,5,5,5,5,5,5,5;
   6,6,6,6,6,6,6,6,6,6;
   7,7,7,7,7,7,7,7,7,7;
   8,8,8,8,8,8,8,8,8,8;
   9,9,9,9,9,9,9,9,9,9;
   10,10,10,10,10,10,10,10,10,10];

B=[1,1,1,1;
   2,2,2,2;
   3,3,3,3;
   4,4,4,4];

C=imread('compressed.png');

decompress(C, 1, 1, 1);



