function compresss(originalImg, k)    originalImg = imread(originalImg);    p = size(originalImg, 2);    n = idivide(int32(p + k), int32(1 + k), "fix");    N = zeros(n, n, 3);    for i=0:n-1      for j=0:n-1        N(i + 1, j + 1, :) = originalImg(i*(k + 1) + 1, j*(k + 1) + 1, :);      endfor
    endfor
    imwrite(uint8(N), "compressed.png", 'Quality', 100);endfunction