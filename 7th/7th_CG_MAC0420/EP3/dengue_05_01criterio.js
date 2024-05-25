/*
    EP3 MAC0420/MAC5744 - Dengue

    Nome: Sabrina Araujo da Silva
    NUSP: 12566182
 */

// WebGL
var gl;
var gCanvas;
var gShader = {};  // encapsula globais do shader

var gVertexShaderSrc;
var gFragmentShaderSrc;

var gPosicoes = [];
var gCores = [];
var gObjetos = []; 

//

window.onload = main;
var ctx;
var h; var w;

var inseticida;
var tiro;
var mosquitos = []
var mosquitosIndex = [];
var numMosquitos = 5;

var tiroDisponivel = true;
var ultimoQuadro = Date.now();

const BICO_INSETICIDA = 0.075;
const LAR_INSETICIDA = 0.05;
const ALT_MIN_INSETICIDA = 0.25;
const ALT_MAX_INSETICIDA = 0.75;
const ANG_MIN_INSETICIDA = -35;
const ANG_MAX_INSETICIDA =  75;
const COR_INSETICIDA_BASE = [0, .7, .9, 1];
const COR_INSETICIDA_PARAFUSO = [0, 0.2, 0.5, 1];
const COR_INSETICIDA_BICO = [0, 0.8, 1, 1];
const ALT_PASSO = 0.02;
const ANG_PASSO = 2;

var velocidade = 3;
var TIRO_VX = 0.3;
var TIRO_VY = 0.3;
const COR_TIRO = [0, 0, 0, 1]
const G = -0.05;

const ALT_DENGUE = 0.05;
const LAR_DENGUE = 0.05;
const MAX_VEL_DENGUE = 0.05;
const COR_DENGUE = [0.5, 0.3, 0.2, 1];
const BORDA = 0.15;


var pausado = false;
var passo = false;
var tempoPasso = 0;

function main() {
    gCanvas = document.getElementById("glcanvas");
    gl = gCanvas.getContext('webgl2');
    if (!gl) alert("WebGL 2.0 isn't available");

    gCanvas.width = window.innerWidth;
    gCanvas.height = window.innerHeight;

    w = gCanvas.width;
    h = gCanvas.height;

    inputVelocidade();
    inputPause();

    criaObjetos();

    atualizaTela();

    redimensionaCanvas();
}

function inputVelocidade() {
    // Atualiza input da velocidade
    const controleVelocidade = document.getElementById('bVel');
    controleVelocidade.addEventListener('input', function() {
        velocidade = parseInt(this.value) * 0.5;
        console.log(`Velocidade alterada: ${velocidade}`);
    });
}

function inputPause () {
    const pauseBotao = document.getElementById('bRun');
    const passoBotao = document.getElementById('bStep');
    pauseBotao.addEventListener('click', function() {
        console.log(`Botão \"${pauseBotao.value}\" pressionado`)
        pausado = !pausado;
        pauseBotao.value = pausado ? 'Continuar' : 'Pausar';
        passoBotao.value = pausado ? 'Passo' : '';
        passoBotao.disabled = !pausado;
    });

    passoBotao.addEventListener('click', function() {
        console.log(`Botão \"Passo\" pressionado`)
        passo = true;
    });
}

function criaObjetos() {
    inseticida = new Inseticida();
    inseticida.desenha();
    tiro = new Tiro();
    criaMosquitos(numMosquitos);
    mosquitosIndex = mosquitos.slice();
}

function redimensionaCanvas() {
    // Redimensiona o tamanho do canvas de acordo com o tamanho da tela
    window.onresize = function() {
        console.log("Onresize.");
        gCanvas.width = window.innerWidth;
        gCanvas.height = window.innerHeight;
    };
}

function atualizaTela() {
    // Calcula dt para a velocidade
    const agora = Date.now();
    var dt = (agora - ultimoQuadro) / 1000;
    ultimoQuadro = agora;

    if(!pausado || passo) {
        // Shaders
        crieShaders();

        // Define área de renderização
        gl.viewport(0, 0, gCanvas.width, gCanvas.height);

        // Limpa o contexto
        gl.clearColor(1.0, 0.71, 0.76, 1.0);
        gl.clear(gl.COLOR_BUFFER_BIT);

        // Se o botão passo foi pressionado, então avança somente 0.1s
        if(passo) {
            dt = 0.1;
            passo = false;

            // Imprime o estado de todos os objetos
            for (let i = 0; i < gObjetos.length; i++) {
                let objeto = gObjetos[i];
                let nomeObjeto;
        
                if (i < 3) {
                    nomeObjeto = `Inseticida: ${objeto.constructor.name}`;
                } else if (i < 3 + numMosquitos * 5) {
                    nomeObjeto = `Mosquito: ${objeto.constructor.name}`;
                } else {
                    nomeObjeto = `Tiro: ${objeto.constructor.name}`; 
                }
        
                console.log('Objeto:', nomeObjeto);
                console.log('Posição do objeto:', objeto.pos);
            }
        }

        // Atualiza posições/ Desenha vértices
        window.addEventListener('keydown', atualizaEstado);
        if (!tiroDisponivel) {
            tiro.verificaColisao();
        }
        gPosicoes = [];
        for (let i = 0; i < gObjetos.length; i++) {
            gObjetos[i].atualize(dt);
        }

        // Atualiza o buffer de vertices
        gl.bindBuffer(gl.ARRAY_BUFFER, gShader.bufPosicoes);
        gl.bufferData(gl.ARRAY_BUFFER, flatten(gPosicoes), gl.STATIC_DRAW);
        gl.uniform2f(gShader.uResolution, gCanvas.width, gCanvas.height);
        gl.clear(gl.COLOR_BUFFER_BIT);
        gl.drawArrays(gl.TRIANGLES, 0, gPosicoes.length);

        window.requestAnimationFrame(atualizaTela);
        
    } else {
        window.requestAnimationFrame(atualizaTela); 
    }
}

function atualizaEstado(event) {
    const tecla = event.key.toLowerCase();
    console.log(`Tecla ${tecla} pressionada`);

    // Controlar a altura da base do inseticida
    if (tecla == 'i') {
        inseticida.aumentaAltura();
    }
    if (tecla == 'k') {
        inseticida.diminuiAltura();
    }

    // Controlar o ângulo do bico do inseticida
    if (tecla == 'j') {
        inseticida.giraBicoAntihorario();
    }
    if (tecla == 'l') {
        inseticida.giraBicoHorario();
    }

    // Disparar um tiro do inseticida
    if (tecla == 't') {
        tiro.disparaTiro();
    }
}

class Inseticida {
    constructor() {
        this.larguraBase = LAR_INSETICIDA * w;
        this.alturaBase = ALT_MAX_INSETICIDA * h;
        this.xBase = this.larguraBase;           // x e y do centro da base
        this.yBase = this.alturaBase - this.alturaBase/2;
        this.ladoBico = BICO_INSETICIDA * h;
        this.anguloBico = 0; 
    }

    // Métodos para controlar a altura do inseticida
    aumentaAltura() {
        this.alturaBase = Math.min(ALT_MAX_INSETICIDA * h, this.alturaBase + ALT_PASSO * h);
        this.yBase = Math.min(this.alturaBase - this.alturaBase/2, this.yBase + ALT_PASSO * h);
        gObjetos[0].atualize(this.xBase, this.yBase);
        gObjetos[1].atualize(this.larguraBase, this.alturaBase);
        gObjetos[2].atualize(1, this.larguraBase, this.alturaBase);
        console.log(`Aumentou a altura para: ${(this.alturaBase/h).toFixed(2)}`);
    }

    diminuiAltura() {
        this.alturaBase = Math.max(ALT_MIN_INSETICIDA * h, this.alturaBase - ALT_PASSO * h);
        this.yBase = Math.max(this.alturaBase - this.alturaBase/2 - ALT_MIN_INSETICIDA * h, this.yBase - ALT_PASSO * h);
        gObjetos[0].atualize(this.xBase, this.yBase);
        gObjetos[1].atualize(this.larguraBase, this.alturaBase);
        gObjetos[2].atualize(1, this.larguraBase, this.alturaBase);
        console.log(`Diminuiu a altura para: ${(this.alturaBase/h).toFixed(2)}`);
    }

    // Métodos para controlar o ângulo do bico do inseticida
    giraBicoAntihorario() {
        if (this.anguloBico > ANG_MIN_INSETICIDA) {
            this.anguloBico = Math.max(ANG_MIN_INSETICIDA, this.anguloBico - ANG_PASSO);
            gObjetos[2].rotaciona(-this.anguloBico);
            console.log(`Girou o bico do inseticida no sentido horário em: ${this.anguloBico} graus.`);
        }
    }
    
    giraBicoHorario() {
        if (this.anguloBico < ANG_MAX_INSETICIDA) {
            this.anguloBico = Math.min(ANG_MAX_INSETICIDA, this.anguloBico + ANG_PASSO);
            gObjetos[2].rotaciona(this.anguloBico);
            console.log(`Girou o bico do inseticida no sentido antihorário em: ${this.anguloBico} graus.`);
        }
    }
    
    desenha() {
        // Base inseticida
        gObjetos.push(new Retangulo(this.xBase, this.yBase, this.larguraBase * 2, this.alturaBase, 0, 0, COR_INSETICIDA_BASE));
        // Parafuso do inseticida
        gObjetos.push(new Hexagono(this.larguraBase, this.alturaBase, this.larguraBase / 2, 0, 0, COR_INSETICIDA_PARAFUSO));
        // Bico do inseticida
        gObjetos.push(new Triangulo(this.larguraBase, this.alturaBase, this.ladoBico, 0, 0, COR_INSETICIDA_BICO));
    }
}

class Tiro {
    constructor() {
        this.x = 0;
        this.y = 0;
    }

    disparaTiro() {
        if (tiroDisponivel){
            tiro = new Tiro();
            tiroDisponivel = false;
            console.log('Disparou um tiro!')
            this.desenha();
        }        
    }

    desenha() {
        this.xBico = inseticida.larguraBase;
        this.yBico = inseticida.alturaBase;
        const angulo = inseticida.anguloBico * Math.PI / 180;
        const pontoMedioX = this.xBico + (BICO_INSETICIDA / 2) * Math.cos(angulo);
        const pontoMedioY = this.yBico - (BICO_INSETICIDA / 2) * Math.sin(angulo);

        this.x = pontoMedioX * -1;  
        this.y = pontoMedioY;
        this.vx = TIRO_VX * Math.cos(-inseticida.anguloBico * Math.PI / 180) * velocidade * h;
        this.vy = TIRO_VY * Math.sin(-inseticida.anguloBico * Math.PI / 180) * velocidade * h;

        gObjetos.push(new Disco(this.xBico, this.yBico, 20, this.vx, this.vy, sorteieCorRGBA()));
    }

    // Verifica colisão entre tiro e mosquito
    verificaColisao() {
        for (let i = 0; i < mosquitosIndex.length; i++) {
            let mosquito = mosquitosIndex[i];
            if (this.x >= mosquito.x - LAR_DENGUE * h && this.x <= mosquito.x + LAR_DENGUE * h &&
                this.y >= mosquito.y - ALT_DENGUE * h && this.y <= mosquito.y + ALT_DENGUE * h) {              
                let indice = 3 + 5 * (i);
                gObjetos.splice(indice, 5);
                mosquitosIndex.splice(i, 1);
                tiroDisponivel = true;
                console.log(`Colisão com mosquito em [${(mosquito.x / h).toFixed(2)}, ${(mosquito.y / h).toFixed(2)}]!`);
                if(mosquitosIndex.length === 0) console.log("Todos os mosquitos foram eliminados!");
                break;
            }
        }
    }
}

class Mosquito {
    constructor(index) {
        this.index = index;

        this.borda = BORDA * h;
        this.larDengue = LAR_DENGUE * h;

        let limiteX = w - this.larDengue - this.borda;
        let limiteY = h - this.larDengue - this.borda;
        this.x = Math.random() * limiteX + this.borda;
        this.y = Math.random() * limiteY + this.borda;

        this.vx = (Math.random() - 0.5) * 2 * MAX_VEL_DENGUE * h;
        this.vy = (Math.random() - 0.5) * 2 * MAX_VEL_DENGUE * h;
        this.rotacaoAsas = 0;
        this.direcaoAsas = 1;
        this.corAsas = corAleatoriaRGBA();
        this.corOlhos = corAleatoriaRGBA();
    }

    desenha() {
        // Corpo mosquito
        gObjetos.push(new Quadrado(this.x, this.y, this.larDengue, this.vx, this.vy, COR_DENGUE, true, this.index));
        // Asa direita
        gObjetos.push(new Triangulo(this.x + this.larDengue/2, this.y, this.larDengue*0.6, this.vx, this.vy, this.corAsas, 1, true));
        // Asa esquerda
        gObjetos.push(new Triangulo(this.x - this.larDengue/2, this.y, this.larDengue*0.6, this.vx, this.vy, this.corAsas, -1, true));
        // Olho direito
        gObjetos.push(new Quadrado(this.x + this.larDengue/4, this.y, this.larDengue/5, this.vx, this.vy, this.corOlhos, true));
        // Olho esquerdo
        gObjetos.push(new Quadrado(this.x - this.larDengue/4, this.y, this.larDengue/5, this.vx, this.vy, this.corOlhos, true));
    }
}

function criaMosquitos(numMosquitos) {
    mosquitos = [];
    for (let i = 0; i < numMosquitos; i++) { 
        mosquitos.push(new Mosquito(i));
    }
    for (let mosquito of mosquitos) {
        mosquito.desenha();
    }
}

function corAleatoriaRGBA() {
    const r = Math.floor(Math.random() * 256);
    const g = Math.floor(Math.random() * 256); 
    const b = Math.floor(Math.random() * 256);
    const a = 1; // Alpha (opacidade) definido como 1
    return [r / 255, g / 255, b / 255, a];
}

// WebGL VertexShaders

gVertexShaderSrc = `#version 300 es

// aPosition é um buffer de entrada
in vec2 aPosition;
uniform vec2 uResolution;
in vec4 aColor;  // buffer com a cor de cada vértice
out vec4 vColor; // varying -> passado ao fShader

void main() {
    vec2 escala1 = aPosition / uResolution;
    vec2 escala2 = escala1 * 2.0;
    vec2 clipSpace = escala2 - 1.0;

    gl_Position = vec4(clipSpace, 0, 1);
    vColor = aColor; 
}
`;

gFragmentShaderSrc = `#version 300 es

// Vc deve definir a precisão do FS.
// Use highp ("high precision") para desktops e mediump para mobiles.
precision highp float;

// out define a saída 
in vec4 vColor;
out vec4 outColor;

void main() {
  outColor = vColor;
}
`;

function crieShaders() {
    //  cria o programa
    gShader.program = makeProgram(gl, gVertexShaderSrc, gFragmentShaderSrc);
    gl.useProgram(gShader.program);
  
    // carrega dados na GPU
    gShader.bufPosicoes = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, gShader.bufPosicoes);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(gPosicoes), gl.STATIC_DRAW);
  
    // Associa as variáveis do shader ao buffer gPosicoes
    var aPositionLoc = gl.getAttribLocation(gShader.program, "aPosition");
    // Configuração do atributo para ler do buffer
    // atual ARRAY_BUFFER
    let size = 2;          // 2 elementos de cada vez - vec2
    let type = gl.FLOAT;   // tipo de 1 elemento = float 32 bits
    let normalize = false; // não normalize os dados
    let stride = 0;        // passo, quanto avançar a cada iteração depois de size*sizeof(type) 
    let offset = 0;        // começo do buffer
    gl.vertexAttribPointer(aPositionLoc, size, type, normalize, stride, offset);
    gl.enableVertexAttribArray(aPositionLoc);
  
    // buffer de cores
    var bufCores = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, bufCores);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(gCores), gl.STATIC_DRAW);
    var aColorLoc = gl.getAttribLocation(gShader.program, "aColor");
    gl.vertexAttribPointer(aColorLoc, 4, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(aColorLoc);
  
    // resolve os uniforms
    gShader.uResolution = gl.getUniformLocation(gShader.program, "uResolution");
  
  };

function aproximeDisco(raio, ref = 4) {
    // primeiro um quadrado ao redor da origem
    let vertices = [
        vec2(raio, 0),
        vec2(0, raio),
        vec2(-raio, 0),
        vec2(0, -raio),
    ];

    // refinamento: adiciona 1 vértice em cada lado
    for (let i = 1; i < ref; i++) {
        let novo = [];
        let nv = vertices.length;
        for (let j = 0; j < nv; j++) {
        novo.push(vertices[j]);
        let k = (j + 1) % nv;
        let v0 = vertices[j];
        let v1 = vertices[k];
        let m = mix(v0, v1, 0.5);

        let s = raio / length(m);
        m = mult(s, m)
        novo.push(m);
        }
        vertices = novo;
    }
    return vertices;
}

function Disco(x, y, r, vx, vy, cor) {
    this.vertices = aproximeDisco(r, 3);
    this.nv = this.vertices.length;
    this.vel = vec2(vx, vy);
    this.cor = cor;
    this.pos = vec2(x, y);
  
    // inicializa buffers    
    let centro = this.pos;
    let nv = this.nv;
    let vert = this.vertices;
    for (let i = 0; i < nv; i++) {
      let k = (i + 1) % nv;
      gPosicoes.push(centro);
      gPosicoes.push(add(centro, vert[i])); // translada 
      gPosicoes.push(add(centro, vert[k]));
  
      gCores.push(cor);
      gCores.push(cor);
      gCores.push(cor);
    }
    /**
     * atualiza a posicao dos vertices do disco
     * @param {*} delta - intervalo de tempo desde a ultima atualizacao
     */


    this.atualize = function (delta) {
        this.vel[1] += G * delta * h;

        // Atualiza a posição com base na nova velocidade
        this.pos[0] += this.vel[0] * delta;
        this.pos[1] += this.vel[1] * delta;
        let x, y;
        let vx, vy;
        [x, y] = this.pos;
        [vx, vy] = this.vel;

        tiro.x = x;
        tiro.y = y;
    
        // Colisão com as paredes
        if (x < 0 || y < 0 || x >= gCanvas.width || y >= gCanvas.height) {
            tiroDisponivel = true;
            gObjetos.pop();
            return;
        }

        let centro = this.pos = vec2(x, y);
        this.vel = vec2(vx, vy);
    
        let nv = this.nv;
        let vert = this.vertices;
        for (let i = 0; i < nv; i++) {
            let k = (i + 1) % nv;
            gPosicoes.push(centro);
            gPosicoes.push(add(centro, vert[i]));
            gPosicoes.push(add(centro, vert[k]));
        }
    }
}

function Retangulo(x, y, largura, altura, vx, vy, cor) {
    this.vertices = [
        vec2(-largura / 2, -altura / 2), // bottom left
        vec2(largura / 2, -altura / 2),  // bottom right
        vec2(largura / 2, altura / 2),   // top right
        vec2(-largura / 2, altura / 2)   // top left
    ];
    this.nv = this.vertices.length;
    this.vel = vec2(vx, vy);
    this.cor = cor;
    this.pos = vec2(x, y);

    // initialize buffers
    let centro = this.pos;
    let nv = this.nv;
    let vert = this.vertices;
    for (let i = 0; i < nv; i++) {
        let k = (i + 1) % nv;
        gPosicoes.push(centro);
        gPosicoes.push(add(centro, vert[i])); // translate
        gPosicoes.push(add(centro, vert[k]));

        gCores.push(cor);
        gCores.push(cor);
        gCores.push(cor);
    }

    /**
     * updates the position of the rectangle vertices
     * @param {*} delta - time interval since the last update
     */
    this.atualize = function (x, y, delta) {
        if (x !== undefined && y !== undefined) {
            this.pos = vec2(x, y);
        } 
    
        // Atribui a posição do objeto
        let centro = this.pos;
        for (let i = 0; i < this.nv; i++) {
            let k = (i + 1) % this.nv;
            gPosicoes.push(centro);
            gPosicoes.push(add(centro, this.vertices[i]));
            gPosicoes.push(add(centro, this.vertices[k]));
        }
    };
}

function Hexagono(x, y, lado, vx, vy, cor) {
    // Calcula os vértices do hexágono
    this.vertices = [];
    for (let i = 0; i < 6; i++) {
        const angulo = Math.PI / 3 * i;
        const xVertice = lado * Math.cos(angulo);
        const yVertice = lado * Math.sin(angulo);
        this.vertices.push(vec2(xVertice, yVertice));
    }
    this.nv = this.vertices.length;
    this.vel = vec2(vx, vy);
    this.cor = cor;
    this.pos = vec2(x, y);

    // Inicializa os buffers
    let centro = this.pos;
    let nv = this.nv;
    let vert = this.vertices;
    for (let i = 0; i < nv; i++) {
        let k = (i + 1) % nv;
        gPosicoes.push(centro);
        gPosicoes.push(add(centro, vert[i])); // translada
        gPosicoes.push(add(centro, vert[k]));

        gCores.push(cor);
        gCores.push(cor);
        gCores.push(cor);
    }

    /**
     * Atualiza a posição dos vértices do hexágono
     * @param {*} delta - intervalo de tempo desde a última atualização
     */
    this.atualize = function (x, y, delta) {
        if (x !== undefined && y !== undefined) {
            this.pos = vec2(x, y);
        } 
    
        // Atribui a posição do objeto
        let centro = this.pos;
        for (let i = 0; i < this.nv; i++) {
            let k = (i + 1) % this.nv;
            gPosicoes.push(centro);
            gPosicoes.push(add(centro, this.vertices[i]));
            gPosicoes.push(add(centro, this.vertices[k]));
        }
    };
}

function Triangulo(x, y, lado, vx, vy, cor, orientacao = 1, mosquito) {
    // Calcula os vértices do triângulo
    this.vertices = [
        vec2(0, 0),                                // Vértice inferior
        vec2(lado * orientacao, lado * Math.sqrt(3) / 2),   // Vértice superior direito
        vec2(lado * orientacao, -lado * Math.sqrt(3) / 2)   // Vértice inferior direito
    ];
    this.nv = this.vertices.length;
    this.vel = vec2(vx, vy);
    this.cor = cor;
    this.pos = vec2(x, y);
    this.asaAberta = true;

    // Inicializa os buffers
    let centro = this.pos;
    let nv = this.nv;
    let vert = this.vertices;
    for (let i = 0; i < nv; i++) {
        let k = (i + 1) % nv;
        gPosicoes.push(centro);
        gPosicoes.push(add(centro, vert[i])); // translada
        gPosicoes.push(add(centro, vert[k]));

        gCores.push(cor);
        gCores.push(cor);
        gCores.push(cor);
    }

    /**
     * Atualiza a posição dos vértices do triângulo
     * @param {*} delta - intervalo de tempo desde a última atualização
     */
    this.atualize = function (delta, x, y) {
        if (x !== undefined && y !== undefined) {
            this.pos = vec2(x, y);
        } 

        if(mosquito){
            this.pos = add(this.pos, mult(delta, this.vel));
            let x, y;
            let vx, vy;
            [x, y] = this.pos;
            [vx, vy] = this.vel;
            let altura = lado * Math.sqrt(3) / 2;

            // Bate as asas
            if (this.asaAberta) {
                // Posição das asas abertas
                this.vertices[1] = vec2(lado * orientacao, lado * Math.sqrt(3) / 2 + 2);
                this.vertices[2] = vec2(lado * orientacao, -lado * Math.sqrt(3) / 2 - 2);
            } else {
                // Posição das asas fechadas
                this.vertices[1] = vec2(lado * orientacao, lado * Math.sqrt(3) / 2 - 10);
                this.vertices[2] = vec2(lado * orientacao, -lado * Math.sqrt(3) / 2 + 10);
            }
            // Alterna o estado das asas para o próximo quadro
            this.asaAberta = !this.asaAberta;

            let corpoDengue = (LAR_DENGUE / 2) * h;

            // Colisão com as bordas
            if(orientacao === 1){
                if (x < 0 + corpoDengue) { vx = -vx; };
                if (x  >= gCanvas.width + corpoDengue) { vx = -vx; };
            } else {
                if (x < 0 - corpoDengue) { vx = -vx; };
                if (x + corpoDengue >= gCanvas.width ) { vx = -vx; };
            }
            
            if (y < 0) { vy = -vy; };
            if (y >= gCanvas.height) { vy = -vy; };

            let centro = this.pos = vec2(x, y);
            this.vel = vec2(vx, vy);

            let nv = this.nv;
            let vert = this.vertices;
            for (let i = 0; i < nv; i++) {
                let k = (i + 1) % nv;
                gPosicoes.push(centro);
                gPosicoes.push(add(centro, vert[i]));
                gPosicoes.push(add(centro, vert[k]));
            }
            return;
        }
    
        // Atribui a posição do objeto
        let centro = this.pos;
        for (let i = 0; i < this.nv; i++) {
            let k = (i + 1) % this.nv;
            gPosicoes.push(centro);
            gPosicoes.push(add(centro, this.vertices[i]));
            gPosicoes.push(add(centro, this.vertices[k]));
        }
    };

    this.rotaciona = function(delta) {
        delta = delta * Math.PI / 180;
        // Cria uma matriz de rotação
        let c = Math.cos(delta);
        let s = Math.sin(delta);
        let matrizRotacao = [
            [c, -s],
            [s, c]
        ];
    
        // Rotaciona cada vértice
        for (let i = 0; i < this.nv; i++) {
            let vertice = this.vertices[i];
            this.vertices[i] = vec2(
                matrizRotacao[0][0] * vertice[0] + matrizRotacao[0][1] * vertice[1],
                matrizRotacao[1][0] * vertice[0] + matrizRotacao[1][1] * vertice[1]
            );
        }
        this.atualize();
    };
}

function Quadrado(x, y, lado, vx, vy, cor, mosquito, index) {
    this.vertices = [
        vec2(-lado / 2, -lado / 2), // bottom left
        vec2(lado / 2, -lado / 2),  // bottom right
        vec2(lado / 2, lado / 2),   // top right
        vec2(-lado / 2, lado / 2)   // top left
    ];
    this.nv = this.vertices.length;
    this.vel = vec2(vx, vy);
    this.cor = cor;
    this.pos = vec2(x, y);
    this.mosquito = mosquito;

    // initialize buffers
    let centro = this.pos;
    let nv = this.nv;
    let vert = this.vertices;
    for (let i = 0; i < nv; i++) {
        let k = (i + 1) % nv;
        gPosicoes.push(centro);
        gPosicoes.push(add(centro, vert[i])); // translate
        gPosicoes.push(add(centro, vert[k]));

        gCores.push(cor);
        gCores.push(cor);
        gCores.push(cor);
    }

    /**
     * updates the position of the rectangle vertices
     * @param {*} delta - time interval since the last update
     */
    this.atualize = function (delta, x, y) {
        if (x !== undefined && y !== undefined) {
            this.pos = vec2(x, y);
        } 

        if(mosquito){
            this.pos = add(this.pos, mult(delta, this.vel));
            let x, y;
            let vx, vy;
            
            [x, y] = this.pos;
            [vx, vy] = this.vel;

            if (index !== undefined &&  mosquitos[index] !== undefined) {
                mosquitos[index].x = this.pos[0];
                mosquitos[index].y = this.pos[1];
            }
            
            /* Adiciona perturbação aleatória na velocidade
            const perturbacao = 0.1; 
            if (Math.random() < perturbacao) {
                if (Math.random() < 0.5) vx *= -1;
                if (Math.random() < 0.5) vy *= -1;  
            }
            vx += (Math.random() - 0.5) * 0.005;
            vy += (Math.random() - 0.5) * 0.005; */

            // bateu? Altere o trecho abaixo para considerar o raio!
            if (x < 0) { x = -x; vx = -vx; };
            if (y < 0) { y = -y; vy = -vy; };
            if (x >= gCanvas.width) { x = gCanvas.width; vx = -vx; };
            if (y >= gCanvas.height) { y = gCanvas.height; vy = -vy; };
            
            let centro = this.pos = vec2(x, y);
            this.vel = vec2(vx, vy);

            let nv = this.nv;
            let vert = this.vertices;
            for (let i = 0; i < nv; i++) {
                let k = (i + 1) % nv;
                gPosicoes.push(centro);
                gPosicoes.push(add(centro, vert[i]));
                gPosicoes.push(add(centro, vert[k]));
            }
            return;
        }
    
        // Atribui a posição do objeto
        let centro = this.pos;
        for (let i = 0; i < this.nv; i++) {
            let k = (i + 1) % this.nv;
            gPosicoes.push(centro);
            gPosicoes.push(add(centro, this.vertices[i]));
            gPosicoes.push(add(centro, this.vertices[k]));
        }
    };
}

