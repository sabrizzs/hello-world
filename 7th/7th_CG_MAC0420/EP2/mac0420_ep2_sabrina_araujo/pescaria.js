/*
    pescaria de MAC0420/MAC5744 - Pescaria

    Nome: Sabrina Araujo da Silva
    NUSP: 12566182
 */

window.onload = main;

var ctx;

var alfavel = 1;
var scoreValue = 0;
var arpaoPosicaoX = 0;

var bolhas = [];
var peixes = [];
var numPeixes = 10; 

var botaoPasso = document.getElementById('passo');
var botaoJogar = document.getElementById('jogar');

var jogando = true;
var passo = false;
var colisao = false;

function main() {
    const canvas = document.getElementById('canvas');
    ctx = canvas.getContext('2d');
    if (!ctx) alert("Não consegui abrir o contexto 2d :-( ");

    ctx.canvas.width = window.innerWidth;
    ctx.canvas.height = window.innerHeight - 190;

    atualizaTela();

    window.onresize = function() {
        console.log("Onresize.");
        ctx.canvas.width = window.innerWidth;
        ctx.canvas.height = window.innerHeight - 190;
    };
    console.log("teste");
}

// lida com o botão de jogar/pausar
function clickJogar() {
    console.log("Botão jogar clicado.");
    jogando = !jogando;
    botaoPasso.disabled = !botaoPasso.disabled
    botaoJogar.textContent = jogando ? 'Pausar' : 'Jogar';
}

// lida com o botão de passo a passo
function clickPasso() {
    console.log("Botão passo a passo clicado.");
    passo = true;

    for (var i = 0; i < peixes.length; i++) {
        var peixe = peixes[i];
        console.log("Peixe " + i + ": Antes -> X: " + peixe.x + ", Y: " + peixe.y);
    }
    atualizaPeixes();
    for (var i = 0; i < peixes.length; i++) {
        var peixe = peixes[i];
        console.log("Peixe " + i + ": Depois -> X: " + peixe.x + ", Y: " + peixe.y);
    }

    for (var i = 0; i < bolhas.length; i++) {
        var bolha = bolhas[i];
        console.log("Bolha: Antes -> X: " + bolha.x + ", Y: " + bolha.y);
    }
    atualizaBolhas();
    for (var i = 0; i < bolhas.length; i++) {
        var bolha = bolhas[i];
        console.log("Bolha: Depois -> X: " + bolha.x + ", Y: " + bolha.y);     
    }
}

function atualizaTela() {
    if(jogando || passo){
        ctx.setTransform(  // normaliza o canvas
            ctx.canvas.width / 2, 0,
            0, ctx.canvas.height / 2,
            ctx.canvas.width / 2, ctx.canvas.height / 2
        );

        ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);

        alfavel = document.getElementById('velocidade').value;

        if(jogando){
            botaoJogar.addEventListener('click', clickJogar);
            botaoPasso.addEventListener('click', clickPasso);
            window.addEventListener('keydown', moveArpao);
            canvas.addEventListener('mousemove', moveArpao);
            canvas.addEventListener('mousedown', atiraBolha);
            
            adicionaPeixes();
            atualizaBolhas();
            atualizaPeixes();
            verificaColisao()
        }

        desenhaFundo();
        desenhaArpao();
        desenhaBolhas();
        desenhaPeixes();

        requestAnimationFrame(atualizaTela);
    }else{
        requestAnimationFrame(atualizaTela);
    }
}

function desenhaFundo() {
    ctx.fillStyle = 'lightblue';
    ctx.fillRect(-1, -1, 2, 2 - 0.6); // ret em (-1, -1) com largua 2 e altura 1.4

    ctx.fillStyle = 'tan'; 
    ctx.fillRect(-1, 1 - 0.6, 2, 0.6);
}

function desenhaArpao() {
    ctx.fillStyle = 'red'; 
    ctx.beginPath();
    ctx.moveTo(arpaoPosicaoX, 1 - 0.35);
    ctx.lineTo(arpaoPosicaoX - 0.04, 0.9); 
    ctx.lineTo(arpaoPosicaoX + 0.04, 0.9); 
    ctx.closePath();
    ctx.fill();
}

// desenha as bolhas que estão no array de bolhas
function desenhaBolhas() {
    for(var i = 0; i < bolhas.length; i++) {
        var bolha = bolhas[i];
        ctx.save();
        ctx.translate(bolha.x, bolha.y);
        ctx.fillStyle = 'white'; 
        ctx.beginPath();
        ctx.arc(0, 0, bolha.raio, 0, Math.PI * 2);
        ctx.closePath();
        ctx.fill();
        ctx.restore();
    }
}

// desenha os peixes que estão no array de peixes
function desenhaPeixes() {
    for(var i = 0; i < peixes.length; i++) {
        var peixe = peixes[i];
        ctx.save();
        ctx.translate(peixe.x, peixe.y);
        ctx.fillStyle = peixe.cor;
        ctx.beginPath();
        var angulo = (Math.PI * 2) / peixe.numLados;
        ctx.moveTo(peixe.raio * Math.cos(0), peixe.raio * Math.sin(0));
        for(var j = 1; j <= peixe.numLados; j++) {
            ctx.lineTo(peixe.raio * Math.cos(angulo * j), peixe.raio * Math.sin(angulo * j));
        }
        ctx.closePath();
        ctx.fill();
        ctx.restore();
    }
}

function moveArpao(event) {
    if(event.key === 'a'){
        arpaoPosicaoX -= 0.1;
        if (arpaoPosicaoX < -1) arpaoPosicaoX = -1;
    } else if(event.key === 'd'){
        arpaoPosicaoX += 0.1;
        if (arpaoPosicaoX > 1) arpaoPosicaoX = 1;
    } else if(event.key === 's'){
        atiraBolha();
    } else if(event.type === 'mousemove'){
        arpaoPosicaoX = (event.clientX - ctx.canvas.offsetLeft) / ctx.canvas.width * 2 - 1;
        if (arpaoPosicaoX < -1) arpaoPosicaoX = -1;
        if (arpaoPosicaoX > 1) arpaoPosicaoX = 1;
    }
}

// define uma nova bolha no array de bolhas
function atiraBolha() {
    var novaBolha = {
        x: arpaoPosicaoX, 
        y: 1 - 0.35,
        raio: 0.05
    };
    bolhas.push(novaBolha);
}

function atualizaBolhas() {
    for(var i = 0; i < bolhas.length; i++) {
        var bolha = bolhas[i];
        bolha.y -= 0.02; 
        if(bolha.y <= -1) {
            bolhas.splice(i, 1);
            i--; 
        }
    }
}

function atualizaPeixes() {
    for(var i = 0; i < peixes.length; i++) {
        var peixe = peixes[i];
        peixe.x += peixe.vx * alfavel;
        peixe.y += peixe.vy * alfavel;

        if(peixe.x + peixe.raio >= 1 || peixe.x - peixe.raio <= -1) {
            peixe.vx *= -1;
        }
        if(peixe.y + peixe.raio >= 0.4 || peixe.y - peixe.raio <= -1) {
            peixe.vy *= -1;
        }
    }
}

function adicionaPeixes() {
    function criaPeixe() {
        poligonos = [4, 6, 8, 12, 16]; //define os números de lados para os polígonos/peixes
        var novoPeixe = {              // cria um novo peixe com valores aleatórios
            x: Math.random() * 1.7 - 0.9,
            y: Math.random() * 1.1 - 0.9,
            vx: (Math.random() * 2 - 1) * 0.01,
            vy: (Math.random() * 2 - 1) * 0.01,
            raio: Math.random() * 0.1 + 0.05,
            numLados: poligonos[Math.floor(Math.random() * poligonos.length)],
            cor: 'rgb(' + Math.floor(Math.random() * 256) + ',' + Math.floor(Math.random() * 256) + ',' + Math.floor(Math.random() * 256) + ')'
        };
        return novoPeixe;
    }
    
    while (peixes.length < numPeixes) {
        peixes.push(criaPeixe());
    }
}

function verificaColisao() {
    for(var i = 0; i < bolhas.length; i++) {
        var bolha = bolhas[i];
        for(var j = 0; j < peixes.length; j++) {
            var peixe = peixes[j];
            if(colisaoBolhaPeixe(bolha, peixe)) {
                console.log("Capturou um peixe!");
                bolhas.splice(i, 1);
                peixes.splice(j, 1);
                scoreValue += 1;
                atualizaScore();
                i--;
                break;
            }
        }
    }
}

// verifica se teve colisão com base na fórmula da distância
function colisaoBolhaPeixe(bolha, peixe) {
    var distanciaX = bolha.x - peixe.x;
    var distanciaY = bolha.y - peixe.y;
    var distancia = Math.sqrt(distanciaX * distanciaX + distanciaY * distanciaY);
    return distancia < bolha.raio + peixe.raio; 
}

function atualizaScore() {
    var score = document.getElementById('score');
    score.textContent = 'Peixes capturados: ' + scoreValue;
    
}