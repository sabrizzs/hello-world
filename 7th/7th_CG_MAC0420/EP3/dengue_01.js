/*
    EP3 MAC0420/MAC5744 - Dengue

    Nome: Sabrina Araujo da Silva
    NUSP: 12566182
 */

window.onload = main;
var ctx;

var inseticida;
var tiro;
var mosquitos = []

var tiroDisponivel = true;
var ultimoQuadro = performance.now();

const BICO_INSETICIDA = 0.075;
const LAR_INSETICIDA = 0.05;
const ALT_MIN_INSETICIDA = 0.25;
const ALT_MAX_INSETICIDA = 0.75;
const ANG_MIN_INSETICIDA = -35;
const ANG_MAX_INSETICIDA =  75;
const COR_INSETICIDA_BASE = 'rgba(0, 179, 230, 1)';
const COR_INSETICIDA_PARAFUSO = 'rgba(0, 51, 128, 1)';
const COR_INSETICIDA_BICO = 'rgba(0, 204, 255, 1)';
const ALT_PASSO = 0.02;
const ANG_PASSO = 2;

var velocidade = 3;
var TIRO_VX = 0.3;
var TIRO_VY = 0.3;
const COR_TIRO = 'rgba(0, 0, 0, 1)';
const G = -0.05;

const ALT_DENGUE = 0.05;
const LAR_DENGUE = 0.05;
const MAX_VEL_DENGUE = 0.05;
const COR_DENGUE = 'rgba(127, 76, 51, 1)';
const BORDA = 0.15;

function main() {
    const canvas = document.getElementById('glcanvas');
    ctx = canvas.getContext('2d');
    if (!ctx) alert("Não consegui abrir o ctxo 2d :-( ");

    ctx.canvas.width = window.innerWidth;
    ctx.canvas.height = window.innerHeight;

    inseticida = new Inseticida();
    tiro = new Tiro();

    // Atualiza input da velocidade
    const controleVelocidade = document.getElementById('bVel');
    controleVelocidade.addEventListener('input', function() {
        velocidade = parseInt(this.value) * 0.5;
        console.log(`Velocidade alterada: ${velocidade}`);
    });

    atualizaTela();
    criaMosquitos(10);

    window.onresize = function() {
        console.log("Onresize.");
        ctx.canvas.width = window.innerWidth;
        ctx.canvas.height = window.innerHeight;
    };
}

function atualizaTela() {
    // Normaliza o canvas
    ctx.setTransform(  
        ctx.canvas.width, 0,
        0, ctx.canvas.height,
        0, 0
    );

    // Calcula dt para a velocidade
    const agora = performance.now();
    const dt = (agora - ultimoQuadro) / 1000;

    ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
    window.addEventListener('keydown', atualizaEstado);

    // Desenha elementos
    desenhaFundo();
    if(!tiroDisponivel) tiro.desenha(dt);
    inseticida.desenha();
    desenhaMosquitos(dt);

    // Verifica colisão entre tiro e mosquito
    if (!tiroDisponivel) {
        const mosquitoAtingido = tiro.verificaColisao(mosquitos);
        if (mosquitoAtingido) {
            const indiceMosquitoAtingido = mosquitos.indexOf(mosquitoAtingido);
            mosquitos.splice(indiceMosquitoAtingido, 1);
            tiroDisponivel = true;
            console.log('Mosquito atingido!');
        }
        tiro.atualiza(dt);
    }

    ultimoQuadro = agora;

    requestAnimationFrame(atualizaTela); 

}

function desenhaFundo() {
    ctx.fillStyle = 'pink';
    ctx.fillRect(-1, -1, 2, 2); // ret em (-1, -1) com largua 2 e altura 1.4

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
        this.alturaBase = (ALT_MIN_INSETICIDA + ALT_MAX_INSETICIDA)/2; 
        this.anguloBico = 0; 
    }

    // Métodos para controlar a altura da base do inseticida
    aumentaAltura() {
        this.alturaBase = Math.min(ALT_MAX_INSETICIDA, this.alturaBase + ALT_PASSO);
    }
    diminuiAltura() {
        this.alturaBase = Math.max(ALT_MIN_INSETICIDA, this.alturaBase - ALT_PASSO);
    }

    // Métodos para controlar o ângulo do bico do inseticida
    giraBicoAntihorario() {
        this.anguloBico = Math.max(ANG_MIN_INSETICIDA, this.anguloBico - ANG_PASSO);
    }
    giraBicoHorario() {
        this.anguloBico = Math.min(ANG_MAX_INSETICIDA, this.anguloBico + ANG_PASSO);
    }

    desenha() {
        // Desenha a base do inseticida
        desenhaRetangulo(0, 1 - this.alturaBase, this.alturaBase, LAR_INSETICIDA, COR_INSETICIDA_BASE);
        
        // Desenha o parafuso do bico do inseticida
        desenhaHexagono(LAR_INSETICIDA / 2, 1- this.alturaBase, LAR_INSETICIDA / 4, COR_INSETICIDA_PARAFUSO);
    
        // Desenha o bico do inseticida
        const xBico = LAR_INSETICIDA / 2;
        const yBico = 1 - this.alturaBase;
        const angulo = this.anguloBico * Math.PI / 180;
        desenhaTriangulo(xBico, yBico, BICO_INSETICIDA, COR_INSETICIDA_BICO, angulo);
    }
}

class Tiro {
    constructor() {
        // Calcula a posição do ponto médio entre o vértice do topo do triângulo e o vértice do lado direito
        const xBico = LAR_INSETICIDA / 2 + BICO_INSETICIDA * Math.sqrt(3) / 2; ;
        const yBico = 1 - inseticida.alturaBase;
        const angulo = inseticida.anguloBico * Math.PI / 180;
        const pontoMedioX = xBico + (BICO_INSETICIDA / 2) * Math.cos(angulo);
        const pontoMedioY = yBico - (BICO_INSETICIDA / 2) * Math.sin(angulo);

        // Define a posição do tiro como o ponto médio calculado
        this.x = pontoMedioX * -1;  
        this.y = pontoMedioY; 
        this.vx = TIRO_VX * Math.cos(-inseticida.anguloBico * Math.PI / 180) * velocidade;
        this.vy = TIRO_VY * Math.sin(-inseticida.anguloBico * Math.PI / 180) * velocidade; 
        this.cor = 'black';
    }

    disparaTiro() {
        if (tiroDisponivel){
            tiro = new Tiro(LAR_INSETICIDA / 2, 1 - inseticida.alturaBase, inseticida.anguloBico);
            tiroDisponivel = false;
            console.log('Novo tiro')
        }        
    }

    atualiza(dt) {
        this.vy += G * dt;
        this.x += this.vx * dt;
        this.y -= this.vy * dt;
        if (this.y >= 1 || this.x >= 1) {
            tiroDisponivel = true;
        }
    }

    desenha(dt) {
        desenhaCirculo(this.x, this.y, 0.015, COR_TIRO);
        this.atualiza(dt);
    }

    verificaColisao(mosquitos) {
        for (let mosquito of mosquitos) {
            const distanciaX = this.x - mosquito.x;
            const distanciaY = this.y - mosquito.y;
            const distancia = Math.sqrt(distanciaX * distanciaX + distanciaY * distanciaY);
            
            if (distancia < LAR_DENGUE / 2) {
                return mosquito;
            }
        }
        return null;
    }
}

class Mosquito {
    constructor() {
        this.x = Math.random() * (1 - 2 * BORDA) + BORDA;
        this.y = Math.random() * (1 - 2 * BORDA) + BORDA;
        this.vx = (Math.random() - 0.5) * 2 * MAX_VEL_DENGUE;
        this.vy = (Math.random() - 0.5) * 2 * MAX_VEL_DENGUE;
        this.rotacaoAsas = 0;
        this.direcaoAsas = 1;
        this.corAsas = corAleatoriaRGBA();
        this.corOlhos = corAleatoriaRGBA();
    }

    atualiza(dt) {
        this.x += this.vx * dt;
        this.y += this.vy * dt;

        // Reflete ao atingir as bordas
        if (this.x < BORDA || this.x > 1 - BORDA) {
            this.vx *= -1;
        }
        if (this.y < BORDA || this.y > 1 - BORDA) {
            this.vy *= -1;
        }

        // Adicionar perturbação aleatória na velocidade
        const perturbacao = 0.1; 
        if (Math.random() < perturbacao) {
            if (Math.random() < 0.5) this.vx *= -1;
            if (Math.random() < 0.5) this.vy *= -1;  
        }
        this.vx += (Math.random() - 0.5) * 0.005;
        this.vy += (Math.random() - 0.5) * 0.005;

        // Atualizar rotação das asas
        this.rotacaoAsas += this.direcaoAsas * 0.1;
        if (this.rotacaoAsas >= Math.PI / 12 || this.rotacaoAsas <= -Math.PI / 12) {
            this.direcaoAsas *= -1;
        }
    }

    desenha() {
        ctx.save();
        ctx.translate(this.x, this.y);

        // Desenha cabeça
        desenhaCirculo(0, 0, LAR_DENGUE / 2, COR_DENGUE);

        ctx.save();

        // Asa da esquerda
        ctx.rotate(this.rotacaoAsas);
        desenhaTriangulo(LAR_DENGUE / 2, 0, ALT_DENGUE / 2, this.corAsas);

        ctx.restore();
        ctx.save();

        // Asa da direita
        ctx.rotate(-this.rotacaoAsas);
        ctx.scale(-1, 1);
        desenhaTriangulo(LAR_DENGUE / 2, 0, ALT_DENGUE / 2, this.corAsas);

        ctx.restore();

        // Desenha olhos
        desenhaCirculo(-LAR_DENGUE / 4, ALT_DENGUE / 4, LAR_DENGUE / 12, this.corOlhos);
        desenhaCirculo(LAR_DENGUE / 4, ALT_DENGUE / 4, LAR_DENGUE / 12, this.corOlhos);

        ctx.restore();
    }
}

function criaMosquitos(numMosquitos) {
    for (let i = 0; i < numMosquitos; i++) {
        mosquitos.push(new Mosquito());
    }
}

function desenhaMosquitos(dt) {
    for (let mosquito of mosquitos) {
        mosquito.desenha();
    }
    for (let mosquito of mosquitos) {
        mosquito.atualiza(dt);
    }
}

function desenhaRetangulo(x, y, altura, largura, cor) {
    ctx.save(); 
    ctx.translate(x, y);
    ctx.fillStyle = cor;
    ctx.fillRect(0, 0, largura, altura);
    ctx.restore(); 
}

function desenhaHexagono(x, y, raio, cor) {
    ctx.save(); 
    ctx.translate(x, y);
    ctx.beginPath();
    ctx.fillStyle = cor;
    ctx.moveTo(0, 0);

    for (let i = 0; i < 6; i++) {
        const angulo = Math.PI / 3 * i;
        const xVertice = raio * Math.cos(angulo);
        const yVertice = raio * Math.sin(angulo);
        if (i === 0) {
            ctx.moveTo(xVertice, yVertice);
        } else {
            ctx.lineTo(xVertice, yVertice);
        }
    }

    ctx.closePath();
    ctx.fill();
    ctx.restore(); 
}

function desenhaTriangulo(x, y, lado, cor, angulo) {
    ctx.save(); 
    ctx.translate(x, y);
    ctx.rotate(angulo);
    ctx.beginPath();
    ctx.fillStyle = cor;
    ctx.moveTo(0, 0);
    
    const altura = lado * Math.sqrt(3) / 2; 
    const xBase = lado; 

    ctx.lineTo(xBase, -altura / 2);
    ctx.lineTo(xBase, altura / 2);
    ctx.lineTo(0, 0); 
    ctx.closePath();
    
    ctx.fill();
    ctx.restore(); 
}

function desenhaCirculo(x, y, raio, cor) {
    ctx.beginPath();
    ctx.fillStyle = cor;
    ctx.arc(x, y, raio, 0, Math.PI * 2);
    ctx.fill();
}

function corAleatoriaRGBA() {
    const r = Math.floor(Math.random() * 256);
    const g = Math.floor(Math.random() * 256); 
    const b = Math.floor(Math.random() * 256);
    return `rgba(${r}, ${g}, ${b}, 1)`;
}






